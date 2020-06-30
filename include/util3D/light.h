#pragma once

#include <memory>
#include <functional>
#include <GL/glew.h>
#include <glm/glm.hpp>
#include "util3D/transformable.h"

typedef struct alignas(16) _LightUniformData {
    glm::vec3 light_position;
    glm::vec3 light_color;
    bool casts_shadow;
    glm::mat4 light_mvp;
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