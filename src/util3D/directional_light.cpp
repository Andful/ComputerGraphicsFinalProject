#include "util3D/directional_light.h"
#include "util3D/scene.h"
#include "util3D/mesh.h"
#include "util3D/geometry.h"

DirectionalLight::DirectionalLight(const glm::mat4& _projectionMatrix, const glm::vec3& _color, const glm::ivec2& _dimensions) {
    projectionMatrix = _projectionMatrix;
    Light::data.light_color = _color;
    dimensions = _dimensions;

    texture = Texture(dimensions.x, dimensions.y, GL_DEPTH_COMPONENT32F);
    framebuffer = Framebuffer(texture, GL_DEPTH_ATTACHMENT);
}

void DirectionalLight::update(const glm::mat4& transform) {
    Camera::update(transform);
    Light::data.light_position = getWorldPosition();
    Light::data.light_mvp = getProjectionMatrix() * getInverseWorldTransform();
    glBindBuffer(GL_UNIFORM_BUFFER, *(Light::ubo));
    glBufferSubData(GL_UNIFORM_BUFFER, 0, sizeof(LightUniformData), static_cast<const void*>(&(Light::data)));
    glBindBuffer(GL_UNIFORM_BUFFER, 0);
}

const glm::mat4& DirectionalLight::getProjectionMatrix() const {
    return projectionMatrix;
}

void DirectionalLight::addedToScene(Scene& _scene, std::shared_ptr<Transformable>& self) {
    Transformable::addedToScene(_scene, self);
    std::shared_ptr<DirectionalLight> light = std::dynamic_pointer_cast<DirectionalLight>(self);
    _scene.lights.push_back(light);
    _scene.directional_lights.push_back(light);
}

void DirectionalLight::renderMesh(const Scene& _scene, const Mesh& mesh) const {
    mesh.getShadowShader().bind();
    mesh.bind();
    mesh.getGeometry().bind();
    mesh.getGeometry().draw();
}

void DirectionalLight::prerender() {
    framebuffer.bind();
    glViewport(0, 0, dimensions.x, dimensions.y);
    glDepthMask(GL_TRUE);
	glDepthFunc(GL_LEQUAL);
	glColorMask(GL_FALSE,GL_FALSE, GL_FALSE, GL_FALSE);
	glClearDepth(1.0);
	glClear(GL_DEPTH_BUFFER_BIT);
}

void DirectionalLight::postrender() {
    framebuffer.unbind();
}

void DirectionalLight::bind() {
    texture.bind(1);
}