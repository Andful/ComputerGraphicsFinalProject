#include "util3D/directional_light.h"
#include "util3D/scene.h"
#include "util3D/mesh.h"
#include "util3D/geometry.h"

DirectionalLight::DirectionalLight(const glm::mat4& _projectionMatrix, const glm::vec3& _color, const glm::ivec2& _dimensions) {
    projectionMatrix = _projectionMatrix;
    Light::data.light_color = _color;
    dimensions = _dimensions;

    Light::updateUniformData();

    texture = Texture(dimensions.x, dimensions.y, GL_DEPTH_COMPONENT32F);
    texture.set(GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    texture.set(GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	texture.set(GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	texture.set(GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    framebuffer = Framebuffer(texture, GL_DEPTH_ATTACHMENT);
}

void DirectionalLight::update(const glm::mat4& transform) {
    Camera::update(transform);
    Light::data.light_position = getWorldPosition();
    Light::data.light_mvp = getProjectionMatrix() * getInverseWorldTransform();
    Light::updateUniformData();
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
    mesh.getDepthShader().bind();
    mesh.bind();
    mesh.getGeometry().bind();
    mesh.getGeometry().draw();
}

void DirectionalLight::prerender() {
    framebuffer.bind();
    glClearDepth(1.0);
	glClear(GL_DEPTH_BUFFER_BIT);
	glEnable(GL_DEPTH_TEST);
	glViewport(0, 0, dimensions.x, dimensions.y);
}

void DirectionalLight::postrender() {
    framebuffer.unbind();
}

void DirectionalLight::bind() {
    Light::bind();
    texture.bind(1);
}