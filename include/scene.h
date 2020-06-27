#pragma once

#include <map>
#include <memory>
#include "drawable.h"
#include "group.h"

class DrawableLight;
class Camera;

class Scene: public Drawable 
{
private:
    std::vector<std::shared_ptr<DrawableLight>> lightData;

public:
	bool useXRay = true;

    Scene();
    const std::vector<std::shared_ptr<DrawableLight>>& getLightData() const;
    void addLight(const std::shared_ptr<DrawableLight>& light);
    void draw(const Camera& camera, const Scene& scene, const DrawableLight& light) const;
	void drawDepth(const Camera& camera,const Scene& scene) const;
    using Drawable::update;
    void update();

	void render(Camera& camera) const;

	void toggleXRay();
};