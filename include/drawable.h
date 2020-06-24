#pragma once

#include <stdint.h>
#include <vector>
#include <memory>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/euler_angles.hpp> 

class ICamera;
class Scene;
class DrawableLight;

class Drawable {
private:
    std::vector<std::shared_ptr<Drawable>> children;
    glm::vec3 translation;
    glm::vec3 rotation;
    glm::vec3 scale;
    void render(std::vector<bool> visited,

        const glm::mat4& transform
    );
public:
    bool has_parent;
    glm::mat4 world_transform;
    int index;
    Drawable();
    Drawable(const Drawable& drawable);
    void translate(const glm::vec3& translation);
    void rotate(const glm::vec3& rotation);
    void scaling(const glm::vec3& scale);
    virtual void setTranslation(const glm::vec3& translation);
    virtual void setRotation(const glm::vec3& rotation);
    virtual void setScale(const glm::vec3& scale);
    glm::vec3 getTranslation() const;
    glm::vec3 getRotation() const;
    glm::vec3 getScale() const;
    glm::vec3 getWorldPosition() const;
    void add(std::shared_ptr<Drawable> child);
    virtual void draw(const ICamera& projection, const Scene& scene) const = 0;
    void render(const ICamera& camera, const Scene& scene) const;
    virtual void update(const glm::mat4& transform, Scene& scene);
    glm::mat4 getTransform() const;
    glm::mat4 getInverseTransform() const;
    glm::mat4 getInverseWorldTransform() const;
    virtual ~Drawable();
    friend ICamera;
};
#include "icamera.h"
#include "scene.h"
