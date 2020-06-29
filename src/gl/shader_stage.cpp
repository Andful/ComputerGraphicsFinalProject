#include "gl/shader.h"
#include "gl/shader_stage.h"

bool checkShaderErrors(GLuint shader)
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