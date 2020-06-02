//
// Created by erik on 5/25/20.
//

#include <iostream>
#include <glm/glm.hpp>
#include <glm/gtx/euler_angles.hpp> 
#include <GL/glew.h>

#include "camera.h"

void Camera::mouseRotate(double degx, double degy)
{
	rotate(glm::vec3(-sensitivity*degy , 0 ,-sensitivity*degx));
}

void Camera::prerender()
{
            glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
            glEnable(GL_DEPTH_TEST);
}

glm::mat4 Camera::getProjectionMatrix()
{
	return glm::perspective(glm::radians(80.0f), 1.0f, 0.1f, 30.0f);
}