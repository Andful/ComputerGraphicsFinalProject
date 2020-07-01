#pragma once

#include <memory>
#include <glm/glm.hpp>
#include "util3D/transformable.h"
#include "gl/shader.h"

class Material;
class Geometry;

typedef struct alignas(16) _WorldTransformationUniformData {
    glm::mat4 world_transform;
    glm::mat3x4 normal_transform;
} WorldTransformationUniformData;

class Mesh : public Transformable {
private:
    WorldTransformationUniformData data;
    std::unique_ptr<GLuint, std::function<void(GLuint*)>> ubo;
    std::shared_ptr<Geometry> geometry;
    std::shared_ptr<Material> material;
    Shader shader, xray_shader;
    Shader depthShader, xray_cull_shader;
public:
    Mesh(const Mesh& mesh);
    Mesh(const std::shared_ptr<Geometry>& _geometry,const std::shared_ptr<Material>& material);
    const Geometry& getGeometry() const;
    const Material& getMaterial() const;
    const Shader& getShader() const;
    const Shader& getDepthShader() const;
    const Shader& getXrayCullShader() const;
    void addedToScene(Scene& _scene, std::shared_ptr<Transformable>& self) override;
    void update(const glm::mat4& transform) override;
    void bind() const;
};