#include "util3D/point_light.h"
#include "util3D/scene.h"

PointLight::PointLight() : PointLight(glm::vec3(1.0, 1.0, 1.0)) {}

PointLight::PointLight(const glm::vec3& color) {
    data.casts_shadow = false;
    data.light_color = color;
    Light::updateUniformData();
}

void PointLight::update(const glm::mat4& transform) {
    Transformable::update(transform);
    data.light_position = getWorldPosition();
    glBufferSubData(GL_UNIFORM_BUFFER, 0, sizeof(LightUniformData), static_cast<const void*>(&data));
}

void PointLight::addedToScene(Scene& _scene, std::shared_ptr<Transformable>& self) {
    Transformable::addedToScene(_scene, self);
    _scene.lights.push_back(std::dynamic_pointer_cast<Light>(self));
}