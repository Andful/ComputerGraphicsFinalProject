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
	//glViewport(0, 0, 1024, 500);
	//call parent function to start the render chain
	glColorMask(GL_TRUE, GL_TRUE, GL_TRUE, GL_TRUE); // Enable color writes.
	glDepthMask(GL_FALSE); // Disable depth writes.
	glDisable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL); // Only draw a pixel if it's depth matches the value stored in the depth buffer.
	glDisable(GL_BLEND); // Enable blending.
	glBlendFunc(GL_SRC_ALPHA, GL_ONE); // Additive blending.
	/*for(std::shared_ptr<Light> light : scene.getLights()) {
		light -> bind();
		geometry.draw();
	}*/
	glDisable(GL_CULL_FACE);
	geometry.draw();
	glEnable(GL_CULL_FACE);
}

void SkyboxMaterial::bind() const {
	Material::bind();
	texture->bind(4);
	glUniform1i(4, 4);
//	toonTexture->bind(5);
//	glUniform1i(5, 5);
}