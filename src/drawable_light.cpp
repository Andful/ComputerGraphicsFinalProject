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

void DrawableLight::draw(const ICamera& camera, const Scene& scene) const {}


const glm::vec3& DrawableLight::getColor() const
{
	return lightColor;
}

void DrawableLight::update(const glm::mat4& transform, Scene& scene)
{
	Drawable::update(transform, scene);
	scene.addLight(*this);
}