#pragma once

#include <map>
#include <memory>
#include "drawable.h"
#include "group.h"
#include "drawable_light.h"

class Camera;

class Scene: public Drawable 
{
private:
    std::vector<glm::vec3> lightData;

public:
    Scene();
    const std::vector<glm::vec3>& getLightData() const;
    void addLight(const DrawableLight &light);
    void draw(const ICamera& camera, const Scene& scene) const ;
    using Drawable::update;
    void update();
};