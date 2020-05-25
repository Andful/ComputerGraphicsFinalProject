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
	m_viewMatrix = glm::lookAt(eye, center + eye, up);
}

void Camera::setEye(glm::vec3 newEye) { eye = newEye; updateViewMatrix();}
void Camera::setCenter(glm::vec3 newCenter) { center = newCenter; updateViewMatrix(); }
void Camera::setUp(glm::vec3 newUp) { up = newUp; updateViewMatrix(); }

void Camera::move(CAM_DIR dir)
{
	glm::vec3 direction = normalize(glm::vec3(center.x, 0, center.z));
	switch (dir){
		case CAM_F:
			break;
		case CAM_B:
			direction = -direction;
			break;
		case CAM_L:
			direction = rotate(direction, glm::radians(90.f), glm::vec3(0, 1, 0));
			break;
		case CAM_R:
			direction = rotate(direction, glm::radians(-90.f), glm::vec3(0, 1, 0));
			break;

	}
	setEye(eye + direction * movementMul);

}


void Camera::mouseRotate(double degx, double degy)
{
	//clamp this value so we don't have to deal with the camera going upside down (really you don't need that anyway)
	//the clamp values are sliiiiightly under 90 degrees in radians
	pitch = glm::clamp(pitch + glm::radians(degy * sensitivity), -1.57078, 1.57078);
	yaw += glm::radians(degx * sensitivity);
	std::cout << pitch << std::endl;
	setCenter( calculateDir(pitch, yaw));
}