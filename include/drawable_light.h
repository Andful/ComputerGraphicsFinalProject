#pragma once

#include "drawable_light.h"
#include "drawable.h"
#include "camera.h"

class DrawableLight : public Drawable {
private:
	glm::vec3 lightColor;
public:
	DrawableLight(const glm::vec3& color);
	DrawableLight(const glm::vec3& color, const glm::vec3& baseTrans);
};