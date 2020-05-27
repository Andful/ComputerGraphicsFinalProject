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

struct MeshLoadingException : public std::runtime_error {
    using std::runtime_error::runtime_error;
};

struct Vertex {
    glm::vec3 pos;
    glm::vec3 normal;
    glm::vec2 texCoord;
};
class Mesh {
public:
    Mesh(std::filesystem::path filePath);
    bool hasTextureCoords() const;

    // Bind VAO and call glDrawElements.
    void draw();

private:

    GLsizei m_numIndices { 0 };
    bool m_hasTextureCoords { false };
    std::shared_ptr<GLuint> m_ibo = nullptr;
    std::shared_ptr<GLuint> m_vbo = nullptr;
    std::shared_ptr<GLuint> m_vao = nullptr;
};
