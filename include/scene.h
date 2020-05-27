#pragma once

#include <memory>
#include "camera.h"
#include "Drawable.h"

class Scene
{
private:
    std::vector<std::shared_ptr<Camera>> cameras;
    std::vector<std::shared_ptr<Drawable>> drawables;

public:
    template<class ...Args>
    Scene(const Camera& camera, Args... args) : Scene(...args)
    {
        addCamera(camera);
    }
    
    template<class ...Args>
    Scene(const Drawable& drawable, Args... args) : Scene(...args)
    {
        addDrawable(drawable);
    }

    template<class DRAWABLE>
    void addDrawable(const DRAWABLE& drawable)
    {
        drawables.push_back(std::shared_ptr<Drawable>(new DRAWABLE(drawable)));
    }

    template<class CAMERA>
    void addCamera(const CAMERA& camera)
    {
        cameras.push_back(std::shared_ptr<CAMERA>(new CAMERA(camera)));
    }

    void render();
};