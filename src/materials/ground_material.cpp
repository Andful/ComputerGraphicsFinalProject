#include "materials/ground_material.h"

#include "materials/water_material.h"
#include "util3D/geometry.h"

GroundMaterial::GroundMaterial(glm::vec3 ks, float shininess, glm::vec3 kd, std::shared_ptr<Texture> _tex, std::shared_ptr<Texture> _toonTex)
{
	fragment_shader = FragmentShader("shaders/ground.frag.glsl");
	xray_shader = FragmentShader("shaders/xtoon.frag.glsl");
	xray_cull_shader = FragmentShader("shaders/ground.frag.glsl");
	ground_material_uniform.ks = ks;
	ground_material_uniform.shininess = shininess;
	ground_material_uniform.kd = kd;
	initUniformBuffer();
	texture = _tex;
	toonTexture = _toonTex;
}

const FragmentShader& GroundMaterial::getFragmentShader() {
	return fragment_shader;
}

const FragmentShader& GroundMaterial::getXrayCullShader() {
	return xray_cull_shader;
}

const FragmentShader& GroundMaterial::getXrayShader() {
	return xray_shader;
}

const void* GroundMaterial::getUniformData() const {
	return static_cast<const void*>(&ground_material_uniform);
}

GLsizeiptr GroundMaterial::getUniformDataSize() const {
	return sizeof(GroundMaterialUnifromData);
}

void GroundMaterial::draw(const Scene& scene, const Geometry& geometry) const {
	glColorMask(GL_TRUE, GL_TRUE, GL_TRUE, GL_TRUE); // Enable color writes.
	glDepthMask(GL_FALSE); // Disable depth writes.
	glDepthFunc(GL_EQUAL); // Only draw a pixel if it's depth matches the value stored in the depth buffer.
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE); // Additive blending.
	for(std::shared_ptr<Light> light : scene.getLights()) {
		light -> bind();
		geometry.draw();
	}
	glDepthFunc(GL_LEQUAL);
	glDepthMask(GL_TRUE);
	glDisable(GL_BLEND);
}

void GroundMaterial::bind() const {
	Material::bind();
	texture->bind(4);
	glUniform1i(4, 4);
	toonTexture->bind(5);
	glUniform1i(5, 5);
}
