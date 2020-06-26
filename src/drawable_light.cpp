//
// Created by erik on 6/23/20.
//

#include "drawable_light.h"
#include "camera.h"

//NOLINTNEXTLINE
DrawableLight::DrawableLight(glm::vec3 color, const glm::vec3& baseTrans = glm::vec3(0,0,0))
{
	lightColor = color;
	lightCamera.push_back(std::make_shared<LightCamera>(4096,4096));
	this -> add(lightCamera[0]);
	this -> translate(baseTrans);


}

void DrawableLight::draw(const Camera& camera, const Scene& scene, const DrawableLight& light) const {}
void DrawableLight::drawDepth(const Camera &projection, const Scene &scene) const {}

const glm::vec3& DrawableLight::getColor() const
{
	return lightColor;
}

GLuint DrawableLight::getTexShadow() const {return lightCamera[0]->getTexShadow();}
GLuint DrawableLight::getFrameBuffer() const {return lightCamera[0]->getFramebuffer();}

glm::mat4 DrawableLight::getCameraMVP() const
{
	return lightCamera[0]->getProjectionMatrix() * lightCamera[0]->getInverseWorldTransform();
}

void DrawableLight::update(const glm::mat4& transform, Scene& scene)
{
	Drawable::update(transform, scene);
}

int DrawableLight::getWidth(){return lightCamera[0]->TEX_WIDTH;}
int DrawableLight::getHeight() {return lightCamera[0]->TEX_HEIGHT;}