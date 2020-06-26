#pragma once

#include <stdint.h>
#include <vector>
#include <memory>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/euler_angles.hpp> 

class Camera;
class Scene;
class DrawableLight;

class Drawable {
private:
    glm::vec3 translation;
    glm::vec3 rotation;
    glm::vec3 scale;
    void render(std::vector<bool> visited,

        const glm::mat4& transform
    );
protected:
	std::vector<std::shared_ptr<Drawable>> children;
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
    virtual void draw(const Camera& projection, const Scene& scene, const DrawableLight &light) const = 0;
    virtual void drawDepth(const Camera &projection, const Scene &scene) const = 0;
	virtual void drawShadowMap(const Scene &scene, const DrawableLight &light) const;
    void render(const Camera &camera, const Scene& scene, const DrawableLight &light) const;
    void renderShadow(const Scene&, const DrawableLight&) const;
    virtual void update(const glm::mat4& transform, Scene& scene);
    glm::mat4 getTransform() const;
    glm::mat4 getInverseTransform() const;
    glm::mat4 getInverseWorldTransform() const;
    virtual ~Drawable();
    friend Camera;

	void renderDepth(const Camera &camera, const Scene &scene) const;
};
#include "scene.h"
