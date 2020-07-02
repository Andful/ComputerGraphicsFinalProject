#include "materials/blinn_phong_material.h"
#include "util3D/geometry.h"

BlinnPhongMaterial::BlinnPhongMaterial(glm::vec3 ks, float shininess, glm::vec3 kd, std::shared_ptr<Texture> _tex, std::shared_ptr<Texture> _toonTex)
{
    fragment_shader = FragmentShader("shaders/blinn_phong.frag.glsl");
    xray_shader = FragmentShader("shaders/xtoon.frag.glsl");
    xray_cull_shader = FragmentShader("shaders/xray.frag.glsl");
    blinn_phong_material_uniform.ks = ks;
    blinn_phong_material_uniform.shininess = shininess;
    blinn_phong_material_uniform.kd = kd;
    initUniformBuffer();
    texture = _tex;
    toonTexture = _toonTex;
}

const FragmentShader& BlinnPhongMaterial::getFragmentShader() {
    return fragment_shader;
}

const FragmentShader& BlinnPhongMaterial::getXrayCullShader() {
    return xray_cull_shader;
}

const FragmentShader& BlinnPhongMaterial::getXrayShader() {
    return xray_shader;
}

const void* BlinnPhongMaterial::getUniformData() const {
    return static_cast<const void*>(&blinn_phong_material_uniform);
}

GLsizeiptr BlinnPhongMaterial::getUniformDataSize() const {
    return sizeof(BlinnPhongMaterialUnifromData);
}

void BlinnPhongMaterial::draw(const Scene& scene, const Geometry& geometry) const {
    glColorMask(GL_TRUE, GL_TRUE, GL_TRUE, GL_TRUE); // Enable color writes.
    glDepthMask(GL_FALSE); // Disable depth writes.
    glDepthFunc(GL_EQUAL); // Only draw a pixel if it's depth matches the value stored in the depth buffer.
    glEnable(GL_BLEND); // Enable blending.
    glBlendFunc(GL_SRC_ALPHA, GL_ONE); // Additive blending.
    for(std::shared_ptr<Light> light : scene.getLights()) {
        light -> bind();
        geometry.draw();
    }
	glDepthFunc(GL_LEQUAL);
	glDepthMask(GL_TRUE);
	glDisable(GL_BLEND);
}

void BlinnPhongMaterial::bind() const {
    Material::bind();
    texture->bind(4);
    glUniform1i(4, 4);
    toonTexture->bind(5);
    glUniform1i(5, 5);
}