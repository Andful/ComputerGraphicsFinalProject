#include "materials/chrome_material.h"
#include "util3D/geometry.h"

ChromeMaterial::ChromeMaterial(std::shared_ptr<CubeTexture> _tex, std::shared_ptr<Texture> _toonTex)
{
	fragment_shader = FragmentShader("shaders/chrome.frag.glsl");
	xray_shader = FragmentShader("shaders/xtoon.frag.glsl");
	xray_cull_shader = FragmentShader("shaders/xray.frag.glsl");
	texture = _tex;
	toonTexture = _toonTex;
}

const FragmentShader& ChromeMaterial::getFragmentShader() {
	return fragment_shader;
}

const FragmentShader& ChromeMaterial::getXrayCullShader() {
	return xray_cull_shader;
}

const FragmentShader& ChromeMaterial::getXrayShader() {
	return xray_shader;
}

const void* ChromeMaterial::getUniformData() const {
	return nullptr;
}

GLsizeiptr ChromeMaterial::getUniformDataSize() const {
	return 0;
}

void ChromeMaterial::draw(const Scene& scene, const Geometry& geometry) const {
	glColorMask(GL_TRUE, GL_TRUE, GL_TRUE, GL_TRUE); // Enable color writes.
	glDepthMask(GL_FALSE); // Disable depth writes.
	glDepthFunc(GL_EQUAL); // Only draw a pixel if it's depth matches the value stored in the depth buffer.
	glDisable(GL_BLEND); // Blending temporarily disabled
	glBlendFunc(GL_SRC_ALPHA, GL_ONE); // Additive blending.
	/*for(const std::shared_ptr<Light> &light : scene.getLights()) {
		light -> bind();
		geometry.draw();
	}*/
	geometry.draw();
	glDepthFunc(GL_LEQUAL);
	glDepthMask(GL_TRUE);
}

void ChromeMaterial::bind() const {
	Material::bind();
	texture->bind(4);
	glUniform1i(4, 4);
	toonTexture->bind(5);
	glUniform1i(5, 5);
}