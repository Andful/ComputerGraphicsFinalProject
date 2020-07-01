#include "util3D/scene.h"
#include "util3D/camera.h"
#include "util3D/light.h"
#include "util3D/directional_light.h"

#include "prospective_camera.h"

Scene::Scene()
{
	scene = this;
	lights = {};
	meshes = {};
}

const std::vector<std::shared_ptr<Light>>& Scene::getLights() const {
		return lights;
}

const std::vector<std::shared_ptr<Mesh>>& Scene::getMeshes() const {
		return meshes;
}

void Scene::update() {
	Transformable::update(getTransform());
	for(const std::shared_ptr<DirectionalLight>& light : directional_lights) {
		light->render();
	}
}