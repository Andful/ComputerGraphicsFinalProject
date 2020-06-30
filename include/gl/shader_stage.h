#pragma once

#include <string>
#include <sstream>
#include <filesystem>
#include <fstream>
#include <exception>
#include <fmt/format.h>
#include <GL/glew.h>

class Shader;

bool checkShaderErrors(GLuint shader);

template<GLenum SHADER_STAGE>
class ShaderStage {
    std::shared_ptr<GLuint> m;
public:
    ShaderStage() {
        m = std::shared_ptr<GLenum>(new GLenum(), [](GLenum* p){
            glDeleteShader(*p);
            delete p;
        });
        *m = glCreateShader(SHADER_STAGE);
    }

    ShaderStage(const std::string& source, int i): ShaderStage() {
        compile(source);
    }

    ShaderStage(std::filesystem::path shaderFile): ShaderStage() {
        if (!std::filesystem::exists(shaderFile)) {
            throw std::runtime_error(fmt::format("File {} does not exist", shaderFile.string().c_str()));
        }
        std::ifstream file(shaderFile, std::ios::binary);
        std::stringstream buffer;
        buffer << file.rdbuf();
        std::string source = buffer.str();
        compile(source);
    }

    void compile(const std::string& source) {
        const char* shaderSourcePtr = source.c_str();
        glShaderSource(*m, 1, &shaderSourcePtr, nullptr);
        glCompileShader(*m);

        if (!checkShaderErrors(*m)) {
            throw std::runtime_error(fmt::format("Failed to compile shader {}", shaderSourcePtr));
        }
    }
    GLenum getStage() {
        return SHADER_STAGE;
    }
    friend Shader;
};

class VertexShader: public ShaderStage<GL_VERTEX_SHADER> {
    using ShaderStage::ShaderStage;
};

class FragmentShader: public ShaderStage<GL_FRAGMENT_SHADER> {
    using ShaderStage::ShaderStage;
};