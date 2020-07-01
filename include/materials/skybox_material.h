#pragma once
#include "util3D/material.h"
#include "gl/shader_stage.h"
#include "gl/cube_texture.h"

class SkyboxMaterial : public Material {
private:
	FragmentShader fragment_shader, xray_shader, xray_cull_shader;
	std::shared_ptr<CubeTexture> texture, toonTexture;
public:
	SkyboxMaterial(std::shared_ptr<CubeTexture> tex, std::shared_ptr<CubeTexture> toonTex);
	const FragmentShader& getFragmentShader() override;
	const FragmentShader& getXrayCullShader() override;
	const FragmentShader& getXrayShader() override;
	const void* getUniformData() const override;
	GLsizeiptr getUniformDataSize() const override;
	void draw(const Scene& scene, const Geometry& geometry) const override;
	void bind() const override;
};