//
// Created by erik on 6/23/20.
//

#include "drawable_light.h"


DrawableLight::DrawableLight(glm::vec3 color)
{
	lightColor = color;
}

DrawableLight::DrawableLight(glm::vec3 color, const glm::vec3& baseTrans)
{
	lightColor = color;
	this -> translate(baseTrans);
}

void DrawableLight::draw(const glm::mat4& projection, const glm::mat4& transform){}


const float *DrawableLight::getColor()
{
	return glm::value_ptr(lightColor);
}