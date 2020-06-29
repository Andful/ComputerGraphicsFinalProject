//
// Created by erik on 5/25/20.
//
#pragma once

#include "disable_all_warnings.h"

#include<glm/glm.hpp>
#include "util3D/camera.h"

class Camera;

class ProspectiveCamera : public Camera
{
private:
	double sensitivity = 0.005;
	float movementMul = 0.1f;
	glm::mat4 prospectiveMatrix;
public:
	ProspectiveCamera();
	void updateViewMatrix();
	void mouseRotate(double, double);
	const glm::mat4& getProjectionMatrix() const;
	void prerender();
	void renderMesh(const Scene& scene, const Mesh& mesh) const override;
};