#include "scene.h"
#include "camera.h"
Scene::Scene()
{
	lights = {};
    objects = {};
    root = create<Group>();
    camera = nullptr;
}

size_t Scene::size() const
{
    return objects.size();
}

void Scene::add(const std::shared_ptr<Drawable>& drawable)
{
    root -> add(drawable);
}
void Scene::addCamera(const std::shared_ptr<Camera> &cam)
{
	camera = cam;
	add(cam);
}
void Scene::addLight(const std::shared_ptr<DrawableLight> &light)
{
	lights.push_back(light);
}

std::vector<std::shared_ptr<DrawableLight>>& Scene::getLights()
{
		return lights;
}

std::shared_ptr<Camera> Scene::getCamera()
{
	return camera;
}

const float *Scene::getCameraPos()
{
	return glm::value_ptr(camera->getTranslation());
}