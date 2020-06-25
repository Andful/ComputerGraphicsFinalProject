#pragma once
#include "camera.h"
#include <glm/glm.hpp>
#include <GL/glew.h>
#include <cstdio>

class LightCamera : public Camera
{
public:
	glm::mat4 getProjectionMatrix() const;
};