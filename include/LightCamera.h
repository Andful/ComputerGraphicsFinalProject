#pragma once
#include "prospective_camera.h"
#include <glm/glm.hpp>
#include <GL/glew.h>
#include <cstdio>

class LightCamera : public ProspectiveCamera
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

