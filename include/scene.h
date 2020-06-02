#pragma once

<<<<<<< HEAD
#include <map>
#include <memory>
#include "drawable.h"
#include "group.h"
=======
#include <memory>
#include "camera.h"
#include "Drawable.h"
>>>>>>> fa1109b6f083e67db6402c2f6b6f46510036cf78

class Scene
{
private:
<<<<<<< HEAD
    std::vector<std::shared_ptr<Drawable>> objects;
    std::shared_ptr<Drawable> root;

public:
    Scene();
    size_t size() const;
    std::shared_ptr<Drawable> getRoot();
    void add(const std::shared_ptr<Drawable>& drawable);
    template<class DRAWABLE,class ...Args>
    std::shared_ptr<DRAWABLE> create(Args... args)
    {   
        std::shared_ptr<DRAWABLE> result = std::make_shared<DRAWABLE>(args...);
        result -> index = int(objects.size());
        result -> scene = this;
        objects.push_back(result);
        return result;
    }

    friend Drawable;
=======
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
>>>>>>> fa1109b6f083e67db6402c2f6b6f46510036cf78
};