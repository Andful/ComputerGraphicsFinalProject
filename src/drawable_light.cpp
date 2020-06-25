//
// Created by erik on 6/23/20.
//

#include "drawable_light.h"

//NOLINTNEXTLINE
DrawableLight::DrawableLight(glm::vec3 color, const glm::vec3& baseTrans = glm::vec3(0,0,0))
{
	lightColor = color;
	lightCamera.push_back(std::make_shared<LightCamera>());
	this -> add(lightCamera[0]);
	this -> translate(baseTrans);

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
	return lightCamera[0]->getProjectionMatrix() * lightCamera[0]->getInverseWorldTransform();
}

void DrawableLight::update(const glm::mat4& transform, Scene& scene)
{
	Drawable::update(transform, scene);
}