#pragma once

#include <stdint.h>
#include <vector>
#include <memory>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/euler_angles.hpp> 

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