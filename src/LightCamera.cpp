//
// Created by erik on 6/24/20.
//

#include "LightCamera.h"

LightCamera::LightCamera(int TexW, int TexH)
{
	//TODO define destructor for the texture
	TEX_WIDTH = TexW;
	TEX_HEIGHT = TexH;
	//below here we will create the shadow map texture.
	glCreateTextures(GL_TEXTURE_2D, 1, &texShadow);
	glTextureStorage2D(texShadow, 1, GL_DEPTH_COMPONENT32F, TEX_WIDTH, TEX_HEIGHT);
	// Set behaviour for when texture coordinates are outside the [0, 1] range.
	glTextureParameteri(texShadow, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTextureParameteri(texShadow, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTextureParameteri(texShadow, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTextureParameteri(texShadow, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	//enable depth compare mode and use GL_LEQUAL comparison
	glTextureParameteri(texShadow, GL_TEXTURE_COMPARE_MODE, GL_COMPARE_REF_TO_TEXTURE);
	glTextureParameteri(texShadow, GL_TEXTURE_COMPARE_FUNC, GL_LEQUAL);

	glCreateFramebuffers(1, &framebuffer);
	glNamedFramebufferTexture(framebuffer, GL_DEPTH_ATTACHMENT, texShadow, 0);
}

glm::mat4 LightCamera::getProjectionMatrix() const
{
	return glm::perspective(glm::radians(80.0f), 1.0f, 0.1f, 30.0f);
}

GLuint LightCamera::getTexShadow() const {return texShadow;}

GLuint LightCamera::getFramebuffer() const {return framebuffer;}