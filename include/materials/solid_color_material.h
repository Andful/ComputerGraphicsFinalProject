#include <glm/glm.hpp>
#include "gl/shader_stage.h"
#include "util3D/material.h"

class FragmentShader;

typedef struct alignas(16) _SolidColorMaterialUnifrom{
    glm::vec3  color;
} SolidColorMaterialUnifrom;

class SolidColorMaterial : public Material {
private:
    FragmentShader fragment_shader, xray_shader, xray_cull_shader;
    SolidColorMaterialUnifrom solid_color_material_uniform;
public:
    SolidColorMaterial(glm::vec3 color);
    const FragmentShader& getFragmentShader() override;
    const FragmentShader& getXrayCullShader() override;
    const FragmentShader& getXrayShader() override;

    const void* getUniformData() const override;
    GLsizeiptr getUniformDataSize() const override;
};