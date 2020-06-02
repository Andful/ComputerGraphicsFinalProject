//
// Created by erik on 5/25/20.
//
#pragma once

#include "disable_all_warnings.h"

#include<glm/glm.hpp>
#include "icamera.h"

class ICamera;

class Camera : public ICamera
{
private:
	double sensitivity = 0.005;
	float movementMul = 0.1f; 
public:
	void updateViewMatrix();
	void mouseRotate(double, double);
	glm::mat4 getProjectionMatrix();
	void prerender();
};