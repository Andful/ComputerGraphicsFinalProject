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
}

void ProspectiveCamera::mouseRotate(double degx, double degy)
{
	rotate(glm::vec3(-sensitivity*degy , 0 ,-sensitivity*degx));
}

void ProspectiveCamera::prerender() {
   glViewport(0, 0, 1024, 1024);
   glColorMask(GL_TRUE, GL_TRUE, GL_TRUE, GL_TRUE);
   glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
   glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
   glEnable(GL_DEPTH_TEST);
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