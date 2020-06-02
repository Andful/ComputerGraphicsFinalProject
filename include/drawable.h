#pragma once

<<<<<<< HEAD
#include <stdint.h>
=======
>>>>>>> fa1109b6f083e67db6402c2f6b6f46510036cf78
#include <vector>
#include <memory>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/euler_angles.hpp> 

<<<<<<< HEAD
class ICamera;
class Scene;

class Drawable {
private:
    std::weak_ptr<Drawable> self; 
    std::vector<std::weak_ptr<Drawable>> parents;
    std::vector<std::shared_ptr<Drawable>> children;
    glm::vec3 translation;
    glm::vec3 rotation;
    glm::vec3 scale;
    void render(std::vector<bool> visited,

        const glm::mat4& transform
    );
public:
    int index;
    Scene* scene;
    Drawable();
    void translate(const glm::vec3& translation);
    void rotate(const glm::vec3& rotation);
    void scaling(const glm::vec3& scale);
    virtual void setTranslation(const glm::vec3& translation);
    virtual void setRotation(const glm::vec3& rotation);
    virtual void setScale(const glm::vec3& scale);
    glm::vec3 getTranslation() const;
    glm::vec3 getRotation() const;
    glm::vec3 getScale() const;
    void add(std::shared_ptr<Drawable> child);
    virtual void draw(const glm::mat4& projection, const glm::mat4& transform) = 0;
    void render(const glm::mat4& projection, const glm::mat4& transform);
    glm::mat4 getTransform() const;
    glm::mat4 getInverseTransform() const;
    const Scene& getScene() const;
    virtual ~Drawable();
    friend ICamera;
};
#include "icamera.h"
#include "scene.h"
=======
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
>>>>>>> fa1109b6f083e67db6402c2f6b6f46510036cf78
