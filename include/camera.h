//
// Created by erik on 5/25/20.
//
#pragma once

//#include "disable_all_warnings.h"

#include<glm/glm.hpp>
#include "LightCamera.h"

class Camera : public LightCamera {
private:
	double sensitivity = 0.005;
	float movementMul = 0.1f; 
public:
	Camera(int, int);
	void updateViewMatrix();
	void mouseRotate(double, double);
	glm::mat4 getProjectionMatrix() const;
	void prerender();
	int getWidth() const;
	int getHeight() const ;
};