//
// Created by erik on 7/1/20.
//

#include "materials/skybox_material.h"
#include "util3D/geometry.h"

SkyboxMaterial::SkyboxMaterial(std::shared_ptr<CubeTexture> _tex, std::shared_ptr<CubeTexture> _toonTex)
{
	fragment_shader = FragmentShader("shaders/skybox.frag.glsl");
	xray_shader = FragmentShader("shaders/skybox.frag.glsl");
	xray_cull_shader = FragmentShader("shaders/skybox.frag.glsl");
	initUniformBuffer();
	texture = _tex;
	toonTexture = _toonTex;
}

const FragmentShader& SkyboxMaterial::getFragmentShader() {
	return fragment_shader;
}

const FragmentShader& SkyboxMaterial::getXrayCullShader() {
	return fragment_shader;
}

const FragmentShader& SkyboxMaterial::getXrayShader() {
	return xray_shader;
}

const void* SkyboxMaterial::getUniformData() const {
	return nullptr;
}

GLsizeiptr SkyboxMaterial::getUniformDataSize() const {
	return 0;
}

void SkyboxMaterial::draw(const Scene& scene, const Geometry& geometry) const {
	glColorMask(GL_TRUE, GL_TRUE, GL_TRUE, GL_TRUE); // Enable color writes.
	glDepthFunc(GL_LEQUAL); // Only draw a pixel if it's depth matches the value stored in the depth buffer.
	glDisable(GL_BLEND); // disable blending.
	glDisable(GL_CULL_FACE);
	geometry.draw();
	glEnable(GL_CULL_FACE);
}

void SkyboxMaterial::bind() const {
	Material::bind();
	texture->bind(4);
	glUniform1i(4, 4);
}