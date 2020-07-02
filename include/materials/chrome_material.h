#pragma once

#include <memory>
#include <glm/glm.hpp>
#include <GL/glew.h>
#include "gl/shader_stage.h"
#include "gl/cube_texture.h"
#include "util3D/material.h"

class FragmentShader;

class ChromeMaterial : public Material {
private:
	FragmentShader fragment_shader, xray_shader, xray_cull_shader;
	std::shared_ptr<Texture> texture, toonTexture;
public:
	ChromeMaterial(std::shared_ptr<CubeTexture> tex, std::shared_ptr<Texture> toonTex);
	const FragmentShader& getFragmentShader() override;
	const FragmentShader& getXrayCullShader() override;
	const FragmentShader& getXrayShader() override;
	const void* getUniformData() const override;
	GLsizeiptr getUniformDataSize() const override;
	void draw(const Scene& scene, const Geometry& geometry) const override;
	void bind() const override;
};