<<<<<<< HEAD
#pragma once

=======
>>>>>>> fa1109b6f083e67db6402c2f6b6f46510036cf78
#include "disable_all_warnings.h"
DISABLE_WARNINGS_PUSH()
#include <GL/glew.h>
#include <glm/mat3x3.hpp>
#include <glm/mat4x4.hpp>
#include <glm/vec2.hpp>
#include <glm/vec3.hpp>
#include <glm/vec4.hpp>
#include <fmt/format.h>
DISABLE_WARNINGS_POP()
#include <exception>
#include <filesystem>
#include <vector>
#include <iostream>
#include <fstream>

bool checkShaderErrors(GLuint shader);
bool checkProgramErrors(GLuint program);
std::string readFile(std::filesystem::path filePath);


struct ShaderLoadingException : public std::runtime_error {
    using std::runtime_error::runtime_error;
};

class Shader {
private:
    friend class ShaderBuilder;
    Shader(std::shared_ptr<GLuint> program);

private:
    std::shared_ptr<GLuint> program;
public:
    Shader();
    void load(){}
    template<class ...Args>
    void load(std::filesystem::path shaderFile, Args... args) {
        if (!std::filesystem::exists(shaderFile)) {
            throw ShaderLoadingException(fmt::format("File {} does not exist", shaderFile.string().c_str()));
        }

        GLuint shaderStage;
        if (shaderFile.filename().string().find(".vert")!= std::string::npos) {
            shaderStage = GL_VERTEX_SHADER;
        } else if (shaderFile.filename().string().find(".geom")!= std::string::npos) {
            shaderStage = GL_GEOMETRY_SHADER;
        } else if (shaderFile.filename().string().find(".frag")!= std::string::npos) {
            shaderStage = GL_FRAGMENT_SHADER;
        } else if (shaderFile.filename().string().find(".comp")!= std::string::npos) {
            shaderStage = GL_COMPUTE_SHADER;
        } else {
            throw ShaderLoadingException(fmt::format("Shader file should contain estension \".vert\" \".geom\" \".frag\" or \".comp\""));
        }

        const std::string shaderSource = readFile(shaderFile);
        GLuint shader = glCreateShader(shaderStage);
        const char* shaderSourcePtr = shaderSource.c_str();
        glShaderSource(shader, 1, &shaderSourcePtr, nullptr);
        glCompileShader(shader);
        if (!checkShaderErrors(shader)) {
            throw ShaderLoadingException(fmt::format("Failed to compile shader {}", shaderFile.string().c_str()));
        }
        glAttachShader(*program, shader);
        glDeleteShader(shader);
        load(args...);
    }
<<<<<<< HEAD

    template<class ...Args>
    Shader(Args... args) : Shader() {
        load(args...);
        glLinkProgram(*program);

=======

    template<class ...Args>
    Shader(Args... args) : Shader() {
        load(args...);
        glLinkProgram(*program);

>>>>>>> fa1109b6f083e67db6402c2f6b6f46510036cf78
        if (!checkProgramErrors(*program)) {
            throw ShaderLoadingException("Shader program failed to link");
        }
    }
    void bind() const;
};

class ShaderBuilder {
public:
    ShaderBuilder& addStage(GLuint shaderStage, std::filesystem::path shaderFile);
    Shader build();

private:
    std::vector<std::shared_ptr<GLuint>> m_shaders = {};
};