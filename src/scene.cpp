#include "scene.h"
#include "camera.h"
#include "icamera.h"
#include "drawable_light.h"


void Scene::draw(const Camera& camera,const Scene& scene, const DrawableLight& light) const {}
void Scene::drawDepth(const Camera& camera,const Scene& scene) const {}

Scene::Scene(int width, int height)
{
	has_parent = true;
	lightData = {};
	TEX_WIDTH = width;
	TEX_HEIGHT = height;
	for(int i = 0; i < 2; i++)
	{
		glCreateTextures(GL_TEXTURE_2D, 1, &depthtextures[i]);
		glTextureStorage2D(depthtextures[i], 1, GL_DEPTH_COMPONENT32F, TEX_WIDTH, TEX_HEIGHT);
		// Set behaviour for when texture coordinates are outside the [0, 1] range.
		glTextureParameteri(depthtextures[i], GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTextureParameteri(depthtextures[i], GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		glTextureParameteri(depthtextures[i], GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTextureParameteri(depthtextures[i], GL_TEXTURE_MAG_FILTER, GL_NEAREST);

		glCreateTextures(GL_TEXTURE_2D, 1, &colortextures[i]);
		glTextureStorage2D(colortextures[i], 1, GL_RGBA8, TEX_WIDTH, TEX_HEIGHT);
		// Set behaviour for when texture coordinates are outside the [0, 1] range.
		glTextureParameteri(colortextures[i], GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTextureParameteri(colortextures[i], GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		glTextureParameteri(colortextures[i], GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTextureParameteri(colortextures[i], GL_TEXTURE_MAG_FILTER, GL_NEAREST);


		glCreateFramebuffers(1, &framebuffers[i]);
		glNamedFramebufferTexture(framebuffers[i], GL_DEPTH_ATTACHMENT, depthtextures[i], 0);
		glNamedFramebufferTexture(framebuffers[i], GL_COLOR_ATTACHMENT0, colortextures[i], 0);
	}
	//???
	glCreateBuffers(1, &ibo);
	glNamedBufferStorage(ibo, static_cast<GLsizeiptr>(6 * sizeof(int)), &quadTriList, 0);

	glCreateBuffers(1, &vbo);
	//i have absolutely no idea why this doesn't work if the size is 12 instead of 13.  it should work, there is no reason i need that extra space.
	//yet with a size of 12, it will render one triangle only.
	glNamedBufferStorage(vbo, static_cast<GLsizeiptr>(13 * sizeof(float)), &quadVerts, 0);

	glCreateVertexArrays(1, &vao);

	glVertexArrayElementBuffer(vao, ibo);
	glVertexArrayVertexBuffer(vao, 0, vbo, 0, sizeof(float) * 3);
	glEnableVertexArrayAttrib(vao, 0);



}

void Scene::render(Camera &camera) const
{
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);

	//clear the framebuffers
	for(GLuint framebuffer : framebuffers)
	{
		glBindFramebuffer(GL_FRAMEBUFFER, framebuffer);
		camera.prerender();
	}

	if(this->useXRay)
	{
		//render depth buffer
		glBindFramebuffer(GL_FRAMEBUFFER, camera.getFramebuffer());
		glDepthMask(GL_TRUE);
		glDepthFunc(GL_LEQUAL);
		glColorMask(GL_FALSE,GL_FALSE, GL_FALSE, GL_FALSE);
		glClearDepth(1.0);
		glClear(GL_DEPTH_BUFFER_BIT);
		this->renderDepth(camera, *this);


		glColorMask(GL_FALSE,GL_FALSE, GL_FALSE, GL_FALSE);
		glDepthMask(GL_TRUE);
		glDepthFunc(GL_LEQUAL);
		glBindFramebuffer(GL_FRAMEBUFFER, framebuffers[0]);
		glClearDepth(1.0);
		glClear(GL_DEPTH_BUFFER_BIT);
		this->xRayCull(camera, *this);
	}
	else
	{
		//render depth buffer
		glDepthMask(GL_TRUE);
		glDepthFunc(GL_LEQUAL);
		glColorMask(GL_FALSE,GL_FALSE, GL_FALSE, GL_FALSE);
		glBindFramebuffer(GL_FRAMEBUFFER, framebuffers[0]);
		glClearDepth(1.0);
		glClear(GL_DEPTH_BUFFER_BIT);
		this->renderDepth(camera, *this);
	}

	//this->renderShadow(*this, Camera)

	//render each light in sequence.
	for(const auto &light : lightData)
	{
		glBindFramebuffer(GL_FRAMEBUFFER, light->getFrameBuffer());
		glClearDepth(1.0);
		glClear(GL_DEPTH_BUFFER_BIT);
		glEnable(GL_DEPTH_TEST);
		glViewport(0, 0, light->getWidth(), light->getHeight());
		Drawable::renderShadow(*this, *light);
		glBindFramebuffer(GL_FRAMEBUFFER, framebuffers[0]);

		glViewport(0, 0, camera.getWidth(), camera.getHeight());
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

	glDisable(GL_CULL_FACE);
	//postfx time!
	glBindVertexArray(vao);
	glActiveTexture(GL_TEXTURE1);
	glColorMask(GL_TRUE, GL_TRUE, GL_TRUE, GL_TRUE);
	glDisable(GL_DEPTH_TEST);
	//these should all be screen sized so let's not change the viewport constantly.
	glViewport(0, 0, TEX_WIDTH, TEX_HEIGHT);
	unsigned int i = 0;
	for(; i < postShaders.size() -1; i++)
	{
		glBindFramebuffer(GL_FRAMEBUFFER, framebuffers[(i+1)%2]);
		postShaders[i]->bind();
		glBindTexture(GL_TEXTURE_2D, colortextures[i%2]);
		glUniform1i(0, 1);
		glUniform2fv(1, 1, glm::value_ptr(glm::vec2(TEX_WIDTH, TEX_HEIGHT)));
		glUniform1i(2, samples);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);
	}

	glBindFramebuffer(GL_FRAMEBUFFER, 0);
	postShaders[i]->bind();
	glBindTexture(GL_TEXTURE_2D, colortextures[i % 2]);
	glUniform1i(0, 1);
	glUniform2fv(1, 1, glm::value_ptr(glm::vec2(TEX_WIDTH, TEX_HEIGHT)));
	glUniform1i(2, samples);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);
}

/*
 * This function just adds a light to the light vector, it still needs to be added normally too.
 * Should probably be improved at some point.
 */
void Scene::addLight(const std::shared_ptr<DrawableLight>& light)
{
	lightData.push_back(light);
}

const std::vector<std::shared_ptr<DrawableLight>>& Scene::getLightData() const
{
		return lightData;
}

void Scene::update()
{
	Drawable::update(getTransform(), *this);
}

void Scene::toggleXRay() {useXRay = !useXRay;}

void Scene::addPostShader(const std::shared_ptr<Shader> &shader)
{
	postShaders.push_back(shader);
}