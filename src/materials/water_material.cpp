#include "materials/water_material.h"
#include "util3D/geometry.h"

WaterMaterial::WaterMaterial(glm::vec3 ks, float shininess, glm::vec3 kd, std::shared_ptr<Texture> _tex, std::shared_ptr<Texture> _toonTex)
{
	fragment_shader = FragmentShader("shaders/water.frag.glsl");
	xray_shader = FragmentShader("shaders/xtoon.frag.glsl");
	xray_cull_shader = FragmentShader("shaders/xray.frag.glsl");
	water_material_uniform.ks = ks;
	water_material_uniform.shininess = shininess;
	water_material_uniform.kd = kd;
	initUniformBuffer();
	texture = _tex;
	toonTexture = _toonTex;
}

const FragmentShader& WaterMaterial::getFragmentShader() {
	return fragment_shader;
}

const FragmentShader& WaterMaterial::getXrayCullShader() {
	return xray_cull_shader;
}

const FragmentShader& WaterMaterial::getXrayShader() {
	return xray_shader;
}

const void* WaterMaterial::getUniformData() const {
	return static_cast<const void*>(&water_material_uniform);
}

GLsizeiptr WaterMaterial::getUniformDataSize() const {
	return sizeof(WaterMaterialUniformData);
}

void WaterMaterial::draw(const Scene& scene, const Geometry& geometry) const {
	//glViewport(0, 0, 1024, 500);
	//call parent function to start the render chain
	glColorMask(GL_TRUE, GL_TRUE, GL_TRUE, GL_TRUE); // Enable color writes.
	glDepthMask(GL_FALSE); // Disable depth writes.
	glDepthFunc(GL_EQUAL); // Only draw a pixel if it's depth matches the value stored in the depth buffer.
	glDisable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE); // Additive blending.
	for(std::shared_ptr<Light> light : scene.getLights()) {
		light -> bind();
		geometry.draw();
	}
	geometry.draw();
	glDepthFunc(GL_LEQUAL);
	glDepthMask(GL_TRUE);
	glDisable(GL_BLEND);
}

void WaterMaterial::bind() const {
	Material::bind();
	texture->bind(4);
	glUniform1i(4, 4);
	toonTexture->bind(5);
	glUniform1i(5, 5);
}
