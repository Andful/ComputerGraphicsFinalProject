#pragma once

#include <map>
#include <memory>

#include "util3D/transformable.h"
#include "util3D/light.h"
#include "util3D/camera.h"
#include "util3D/mesh.h"

class Light;
class PointLight;
class DirectionalLight;
class Mesh;


class Scene: public Transformable 
{
private:
    std::vector<std::shared_ptr<DirectionalLight>> directional_lights;
    std::vector<std::shared_ptr<Light>> lights;
    std::vector<std::shared_ptr<Mesh>> meshes;

public:
    Scene();
    const std::vector<std::shared_ptr<Light>>& getLights() const;
    const std::vector<std::shared_ptr<Mesh>>& getMeshes() const;
    using Transformable::update;
    void update();
    friend Mesh;
    friend PointLight;
    friend DirectionalLight;
};