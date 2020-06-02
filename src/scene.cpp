#include "scene.h"

<<<<<<< HEAD
Scene::Scene()
{
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
=======
Scene::render()
{
    //TODO
>>>>>>> fa1109b6f083e67db6402c2f6b6f46510036cf78
}