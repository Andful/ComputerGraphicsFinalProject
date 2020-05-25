//
// Created by erik on 5/25/20.
//

#include "camera.h"
#include <iostream>
Camera::Camera(glm::vec3 pos, glm::vec3 upwards, double _pitch, double _yaw) :
		m_viewMatrix(0.f),
		eye(pos), up(upwards),
		center(0.f)
{
	pitch = glm::radians(_pitch);
	yaw = glm::radians(_yaw);
	m_viewMatrix = glm::lookAt(eye, calculateDir(pitch, yaw) + eye, up);
}

Camera::~Camera() = default;

void Camera::updateViewMatrix() {
	m_viewMatrix = glm::lookAt(eye, center, up);
}

void Camera::setEye(glm::vec3 newEye) { eye = newEye; updateViewMatrix();}
void Camera::setCenter(glm::vec3 newCenter) { center = newCenter; updateViewMatrix(); }
void Camera::setUp(glm::vec3 newUp) { up = newUp; updateViewMatrix(); }



void Camera::mouseRotate(double degx, double degy)
{
	//clamp this value so we don't have to deal with the camera going upside down (really you don't need that anyway)
	//the clamp values are sliiiiightly under 90 degrees in radians
	pitch = glm::clamp(pitch + glm::radians(degy * sensitivity), -1.57078, 1.57078);
	yaw += glm::radians(degx * sensitivity);
	std::cout << pitch << std::endl;
	setCenter( calculateDir(pitch, yaw)+ eye);
}