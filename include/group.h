#pragma once
#include "drawable.h"
#include <glm/glm.hpp>


class Group : public Drawable
{
public:
    void draw(const ICamera&, const Scene& scene, const DrawableLight &light) const;

	void drawDepth(const ICamera &projection, const Scene &scene) const;
};