#include "drawable.h"
#include "scene.h"

#include <iostream>
#include <glm/gtx/string_cast.hpp>

Drawable::Drawable() : children(), has_parent(false)
{
    this -> world_transform = glm::mat4(1.0f);
    this -> translation = glm::vec3(0,0,0);
    this -> rotation = glm::vec3(0,0,0);
    this -> scale = glm::vec3(1,1,1);
}

Drawable::Drawable(const Drawable& drawable) : children(), has_parent(false)
{
    this -> world_transform = drawable.world_transform;
    this -> translation = drawable.translation;
    this -> rotation = drawable.rotation;
    this -> scale = drawable.scale;
}

void Drawable::drawShadowMap(const Scene &scene, const DrawableLight &light) const {}

void Drawable::rotate(const glm::vec3& _rotation)
{
    this->rotation += _rotation;
}

void Drawable::translate(const glm::vec3& _translation)
{
    this->translation += _translation;
}

void Drawable::scaling(const glm::vec3& _scale)
{
    this->scale *= _scale;
}

void Drawable::setTranslation(const glm::vec3& _translation)
{
    this->translation = _translation;
}

void Drawable::setRotation(const glm::vec3& _rotation)
{
    this->rotation = _rotation;
}

void Drawable::setScale(const glm::vec3& _scale)
{
    this->scale = _scale;
}

glm::vec3 Drawable::getTranslation() const
{
    return this->translation;
}

glm::vec3 Drawable::getRotation() const
{
    return this->rotation;
}

glm::vec3 Drawable::getScale() const
{
    return this->scale;
}

void Drawable::render(const Camera& camera, const Scene& scene, const DrawableLight &light) const
{
    this -> draw(camera, scene, light);
    for (const auto &child: this->children)
    {
        child->render(camera, scene, light);
    }
}

void Drawable::renderDepth(const Camera &camera, const Scene &scene) const
{
	this->drawDepth(camera, scene);
	for(const auto &child : this->children) child->renderDepth(camera, scene);
}

void Drawable::renderShadow(const Scene &scene, const DrawableLight &light) const
{
	this->drawShadowMap(scene, light);
	for(const auto &child : this->children) child->renderShadow(scene, light);
}

void Drawable::xRayCull(const Camera &camera, const Scene &scene) const
{
	this->drawXRayCull(camera, scene);
	for(const auto &child : this->children) child->xRayCull(camera, scene);
}

void Drawable::update(const glm::mat4& transform, Scene& scene) {
    this -> world_transform = transform*this->getTransform();
    for (std::shared_ptr<Drawable> &child: this->children)
    {
        child->update(this -> world_transform, scene);
    }
}

glm::mat4 Drawable::getTransform() const
{
    return 
        glm::translate(glm::mat4(1.0f), this->translation)*
        glm::orientate4(this->rotation)*
        glm::scale(glm::mat4(1.0f), this->scale);
}

glm::vec3 Drawable::getWorldPosition() const
{
	glm::vec4 pos = this -> world_transform * glm::vec4(0.0f, 0.0f, 0.0f, 1.0f);
	glm::vec3 res = glm::vec3(pos.x/pos.w, pos.y/pos.w, pos.z/pos.w);
	return res;
}

glm::mat4 Drawable::getInverseTransform() const
{
    return glm::inverse(getTransform());
}

glm::mat4 Drawable::getInverseWorldTransform() const
{
    return glm::inverse(world_transform);
}

void Drawable::add(std::shared_ptr<Drawable> child)
{
    if (child->has_parent) {
        throw std::logic_error("Drawable already has parent");
    } else {
        child -> has_parent = true;
        children.push_back(child);
    }
}

Drawable::~Drawable() {}

void Drawable::drawXRayCull(const Camera &camera, const Scene &scene) const
{
}

