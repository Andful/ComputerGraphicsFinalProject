#include "scene.h"
#include "camera.h"
#include "icamera.h"

void Scene::draw(const ICamera& camera,const Scene& scene, const DrawableLight& light) const {}
void Scene::drawDepth(const ICamera& camera,const Scene& scene) const {}

Scene::Scene()
{
	has_parent = true;
	lightData = {};
}

void Scene::render(ICamera &camera) const
{
	camera.prerender();
	//render depth buffer
	this->renderDepth(camera, *this);

	//render each light in sequence.
	for(auto light : lightData)
	{
		//call parent function to start the render chain
		Drawable::render(camera, *this, *light);
	}

}

/*
 * This function just adds a light to the light vector, it still needs to be added normally too.
 * Should probably be improved at some point.
 */
void Scene::addLight(std::shared_ptr<DrawableLight> light)
{
	lightData.push_back(light);
}

const std::vector<std::shared_ptr<DrawableLight>>& Scene::getLightData() const
{
		return lightData;
}

void Scene::update() {
	//lightData.clear();
	Drawable::update(getTransform(), *this);
}