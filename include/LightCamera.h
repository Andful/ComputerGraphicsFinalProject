#pragma once
#include "prospective_camera.h"
#include <glm/glm.hpp>
#include <GL/glew.h>
#include <cstdio>

class LightCamera : public ProspectiveCamera
{
public:
	glm::mat4 getProjectionMatrix() const;
};