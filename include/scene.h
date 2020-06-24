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
    std::vector<std::shared_ptr<DrawableLight>> lightData;

public:
    Scene();
    const std::vector<std::shared_ptr<DrawableLight>>& getLightData() const;
    void addLight(std::shared_ptr<DrawableLight> light);
    void draw(const ICamera& camera, const Scene& scene, const DrawableLight& light) const;
	void drawDepth(const ICamera& camera,const Scene& scene) const;
    using Drawable::update;
    void update();

	void render(ICamera& camera) const;
};