#include <iostream>
#include <queue>
#include <glm/gtx/string_cast.hpp>

#include "util3D/transformable.h"
#include "util3D/scene.h"

Transformable::Transformable() : scene(nullptr), children()
{
    this -> world_transform = glm::mat4(1.0f);
    this -> translation = glm::vec3(0,0,0);
    this -> rotation = glm::vec3(0,0,0);
    this -> scale = glm::vec3(1,1,1);
}

Transformable::Transformable(const Transformable& transformable) : scene(nullptr), children()
{
    this -> world_transform = transformable.world_transform;
    this -> translation = transformable.translation;
    this -> rotation = transformable.rotation;
    this -> scale = transformable.scale;
}

void Transformable::updateRotation() {
    rotation  = glm::eulerAngles(quaternion); 	
}

void Transformable::updateQuaternion() {
    quaternion = glm::quat(rotation);
}

void Transformable::rotate(const glm::vec3& _rotation)
{
    rotation += _rotation;
    updateQuaternion();
}

void Transformable::translate(const glm::vec3& _translation)
{
    this->translation += _translation;
}

void Transformable::scaling(const glm::vec3& _scale)
{
    this->scale *= _scale;
}

void Transformable::setTranslation(const glm::vec3& _translation)
{
    this->translation = _translation;
}

void Transformable::setRotation(const glm::vec3& _rotation)
{
    this->rotation = _rotation;
    updateQuaternion();
}

void Transformable::setQuaternion(const glm::quat& _quaternion) {
    quaternion = _quaternion;
    updateRotation();
}

void Transformable::setScale(const glm::vec3& _scale)
{
    this->scale = _scale;
}

glm::vec3 Transformable::getTranslation() const
{
    return this->translation;
}

glm::vec3 Transformable::getRotation() const
{
    return this->rotation;
}

glm::vec3 Transformable::getScale() const
{
    return this->scale;
}

void Transformable::update(const glm::mat4& transform) {
    this -> world_transform = transform*this->getTransform();
    for (std::shared_ptr<Transformable> &child: this->children)
    {
        child->update(this -> world_transform);
    }
}

glm::mat4 Transformable::getTransform() const
{
    return 
        glm::translate(glm::mat4(1.0f), this->translation)*
        glm::orientate4(this->rotation)*
        glm::scale(glm::mat4(1.0f), this->scale);
}

glm::vec3 Transformable::getWorldPosition() const
{
	glm::vec4 pos = this -> world_transform * glm::vec4(0.0f, 0.0f, 0.0f, 1.0f);
	glm::vec3 res = glm::vec3(pos.x/pos.w, pos.y/pos.w, pos.z/pos.w);
	return res;
}

glm::mat4 Transformable::getInverseTransform() const
{
    return glm::inverse(getTransform());
}

const glm::mat4& Transformable::getWorldTransform() const {
    return world_transform;
}

glm::mat4 Transformable::getInverseWorldTransform() const
{
    return glm::inverse(world_transform);
}

void Transformable::add(std::shared_ptr<Transformable> child)
{
    if (child -> scene)
    {
        throw std::logic_error("Transformable already has parent");
    }
    else
    {
        children.push_back(child);
        if(scene)
        {
            child -> addedToScene(*scene, child);
        }
    }
}

void Transformable::addedToScene(Scene& _scene, std::shared_ptr<Transformable>& self)
{
    scene = &_scene;
    for (std::shared_ptr<Transformable> child : children)
    {
        child -> addedToScene(_scene, child);
    }
}

const Scene& Transformable::getScene() const
{
    return *scene;
}

Transformable::~Transformable() {}

