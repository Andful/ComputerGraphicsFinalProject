#pragma once
#include "disable_all_warnings.h"
DISABLE_WARNINGS_PUSH()
#include <GL/glew.h>
#include <glm/mat3x3.hpp>
#include <glm/mat4x4.hpp>
#include <glm/vec2.hpp>
#include <glm/vec3.hpp>
#include <glm/vec4.hpp>
DISABLE_WARNINGS_POP()
#include <exception>
#include <filesystem>
#include <vector>

struct ShaderLoadingException : public std::runtime_error {
    using std::runtime_error::runtime_error;
};

class Shader {
public:
    Shader();

    // ... Feel free to add more methods here (e.g. for setting uniforms or keeping track of texture units) ...

    void bind() const;

private:
    friend class ShaderBuilder;
    Shader(std::shared_ptr<GLuint> program);

private:
    std::shared_ptr<GLuint> m_program;
};

class ShaderBuilder {
public:
    ShaderBuilder& addStage(GLuint shaderStage, std::filesystem::path shaderFile);
    Shader build();

private:
    std::vector<std::shared_ptr<GLuint>> m_shaders = {};
};
