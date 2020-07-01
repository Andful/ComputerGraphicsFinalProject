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
    std::shared_ptr<GLuint> ubo;
public:
    Geometry();
    virtual const VertexShader& getVertexShader() const = 0;
    // Bind VAO and call glDrawElements.
    virtual void draw() const = 0;
    virtual const void* getUniformData() const = 0;
    virtual GLsizeiptr getUniformDataSize() const = 0;
    void initUniformBuffer() const;
    void updateUniformData() const;
    void bind() const;
    virtual ~Geometry() = default;
};
