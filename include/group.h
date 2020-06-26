#pragma once
#include "drawable.h"
#include <glm/glm.hpp>


class Group : public Drawable
{
public:
    void draw(const Camera&, const Scene& scene, const DrawableLight &light) const;

	void drawDepth(const Camera &projection, const Scene &scene) const;
};