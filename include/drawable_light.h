#pragma once

#include "drawable.h"
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

class DrawableLight : public Drawable {
private:
	glm::vec3 lightColor{};
public:
	explicit DrawableLight(glm::vec3 color);
	DrawableLight(glm::vec3 color, const glm::vec3& baseTrans);
	const float *getColor();
	void draw(const glm::mat4& projection, const glm::mat4& transform);
};