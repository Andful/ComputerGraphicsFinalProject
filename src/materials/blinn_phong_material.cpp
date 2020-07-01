#include "materials/blinn_phong_material.h"
#include "util3D/geometry.h"

BlinnPhongMaterial::BlinnPhongMaterial(glm::vec3 ks, float shininess, glm::vec3 kd) {
    fragment_shader = FragmentShader("shaders/blinn_phong.frag.glsl");
    blinn_phong_material_uniform.ks = ks;
    blinn_phong_material_uniform.shininess = shininess;
    blinn_phong_material_uniform.kd = kd;
    initUniformBuffer();
}

const FragmentShader& BlinnPhongMaterial::getFragmentShader() {
    return fragment_shader;
}

const void* BlinnPhongMaterial::getUniformData() const {
    return static_cast<const void*>(&blinn_phong_material_uniform);
}

GLsizeiptr BlinnPhongMaterial::getUniformDataSize() const {
    return sizeof(BlinnPhongMaterialUnifromData);
}

void BlinnPhongMaterial::draw(const Scene& scene, const Geometry& geometry) const {
    //glViewport(0, 0, 1024, 500);
	//call parent function to start the render chain
    glUniform1i(1, 1);
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