#pragma once

#include <stdint.h>
#include <vector>
#include <memory>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/euler_angles.hpp> 

class Scene;

class Transformable {
private:
    glm::vec3 translation;
    glm::vec3 rotation;
    glm::quat quaternion;
    glm::vec3 scale;
    Scene* scene;
    void updateRotation();
    void updateQuaternion();
protected:
	std::vector<std::shared_ptr<Transformable>> children;
    glm::mat4 world_transform;
public:
    Transformable();
    Transformable(const Transformable& drawable);
    void translate(const glm::vec3& translation);
    void rotate(const glm::vec3& rotation);
    void scaling(const glm::vec3& scale);
    virtual void setTranslation(const glm::vec3& translation);
    virtual void setRotation(const glm::vec3& rotation);
    virtual void setQuaternion(const glm::quat& quaternion);
    virtual void setScale(const glm::vec3& scale);
    glm::vec3 getTranslation() const;
    glm::vec3 getRotation() const;
    glm::quat getQuaternion() const;
    glm::vec3 getScale() const;
    glm::vec3 getWorldPosition() const;
    void add(std::shared_ptr<Transformable> child);
    virtual void update(const glm::mat4& transform);
    glm::mat4 getTransform() const;
    glm::mat4 getInverseTransform() const;
    const glm::mat4& getWorldTransform() const;
    glm::mat4 getInverseWorldTransform() const;
    const Scene& getScene() const;
    virtual void addedToScene(Scene& _scene, std::shared_ptr<Transformable>& self);
    virtual ~Transformable();
    friend Scene;
};
