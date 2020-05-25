//
// Created by erik on 5/25/20.
//

#include "camera.h"

Camera::Camera() =default;

Camera::~Camera() = default;

void Camera::updateViewMatrix() {
	m_viewMatrix = glm::lookAt(eye, center, up);
}

void Camera::setEye(glm::vec3 newEye) { eye = newEye; updateViewMatrix();}
void Camera::setCenter(glm::vec3 newCenter) { center = newCenter; updateViewMatrix(); }
void Camera::setUp(glm::vec3 newUp) { up = newUp; updateViewMatrix(); }

void Camera::mouseRotate(float degx, float degy)
{
	//m_viewMatrix = (glm::rotate(glm::rotate(m_viewMatrix, glm::radians(degx), glm::vec3(1, 0, 0)), glm::radians(degy), glm::vec3(0, 1, 0)));
}

/*void Camera::rotateCamera(glm::vec3 &axis, float rotation_deg)
{
	m_viewMatrix = glm::rotate(m_viewMatrix, )
}*/