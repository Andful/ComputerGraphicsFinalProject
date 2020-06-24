//
// Created by erik on 6/24/20.
//

#include "LightCamera.h"


void LightCamera::prerender(){}

glm::mat4 LightCamera::getProjectionMatrix() const
{
	return glm::perspective(glm::radians(80.0f), 1.0f, 0.1f, 30.0f);
}