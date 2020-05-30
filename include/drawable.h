#pragma once

#include <vector>
#include <memory>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/euler_angles.hpp> 

class Drawable;

class _Drawable {
public:
    glm::vec3 translation;
    glm::vec3 rotation;
    glm::vec3 scale;
    std::vector<std::shared_ptr<Drawable>> children;
};

class Drawable {
private:
    std::shared_ptr<_Drawable> drawable;
    void render(const glm::mat4& transform);
public:
    void translate(const glm::vec3& translation);
    void rotate(const glm::vec3& rotation);
    void scale(const glm::vec3& scale);
    void setTranslation(const glm::vec3& translation);
    void setRotation(const glm::vec3& rotation);
    void setScale(const glm::vec3& scale);
    template<class DRAWABLE>
    void add(const DRAWABLE& child)
    {
        this->drawable->children.push_back(std::shared_ptr<Drawable>(new DRAWABLE(child)));
    }
    virtual void draw(const glm::mat4& transform) = 0;
    glm::mat4 getTransform() const;
    virtual ~Drawable();
};