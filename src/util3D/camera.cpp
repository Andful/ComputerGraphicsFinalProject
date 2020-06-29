#include <memory>
#include <exception>
#include <stdexcept>
#include "util3D/camera.h"
#include "util3D/scene.h"

Camera::Camera() {
    ubo = std::unique_ptr<GLuint, std::function<void(GLuint*)>>(new GLuint(), [](GLuint* p){
        glDeleteBuffers(1, p);
        delete p;
    });
    glCreateBuffers(1, ubo.get());
    glBindBuffer(GL_UNIFORM_BUFFER, *ubo);
    glBufferData(GL_UNIFORM_BUFFER, sizeof(CameraUniformData), NULL, GL_DYNAMIC_DRAW);
    glBindBuffer(GL_UNIFORM_BUFFER, 0);
}

void Camera::render() {
    prerender();
    bindCamera();
    const Scene& _scene = getScene();
    for(const std::shared_ptr<Mesh> mesh : _scene.getMeshes()) {
        renderMesh(_scene, *mesh);
    }
    postrender();
}

void Camera::update(const glm::mat4& transform) {
    Transformable::update(transform);
    data.mvp = getProjectionMatrix() * getInverseWorldTransform();
    data.camera_position = getWorldPosition();
    glBindBuffer(GL_UNIFORM_BUFFER, *ubo);
    glBufferSubData(
        GL_UNIFORM_BUFFER,
        0,
        sizeof(CameraUniformData),
        static_cast<const void*>(&data));
    glBindBuffer(GL_UNIFORM_BUFFER, 0);
}

void Camera::postrender(){}

void Camera::bindCamera() const {
    glBindBufferBase(GL_UNIFORM_BUFFER, 0, *ubo);
}