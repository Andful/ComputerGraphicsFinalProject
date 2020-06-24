#pragma once
#include "icamera.h"
#include <glm/glm.hpp>
#include <GL/glew.h>

class ICamera;
class DrawableLight;

class LightCamera : public ICamera
{
public:
	void prerender();
	glm::mat4 getProjectionMatrix() const;
};
