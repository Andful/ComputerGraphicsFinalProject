//
// Created by erik on 5/25/20.
//
#pragma once

#include "disable_all_warnings.h"

#include<glm/glm.hpp>
#include "util3D/camera.h"
#include "gl/framebuffer.h"
#include "gl/texture.h"
#include "util3D/basic_geometry.h"

class Camera;

class ProspectiveCamera : public Camera
{
private:
	BasicGeometry quad;
	std::vector<std::shared_ptr<Shader>> postFxShaders = {};
	double sensitivity = 0.005;
	float movementMul = 0.1f;
	glm::mat4 prospectiveMatrix;
	Framebuffer framebuffer;
	Texture texture, colorTexture;
public:
	ProspectiveCamera();
	void updateViewMatrix();
	void mouseRotate(double, double);
	const glm::mat4& getProjectionMatrix() const;
	void prerender();
	void renderMesh(const Scene& scene, const Mesh& mesh) const override;
	void postrender() override;
	void addPostShader(std::shared_ptr<Shader> shader);
};