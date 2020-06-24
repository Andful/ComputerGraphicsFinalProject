#include "scene.h"
#include "camera.h"

void Scene::draw(const ICamera& camera,const Scene& scene) const {}

Scene::Scene()
{
	has_parent = true;
	lightData = {};
}

void Scene::addLight(const DrawableLight &light)
{
	lightData.push_back(light.getWorldPosition());
	lightData.push_back(light.getColor());
}

const std::vector<glm::vec3>& Scene::getLightData() const
{
		return lightData;
}

void Scene::update() {
	lightData.clear();
	Drawable::update(getTransform(), *this);
}