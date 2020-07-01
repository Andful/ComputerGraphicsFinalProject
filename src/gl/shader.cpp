#include "gl/shader.h"
#include "disable_all_warnings.h"
#include <cassert>
DISABLE_WARNINGS_PUSH()
#include <fmt/format.h>
DISABLE_WARNINGS_POP()
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "gl/shader_stage.h"

Shader::Shader()
{
    program = std::shared_ptr<GLuint>(new GLuint(), [](GLuint *p) {
        glDeleteProgram(*p);
        delete p;
    });
    *program = glCreateProgram();
}

Shader::Shader(const VertexShader& vs, const FragmentShader& fs) : Shader() {
    glAttachShader(*program, *(vs.m));
    glAttachShader(*program, *(fs.m));
    glLinkProgram(*program);

    std::cerr << int(*program) << std::endl;

    if (!checkProgramErrors(*program)) {
        throw ShaderLoadingException("Shader program failed to link");
    }
}

Shader::Shader(const VertexShader& vs) : Shader() {
    glAttachShader(*program, *(vs.m));
    glLinkProgram(*program);

    std::cerr << int(*program) << std::endl;

    if (!checkProgramErrors(*program)) {
        throw ShaderLoadingException("Shader program failed to link");
    }
}

Shader::Shader(std::shared_ptr<GLuint> _program)
    : program(_program)
{
}

std::string parseSource();

void Shader::loadSource(const std::string& source, GLenum shaderStage) const {
    GLuint shader = glCreateShader(shaderStage);
    const char* shaderSourcePtr = source.c_str();
    glShaderSource(shader, 1, &shaderSourcePtr, nullptr);
    glCompileShader(shader);
    if (!checkShaderErrors(shader)) {
        throw ShaderLoadingException(fmt::format("Failed to compile shader {}", shaderSourcePtr));
    }
    glAttachShader(*program, shader);
    glDeleteShader(shader);
}

void Shader::bind() const
{
    glUseProgram(*program);
}

template<>
void Shader::loadUniform(GLint index, float data) const {
    glUniform1f(index, data);
}

template<>
void Shader::loadUniform(GLint index, int data) const {
    glUniform1i(index, data);
}

template<>
void Shader::loadUniform(GLint index, const glm::vec3& data) const {
    glUniform3fv(index, 1, glm::value_ptr(data));
}

template<>
void Shader::loadUniform(GLint index, const glm::mat3& data) const {
    glUniformMatrix3fv(index, 1, GL_FALSE, glm::value_ptr(data));
}

template<>
void Shader::loadUniform(GLint index, const glm::mat4& data) const {
    glUniformMatrix4fv(index, 1, GL_FALSE, glm::value_ptr(data));
}

bool checkProgramErrors(GLuint program)
{
    // Check if the program linked successfully
    GLint linkSuccessful;
    glGetProgramiv(program, GL_LINK_STATUS, &linkSuccessful);

    // If it didn't, then read and print the link log
    if (!linkSuccessful) {
        GLint logLength;
        glGetProgramiv(program, GL_INFO_LOG_LENGTH, &logLength);

        std::string logBuffer;
        logBuffer.resize(static_cast<size_t>(logLength));
        glGetProgramInfoLog(program, logLength, nullptr, logBuffer.data());

        std::cerr << logBuffer << std::endl;
        return false;
    } else {
        return true;
    }
}

std::string readFile(std::filesystem::path filePath)
{
    std::ifstream file(filePath, std::ios::binary);
    std::stringstream buffer;
    buffer << file.rdbuf();
    return buffer.str();
}
