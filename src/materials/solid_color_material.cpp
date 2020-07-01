#include "util3D/material.h"
#include "materials/solid_color_material.h"

SolidColorMaterial::SolidColorMaterial(glm::vec3 color) {
    fragment_shader = FragmentShader("shaders/solid.frag.glsl");
    xray_fragment_shader = FragmentShader("shaders/xtoon.frag.glsl");
    xray_cull_shader = FragmentShader("shaders/xray.frag.glsl");
    solid_color_material_uniform.color = color;
    initUniformBuffer();
}

const FragmentShader& SolidColorMaterial::getFragmentShader() {
    return fragment_shader;
}

const FragmentShader& SolidColorMaterial::getXrayCullShader() {
    return xray_cull_shader;
}

const void* SolidColorMaterial::getUniformData() const {
    return static_cast<const void*>(&solid_color_material_uniform);
}

GLsizeiptr SolidColorMaterial::getUniformDataSize() const {
    return sizeof(SolidColorMaterialUnifrom);
}