#include "scene.h"

Scene::Scene()
{
	lights = {};
    objects = {};
    root = create<Group>();
}

size_t Scene::size() const
{
    return objects.size();
}

void Scene::add(const std::shared_ptr<Drawable>& drawable)
{
    root -> add(drawable);
}