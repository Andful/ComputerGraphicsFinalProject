#pragma once
#include "icamera.h"
#include <glm/glm.hpp>
#include <GL/glew.h>
#include <cstdio>

class ICamera;

class LightCamera : public ICamera
{
	friend DrawableLight;
protected:
	GLuint texShadow, framebuffer;
	int TEX_WIDTH;
	int TEX_HEIGHT;
public:
	LightCamera(int, int);
	glm::mat4 getProjectionMatrix() const;

	GLuint getTexShadow() const;

	GLuint getFramebuffer() const;
};

