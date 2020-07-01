#pragma once

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

class VertexShader;
class FragmentShader;

class Shader {
private:
    Shader(std::shared_ptr<GLuint> program);
public:
    std::shared_ptr<GLuint> program;
    Shader();
    Shader(const VertexShader& vs, const FragmentShader& fs);
    Shader(const VertexShader& vs);
    void loadSource(const std::string& source, GLenum shaderType) const;
    void load() const {}
    template<class ...Args>
    void load(std::filesystem::path shaderFile, Args... args) const {
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
        loadSource(shaderSource, shaderStage);
        load(args...);
    }

    template<class ...Args>
    Shader(Args... args) : Shader() {
        load(args...);
        glLinkProgram(*program);

        if (!checkProgramErrors(*program)) {
            throw ShaderLoadingException("Shader program failed to link");
        }
    }
    void bind() const;
    template<class T>
    void loadUniform(GLint, T data) const;
};