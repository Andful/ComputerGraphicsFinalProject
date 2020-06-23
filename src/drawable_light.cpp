//
// Created by erik on 6/23/20.
//

#include "drawable_light.h"

DrawableLight::DrawableLight(const glm::vec3& color)
{
	lightColor = color;
}

DrawableLight::DrawableLight(const glm::vec3& color, const glm::vec3& baseTrans)
{
	lightColor = color;
	this -> translate(baseTrans);
}