//
// Created by erik on 5/25/20.
//

#include <iostream>
#include <glm/glm.hpp>
#include <glm/gtx/euler_angles.hpp> 
#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "prospective_camera.h"
#include "util3D/mesh.h"
#include "util3D/material.h"
#include "materials/skybox_material.h"
#include "util3D/geometry.h"

ProspectiveCamera::ProspectiveCamera() : quad("resources/quad.obj")
{
	prospectiveMatrix = glm::perspective(glm::radians(80.0f), 1.0f, 0.1f, 300.0f);
	//generate depthmap for framebuffer
	for (int i = 0; i < 2; i++)
	{
		depthTexture[i] = Texture(1024, 1024, GL_DEPTH_COMPONENT32F);
		depthTexture[i].set(GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		depthTexture[i].set(GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		depthTexture[i].set(GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		depthTexture[i].set(GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		depthTexture[i].set(GL_TEXTURE_COMPARE_MODE, GL_COMPARE_REF_TO_TEXTURE);
		depthTexture[i].set(GL_TEXTURE_COMPARE_FUNC, GL_LEQUAL);
		framebuffer[i] = Framebuffer(depthTexture[i], GL_DEPTH_ATTACHMENT);

		//generate color portion of framebuffer
		colorTexture[i] = Texture(1024, 1024, GL_RGBA8);
		colorTexture[i].set(GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		colorTexture[i].set(GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		colorTexture[i].set(GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		colorTexture[i].set(GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		framebuffer[i].addAttachment(colorTexture[i], GL_COLOR_ATTACHMENT0);
	}
}

void ProspectiveCamera::mouseRotate(double degx, double degy)
{
	rotate(glm::vec3(-sensitivity*degy , 0 ,-sensitivity*degx));
}

void ProspectiveCamera::prerender() {

	//clear all buffers we're going to use
	clearAllBuffers();
   glViewport(0, 0, 1024, 1024);
   framebuffer[targetBuffer].bind();
   glEnable(GL_DEPTH_TEST);
   glDepthMask(GL_TRUE);
	glDepthFunc(GL_LEQUAL);
	glColorMask(GL_FALSE,GL_FALSE, GL_FALSE, GL_FALSE);
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);
   bindCamera();
   const Scene& _scene = getScene();
   for(const std::shared_ptr<Mesh> mesh : _scene.getMeshes()) {
      mesh -> getDepthShader().bind();
      mesh -> bind();
      mesh -> getGeometry().bind();
      mesh -> getGeometry().draw();
   }
   if (useXRay)
   {
	   flipBuffers();
	   framebuffer[targetBuffer].bind();
	  // printf("%u\n", sourceBuffer);
	   for (const std::shared_ptr<Mesh> mesh : _scene.getMeshes()) {
		   mesh->getXrayCullShader().bind();
		   mesh->bind();
		   mesh->getGeometry().bind();

		   //somewhere along the way this was getting dropped so this has to be down here for now
		   depthTexture[sourceBuffer].bind(1);
		   glUniform1i(3, 1);
		   
		   mesh->getGeometry().draw();
	   }
   }
	//this->renderMesh(_scene, *skybox);
    glViewport(0, 0, 1024, 1024);
}

void ProspectiveCamera::renderMesh(const Scene& _scene, const Mesh& mesh) const
{
	if (useXRay)
	{
		mesh.getXrayShader().bind();
	}
	else mesh.getShader().bind();
   mesh.bind();
   mesh.getGeometry().bind();
   mesh.getMaterial().bind();
   mesh.getMaterial().draw(_scene, mesh.getGeometry());
}

const glm::mat4& ProspectiveCamera::getProjectionMatrix() const
{
	return prospectiveMatrix;
}

void ProspectiveCamera::postrender() {
	//From this point on we will render some quads in screen space so we don't want any culling or depth tests to occur
	glDisable(GL_CULL_FACE);
	glDisable(GL_DEPTH_TEST);
	glColorMask(GL_TRUE, GL_TRUE, GL_TRUE, GL_TRUE);
	glDepthMask(GL_TRUE);
	glDisable(GL_BLEND);

	//this is temporary until I implement the full postfx path
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
	flipBuffers();
	colorTexture[sourceBuffer].bind(1);
	depthTexture[sourceBuffer].bind(2);
	postFxShaders[0]->bind();
	quad.bind();
	glUniform1i(0, 1);
	glUniform1i(2, 2);
	glUniform2fv(1, 1, glm::value_ptr(glm::vec2(1024, 1024)));
	quad.draw();
}

void ProspectiveCamera::addPostShader(std::shared_ptr<Shader> shader)
{
	postFxShaders.push_back(shader);
}

void ProspectiveCamera::flipBuffers()
{
	//flip the target and source
	targetBuffer ^= 1UL << 0;
	sourceBuffer ^= 1UL << 0;
}

void ProspectiveCamera::clearAllBuffers()
{
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
	glClearColor(0.f, 0.f, 0.f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	for (Framebuffer buf : framebuffer) {
		buf.bind();
		glClearColor(0.f, 0.f, 0.f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}
}

void ProspectiveCamera::toggleXRay()
{
	useXRay = !useXRay;
}