#pragma once

#include <map>
#include <memory>
#include "drawable.h"
#include "group.h"
#include "drawable_light.h"

class Camera;

class Scene
{
private:
    std::vector<std::shared_ptr<Drawable>> objects;
    std::shared_ptr<Drawable> root;
    std::vector<std::shared_ptr<DrawableLight>> lights;
    std::shared_ptr<Camera> camera;

public:
    Scene();
    size_t size() const;
    std::shared_ptr<Drawable> getRoot();
    std::vector<std::shared_ptr<DrawableLight>>& getLights();
    void add(const std::shared_ptr<Drawable>& drawable);
    void addCamera(const std::shared_ptr<Camera> & cam);
    void addLight(const std::shared_ptr<DrawableLight> &light);
    template<class DRAWABLE,class ...Args>
    std::shared_ptr<DRAWABLE> create(Args... args)
    {   
        std::shared_ptr<DRAWABLE> result = std::make_shared<DRAWABLE>(args...);
        result -> index = int(objects.size());
        result -> scene = this;
        objects.push_back(result);
        return result;
    }
    const float *getCameraPos();
	std::shared_ptr<Camera> getCamera();

    friend Drawable;
};