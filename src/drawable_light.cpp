//
// Created by erik on 6/23/20.
//

#include "drawable_light.h"


//NOLINTNEXTLINE
DrawableLight::DrawableLight(glm::vec3 color, const glm::vec3& baseTrans = glm::vec3(0,0,0)) : lightCamera()
{
	lightColor = color;
	this -> translate(baseTrans);

	//below here we will create the shadow map texture.
	glCreateTextures(GL_TEXTURE_2D, 1, &texShadow);
	glTextureStorage2D(texShadow, 1, GL_DEPTH_COMPONENT32F, TEX_WIDTH, TEX_HEIGHT);
	// Set behaviour for when texture coordinates are outside the [0, 1] range.
	glTextureParameteri(texShadow, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTextureParameteri(texShadow, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

	// Set interpolation for texture sampling (GL_NEAREST for no interpolation).
	glTextureParameteri(texShadow, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTextureParameteri(texShadow, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glCreateFramebuffers(1, &framebuffer);
	glNamedFramebufferTexture(framebuffer, GL_DEPTH_ATTACHMENT, texShadow, 0);
}

void DrawableLight::draw(const ICamera& camera, const Scene& scene, const DrawableLight& light) const {}
void DrawableLight::drawDepth(const ICamera &projection, const Scene &scene) const {}

const glm::vec3& DrawableLight::getColor() const
{
	return lightColor;
}

GLuint DrawableLight::getTexShadow() const {return texShadow;}
GLuint DrawableLight::getFrameBuffer() const {return framebuffer;}

glm::mat4 DrawableLight::getCameraMVP() const
{
	return lightCamera.getProjectionMatrix() * lightCamera.getInverseWorldTransform() * world_transform;
}

void DrawableLight::update(const glm::mat4& transform, Scene& scene)
{
	Drawable::update(transform, scene);
}