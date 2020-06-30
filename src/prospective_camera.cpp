//
// Created by erik on 5/25/20.
//

#include <iostream>
#include <glm/glm.hpp>
#include <glm/gtx/euler_angles.hpp> 
#include <GL/glew.h>

#include "prospective_camera.h"
#include "util3D/mesh.h"
#include "util3D/material.h"
#include "util3D/geometry.h"

ProspectiveCamera::ProspectiveCamera()
{
	prospectiveMatrix = glm::perspective(glm::radians(80.0f), 1.0f, 0.1f, 30.0f);
   texture = Texture(1024, 1024, GL_DEPTH_COMPONENT32F);
   texture.set(GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
   texture.set(GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	texture.set(GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	texture.set(GL_TEXTURE_MAG_FILTER, GL_NEAREST);
   framebuffer = Framebuffer(texture, GL_DEPTH_ATTACHMENT);
}

void ProspectiveCamera::mouseRotate(double degx, double degy)
{
	rotate(glm::vec3(-sensitivity*degy , 0 ,-sensitivity*degx));
}

void ProspectiveCamera::prerender() {
   glViewport(0, 0, 1024, 1024);
   glClearColor(0.f,0.f,0.f, 1.0f);
   glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
   glEnable(GL_DEPTH_TEST);
   glDepthMask(GL_TRUE);
	glDepthFunc(GL_LEQUAL);
	glColorMask(GL_FALSE,GL_FALSE, GL_FALSE, GL_FALSE);
   bindCamera();
   const Scene& _scene = getScene();
   for(const std::shared_ptr<Mesh> mesh : _scene.getMeshes()) {
      mesh -> getDepthShader().bind();
      mesh -> bind();
      mesh -> getGeometry().bind();
      mesh -> getGeometry().draw();
   }

   glViewport(0, 0, 1024, 1024);
	//call parent function to start the render chain
	glColorMask(GL_TRUE, GL_TRUE, GL_TRUE, GL_TRUE); // Enable color writes.
	glDepthMask(GL_FALSE); // Disable depth writes.
	glDepthFunc(GL_EQUAL); // Only draw a pixel if it's depth matches the value stored in the depth buffer.
	glEnable(GL_BLEND); // Enable blending.
	glBlendFunc(GL_SRC_ALPHA, GL_ONE); // Additive blending.
}

void ProspectiveCamera::renderMesh(const Scene& _scene, const Mesh& mesh) const
{
   mesh.getShader().bind();
   mesh.bind();
   mesh.getMaterial().bind();
   mesh.getGeometry().bind();
   mesh.getMaterial().draw(_scene, mesh.getGeometry());
}

const glm::mat4& ProspectiveCamera::getProjectionMatrix() const
{
	return prospectiveMatrix;
}

void ProspectiveCamera::postrender() {
	glDepthFunc(GL_LEQUAL);
	glDepthMask(GL_TRUE);
	glDisable(GL_BLEND);
}