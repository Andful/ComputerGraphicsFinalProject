#pragma once
#include <memory>
#include <glm/glm.hpp>
#include <GL/glew.h>
#include "gl/shader_stage.h"
#include "util3D/material.h"

class FragmentShader;

typedef struct alignas(16) _GroundMaterialUnifromData{
	glm::vec3 ks;
	float shininess;
	glm::vec3 kd;
} GroundMaterialUnifromData;

class GroundMaterial : public Material {
private:
	GroundMaterialUnifromData ground_material_uniform;
	FragmentShader fragment_shader, xray_shader, xray_cull_shader;
	std::shared_ptr<Texture> texture, toonTexture;
public:
	GroundMaterial(glm::vec3 ks, float shininess, glm::vec3 kd, std::shared_ptr<Texture> tex, std::shared_ptr<Texture> toonTex);
	const FragmentShader& getFragmentShader() override;
	const FragmentShader& getXrayCullShader() override;
	const FragmentShader& getXrayShader() override;
	const void* getUniformData() const override;
	GLsizeiptr getUniformDataSize() const override;
	void draw(const Scene& scene, const Geometry& geometry) const override;
	void bind() const override;
};