#include "drawable.h"

void Drawable::rotate(const glm::vec3& rotation)
{
    this->drawable->rotation += rotation;
}

void Drawable::translate(const glm::vec3& translation)
{
    this->drawable->translation += translation;
}

void Drawable::scale(const glm::vec3& scale)
{
    this->drawable->scale *= scale;
}

void Drawable::setTranslation(const glm::vec3& translation)
{
    this->drawable->translation = translation;
}

void Drawable::setRotation(const glm::vec3& rotation)
{
    this->drawable->rotation = rotation;
}

void Drawable::setScale(const glm::vec3& scale)
{
    this->drawable->scale = scale;
}

void Drawable::render(const glm::mat4& transform)
{
    glm::mat4 t = this->getTransform()*transform;
    this -> draw(t);
    for (const std::shared_ptr<Drawable>& child:drawable->children)
    {
        child->render(t);
    }
}

glm::mat4 Drawable::getTransform() const
{
    return glm::translate(glm::mat4(1.0f), drawable->translation)*
        glm::orientate4(drawable->rotation)*
        glm::scale(glm::mat4(1.0f), drawable->scale);
}

Drawable::~Drawable() {}

