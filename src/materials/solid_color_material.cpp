#include "util3D/material.h"
#include "materials/solid_color_material.h"

SolidColorMaterial::SolidColorMaterial(glm::vec3 color) {
    fragment_shader = FragmentShader("shaders/solid.frag.glsl");
    solid_color_material_uniform.color = color;
    initUniformBuffer();
}

const FragmentShader& SolidColorMaterial::getFragmentShader() {
    return fragment_shader;
}

const void* SolidColorMaterial::getUniformData() const {
    return static_cast<const void*>(&solid_color_material_uniform);
}

GLsizeiptr SolidColorMaterial::getUniformDataSize() const {
    return sizeof(SolidColorMaterialUnifrom);
}