#pragma once

#include <map>
#include <memory>
#include "drawable.h"
#include "group.h"

class Scene
{
private:
    std::vector<std::shared_ptr<Drawable>> objects;
    std::shared_ptr<Drawable> root;
    std::vector<std::shared_ptr <Drawable_Light>> lights;

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
};