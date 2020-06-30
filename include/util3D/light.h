#pragma once

#include <memory>
#include <functional>
#include <GL/glew.h>
#include <glm/glm.hpp>
#include "util3D/transformable.h"

typedef struct alignas(16) _LightUniformData {
    glm::mat4 light_mvp;
    glm::vec3 light_position;
    float pad0;
    glm::vec3 light_color;
    float pad1;
    uint32_t casts_shadow;
} LightUniformData;

class Light {
protected:
    std::unique_ptr<GLuint, std::function<void(GLuint*)>> ubo;
    LightUniformData data;
public:
    Light();
    void updateUniformData() const;
    virtual void bind();
    virtual ~Light() = default;
};