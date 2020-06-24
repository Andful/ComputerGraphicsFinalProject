#include "scene.h"
#include "camera.h"
#include "icamera.h"
#include "drawable_light.h"


void Scene::draw(const ICamera& camera,const Scene& scene, const DrawableLight& light) const {}
void Scene::drawDepth(const ICamera& camera,const Scene& scene) const {}

Scene::Scene()
{
	has_parent = true;
	lightData = {};
}

void Scene::render(ICamera &camera) const
{
	camera.prerender();
	//render depth buffer
	glDepthMask(GL_TRUE);
	glDepthFunc(GL_LEQUAL);
	glColorMask(GL_FALSE,GL_FALSE, GL_FALSE, GL_FALSE);
	this->renderDepth(camera, *this);

	//render each light in sequence.
	for(const auto &light : lightData)
	{
		glBindFramebuffer(GL_FRAMEBUFFER, light->getFrameBuffer());
		glClearDepth(1.0);
		glClear(GL_DEPTH_BUFFER_BIT);
		glEnable(GL_DEPTH_TEST);
		Drawable::renderShadow(*this, *light);
		glBindFramebuffer(GL_FRAMEBUFFER, 0);

		//call parent function to start the render chain
		glColorMask(GL_TRUE, GL_TRUE, GL_TRUE, GL_TRUE); // Enable color writes.
		glDepthMask(GL_FALSE); // Disable depth writes.
		glDepthFunc(GL_EQUAL); // Only draw a pixel if it's depth matches the value stored in the depth buffer.
		glEnable(GL_BLEND); // Enable blending.
		glBlendFunc(GL_SRC_ALPHA, GL_ONE); // Additive blending.
		Drawable::render(camera, *this, *light);
		glDepthFunc(GL_LEQUAL);
		glDepthMask(GL_TRUE);
		glDisable(GL_BLEND);
	}

}

/*
 * This function just adds a light to the light vector, it still needs to be added normally too.
 * Should probably be improved at some point.
 */
void Scene::addLight(std::shared_ptr<DrawableLight> light)
{
	lightData.push_back(light);
}

const std::vector<std::shared_ptr<DrawableLight>>& Scene::getLightData() const
{
		return lightData;
}

void Scene::update() {
	//lightData.clear();
	Drawable::update(getTransform(), *this);
}