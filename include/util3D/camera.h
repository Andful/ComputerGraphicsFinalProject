#pragma once

#include <memory>
#include <functional>
#include <glm/glm.hpp>
#include <GL/glew.h>
#include "transformable.h"

class Mesh;

typedef struct alignas(16) _CameraUniformData {
    glm::mat4 mvp;
    glm::vec3 camera_position;
} CameraUniformData;

class Camera : public Transformable
{
private:
    CameraUniformData data;
    std::unique_ptr<GLuint, std::function<void(GLuint*)>> ubo;
public:
    Camera();
    virtual void prerender() = 0;
    void render();
    virtual void renderMesh(const Scene& scene, const Mesh& mesh) const = 0;
    virtual void postrender();
    virtual const glm::mat4& getProjectionMatrix() const = 0;
    void update(const glm::mat4& transform) override;
    void bindCamera() const;
    virtual ~Camera() = default;
};