#pragma once
#include "disable_all_warnings.h"
DISABLE_WARNINGS_PUSH()
#include <GL/glew.h>
#include <glm/vec2.hpp>
#include <glm/vec3.hpp>
DISABLE_WARNINGS_POP()
#include <memory>
#include <exception>
#include <filesystem>
#include <vector>

#include "gl/shader_stage.h"
#include "util3D/geometry.h"

class Scene;
class Transformable;
class Camera;

struct GeometryLoadingException : public std::runtime_error {
    using std::runtime_error::runtime_error;
};

struct Vertex {
    glm::vec3 pos;
    glm::vec3 normal;
    glm::vec2 texCoord;
};
class Geometry {
private:
    GLsizei m_numIndices { 0 };
    std::shared_ptr<GLuint> ubo;
    bool m_hasTextureCoords { false };
    std::shared_ptr<GLuint> m_ibo = nullptr;
    std::shared_ptr<GLuint> m_vbo = nullptr;
    std::shared_ptr<GLuint> m_vao = nullptr;
    VertexShader vertex_shader;
public:
    Geometry() = default;
    Geometry(const Geometry&) = default;
    Geometry(std::filesystem::path filePath);
    bool hasTextureCoords() const;
    const VertexShader& getVertexShader();
    // Bind VAO and call glDrawElements.
    void draw() const;
    virtual const void* getUniformData() const;
    virtual GLsizeiptr getUniformDataSize() const;
    void initUniformBuffer() const;
    void updateUniformData() const;
    void updateUniformData();
    void bind() const;
    virtual ~Geometry() = default;
};
