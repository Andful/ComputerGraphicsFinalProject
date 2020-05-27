#include "shader.h"
#include "disable_all_warnings.h"
#include <cassert>
DISABLE_WARNINGS_PUSH()
#include <fmt/format.h>
DISABLE_WARNINGS_POP()
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

static bool checkShaderErrors(GLuint shader);
static bool checkProgramErrors(GLuint program);
static std::string readFile(std::filesystem::path filePath);

Shader::Shader()
{
    m_program = std::shared_ptr<GLuint>(new GLuint(), [](GLuint *p) {
        glDeleteProgram(*p);
        delete p;
    });
}

Shader::Shader(std::shared_ptr<GLuint> program)
    : m_program(program)
{
}

void Shader::bind() const
{
    glUseProgram(*m_program);
}

ShaderBuilder& ShaderBuilder::addStage(GLuint shaderStage, std::filesystem::path shaderFile)
{
    if (!std::filesystem::exists(shaderFile)) {
        throw ShaderLoadingException(fmt::format("File {} does not exist", shaderFile.string().c_str()));
    }

    const std::string shaderSource = readFile(shaderFile);
    std::shared_ptr<GLuint> shader(new GLuint(), [](GLuint* p){
        glDeleteShader(*p);
        delete p;
    });
    *shader = glCreateShader(shaderStage);
    const char* shaderSourcePtr = shaderSource.c_str();
    glShaderSource(*shader, 1, &shaderSourcePtr, nullptr);
    glCompileShader(*shader);
    if (!checkShaderErrors(*shader)) {
        shader = nullptr;
        throw ShaderLoadingException(fmt::format("Failed to compile shader {}", shaderFile.string().c_str()));
    }

    m_shaders.push_back(shader);
    return *this;
}

Shader ShaderBuilder::build()
{
    // Combine vertex and fragment shaders into a single shader program.
    std::shared_ptr<GLuint> program(new GLuint(), [](GLuint *p) {
        glDeleteProgram(*p);
        delete p;
    });
    *program = glCreateProgram();
    for (const std::shared_ptr<GLuint>& shader : m_shaders)
        glAttachShader(*program, *shader);
    glLinkProgram(*program);

    if (!checkProgramErrors(*program)) {
        throw ShaderLoadingException("Shader program failed to link");
    }

    return Shader(program);
}

static std::string readFile(std::filesystem::path filePath)
{
    std::ifstream file(filePath, std::ios::binary);

    std::stringstream buffer;
    buffer << file.rdbuf();
    return buffer.str();
}

static bool checkShaderErrors(GLuint shader)
{
    // Check if the shader compiled successfully.
    GLint compileSuccessful;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &compileSuccessful);

    // If it didn't, then read and print the compile log.
    if (!compileSuccessful) {
        GLint logLength;
        glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &logLength);

        std::string logBuffer;
        logBuffer.resize(static_cast<size_t>(logLength));
        glGetShaderInfoLog(shader, logLength, nullptr, logBuffer.data());

        std::cerr << logBuffer << std::endl;
        return false;
    } else {
        return true;
    }
}

static bool checkProgramErrors(GLuint program)
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
