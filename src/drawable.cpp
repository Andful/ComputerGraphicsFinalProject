#include "drawable.h"
<<<<<<< HEAD
#include "scene.h"

Drawable::Drawable()
{
    this -> parents = {};
    this -> children = {};

    this -> translation = glm::vec3(0,0,0);
    this -> rotation = glm::vec3(0,0,0);
    this -> scale = glm::vec3(1,1,1);
}

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

void Drawable::add(std::shared_ptr<Drawable> child)
{   //::weak_ptr<Drawable>
    if (child->index >= 0 && child->scene == this -> scene)
    {
        child->parents.push_back(std::weak_ptr<Drawable>(this -> scene -> objects[size_t(this -> index)]));
        this -> children.push_back(this -> scene -> objects[size_t(child -> index)]); 
    }
}

void Drawable::render(const glm::mat4& projection, const glm::mat4& transform)
{
    glm::mat4 t = transform*this->getTransform();
    this -> draw(projection, t);
    for (const std::weak_ptr<Drawable>& child: this->children)
    {
        child.lock()->render(projection, t);
=======

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
>>>>>>> fa1109b6f083e67db6402c2f6b6f46510036cf78
    }
}

glm::mat4 Drawable::getTransform() const
{
<<<<<<< HEAD
    return 
        glm::translate(glm::mat4(1.0f), this->translation)*
        glm::orientate4(this->rotation)*
        glm::scale(glm::mat4(1.0f), this->scale);
}

glm::mat4 Drawable::getInverseTransform() const
{
    return glm::inverse(getTransform());
}

const Scene& Drawable::getScene() const
{
    return *scene;
=======
    return glm::translate(glm::mat4(1.0f), drawable->translation)*
        glm::orientate4(drawable->rotation)*
        glm::scale(glm::mat4(1.0f), drawable->scale);
>>>>>>> fa1109b6f083e67db6402c2f6b6f46510036cf78
}

Drawable::~Drawable() {}

