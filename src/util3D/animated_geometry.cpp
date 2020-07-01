#include <iostream>
#include <stack>
#include <vector>
#include <filesystem>
#include "disable_all_warnings.h"
DISABLE_WARNINGS_PUSH()
#include <assimp/Importer.hpp>
#include <assimp/postprocess.h>
#include <assimp/scene.h>
#include <fmt/format.h>
#include <glm/gtc/matrix_inverse.hpp>
#include <glm/mat3x3.hpp>
#include <glm/mat4x4.hpp>
#include <glm/vec4.hpp>
#include <gsl/span>
DISABLE_WARNINGS_POP()
#include "util3D/animated_geometry.h"

static glm::mat4 assimpMatrix(const aiMatrix4x4& m);
static glm::vec3 assimpVec(const aiVector3D& v);


void AnimatedGeometry::load(std::filesystem::path path) {
    if (!std::filesystem::exists(path))
        throw GeometryLoadingException(fmt::format("File {} does not exist", path.string().c_str()));

    Assimp::Importer importer;
    const aiScene* scene = importer.ReadFile(path.string().data(), aiProcess_GenSmoothNormals | aiProcess_Triangulate);

    if (scene == nullptr || scene->mRootNode == nullptr || scene->mFlags == AI_SCENE_FLAGS_INCOMPLETE) {
        throw GeometryLoadingException(fmt::format("Assimp failed to load mesh file {}", path.string().c_str()));
    }

    std::vector<Vertex> vertices;
    std::vector<unsigned> indices;

    std::stack<std::tuple<aiNode*, glm::mat4>> stack;
    stack.push({ scene->mRootNode, assimpMatrix(scene->mRootNode->mTransformation) });
    while (!stack.empty()) {
        auto [node, matrix] = stack.top();
        stack.pop();

        matrix *= assimpMatrix(node->mTransformation);
        const glm::mat3 normalMatrix = glm::inverseTranspose(glm::mat3(matrix));

        for (unsigned i = 0; i < node->mNumMeshes; i++) {
            // Process subMesh
            const aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];

            if (mesh->mNumVertices == 0 || mesh->mNumFaces == 0)
                std::cerr << "Empty mesh encountered" << std::endl;

            // Triangles
            const size_t indexOffset = vertices.size();
            for (unsigned j = 0; j < mesh->mNumFaces; j++) {
                const aiFace& face = mesh->mFaces[j];
                if (face.mNumIndices != 3) {
                    std::cerr << "Found a face which is not a triangle, discarding!" << std::endl;
                }

                auto aiIndices = face.mIndices;
                indices.push_back(static_cast<unsigned>(aiIndices[0] + indexOffset));
                indices.push_back(static_cast<unsigned>(aiIndices[1] + indexOffset));
                indices.push_back(static_cast<unsigned>(aiIndices[2] + indexOffset));
            }

            // Vertices
            for (unsigned j = 0; j < mesh->mNumVertices; j++) {
                const glm::vec3 pos = matrix * glm::vec4(assimpVec(mesh->mVertices[j]), 1.0f);
                const glm::vec3 normal = normalMatrix * assimpVec(mesh->mNormals[j]);
                glm::vec2 texCoord { 0 };
                if (mesh->HasTextureCoords(0)) {
                    texCoord = glm::vec2(assimpVec(mesh->mTextureCoords[0][j]));
                    m_hasTextureCoords = true;
                }
                vertices.push_back(Vertex { pos, normal, texCoord });
            }
        }

        for (unsigned i = 0; i < node->mNumChildren; i++) {
            stack.push({ node->mChildren[i], matrix });
        }
    }
    importer.FreeScene();

    // Create Element(/Index) Buffer Objects and Vertex Buffer Object.
    m_ibo -> push_back(GLuint());
    glCreateBuffers(1, &(m_ibo->back()));
    glNamedBufferStorage(m_ibo->back(), static_cast<GLsizeiptr>(indices.size() * sizeof(decltype(indices)::value_type)), indices.data(), 0);

    m_vbo -> push_back(GLuint());
    glCreateBuffers(1, &(m_vbo->back()));
    glNamedBufferStorage(m_vbo->back(), static_cast<GLsizeiptr>(vertices.size() * sizeof(Vertex)), vertices.data(), 0);

    // Bind vertex data to shader inputs using their index (location).
    // These bindings are stored in the Vertex Array Object.
    m_vao -> push_back(GLuint());
    glCreateVertexArrays(1, &(m_vao -> back()));

    // The indicies (pointing to vertices) should be read from the index buffer.
    glVertexArrayElementBuffer(m_vao -> back(), m_ibo -> back());

    // The position and normal vectors should be retrieved from the specified Vertex Buffer Object.
    // The stride is the distance in bytes between vertices. We use the offset to point to the normals
    // instead of the positions.
    glVertexArrayVertexBuffer(m_vao->back(), 0, m_vbo->back(), offsetof(Vertex, pos), sizeof(Vertex));
    glVertexArrayVertexBuffer(m_vao->back(), 1, m_vbo->back(), offsetof(Vertex, normal), sizeof(Vertex));
    glVertexArrayVertexBuffer(m_vao->back(), 2, m_vbo->back(), offsetof(Vertex, texCoord), sizeof(Vertex));
    glEnableVertexArrayAttrib(m_vao->back(), 0);
    glEnableVertexArrayAttrib(m_vao->back(), 1);
    glEnableVertexArrayAttrib(m_vao->back(), 2);

    m_numIndices.push_back(static_cast<GLsizei>(indices.size()));
}
AnimatedGeometry::AnimatedGeometry(std::filesystem::path filePath) {
    vertex_shader = VertexShader("shaders/default.vert.glsl");
    m_ibo = std::shared_ptr<std::vector<GLuint>>(
        new std::vector<GLuint>(),
        [](std::vector<GLuint>* p){
            glDeleteBuffers(GLsizei(p->size()), p -> data());
            delete p;
        });
    m_vbo = std::shared_ptr<std::vector<GLuint>>(
        new std::vector<GLuint>(),
        [](std::vector<GLuint>* p){
            glDeleteBuffers(GLsizei(p->size()), p -> data());
            delete p;
        });
    m_vao = std::shared_ptr<std::vector<GLuint>>(
        new std::vector<GLuint>(),
        [](std::vector<GLuint>* p){
            glDeleteBuffers(GLsizei(p->size()), p -> data());
            delete p;
        });

    if (!std::filesystem::exists(filePath)){
        throw GeometryLoadingException(fmt::format("File {} does not exist", filePath.string().c_str()));
    }
    std::cout << filePath << std::endl;
    std::vector<std::string> files = {};
    for(auto& p: std::filesystem::directory_iterator(filePath)) {
        files.push_back(p.path().string());
    }
    std::sort(files.begin(), files.end());
    for (auto&p : files) {
        std::cout << p << '\n';
        load(p);
    }
}
bool AnimatedGeometry::hasTextureCoords() const {
    return false;
}
const VertexShader& AnimatedGeometry::getVertexShader() const {
    return vertex_shader;
}
    // Bind VAO and call glDrawElements.
void AnimatedGeometry::draw() const {
    glBindVertexArray(m_vao->at(size_t(animation_index)));
    glDrawElements(GL_TRIANGLES, m_numIndices[size_t(animation_index)], GL_UNSIGNED_INT, nullptr);
}

void AnimatedGeometry::updateFrame() {
    animation_index = (animation_index + 1) % int(m_numIndices.size());
}

const void* AnimatedGeometry::getUniformData() const {
    return nullptr;
}

GLsizeiptr AnimatedGeometry::getUniformDataSize() const {
    return 0;
}

static glm::mat4 assimpMatrix(const aiMatrix4x4& m)
{
    //float values[3][4] = {};
    glm::mat4 matrix;
    matrix[0][0] = m.a1;
    matrix[0][1] = m.b1;
    matrix[0][2] = m.c1;
    matrix[0][3] = m.d1;
    matrix[1][0] = m.a2;
    matrix[1][1] = m.b2;
    matrix[1][2] = m.c2;
    matrix[1][3] = m.d2;
    matrix[2][0] = m.a3;
    matrix[2][1] = m.b3;
    matrix[2][2] = m.c3;
    matrix[2][3] = m.d3;
    matrix[3][0] = m.a4;
    matrix[3][1] = m.b4;
    matrix[3][2] = m.c4;
    matrix[3][3] = m.d4;
    return matrix;
}

static glm::vec3 assimpVec(const aiVector3D& v)
{
    return glm::vec3(v.x, v.y, v.z);
}