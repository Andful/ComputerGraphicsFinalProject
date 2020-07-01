#pragma once
#include "disable_all_warnings.h"
DISABLE_WARNINGS_PUSH()
#include <GL/glew.h>
#include <glm/vec3.hpp>
DISABLE_WARNINGS_POP()
#include <exception>
#include <filesystem>
#include <memory>

struct ImageLoadingException : public std::runtime_error {
    using std::runtime_error::runtime_error;
};

class Framebuffer;

class Texture {
protected:
    std::shared_ptr<GLuint> m_texture = nullptr;
public:
    Texture() = default;
    Texture(const Texture&) = default;
    Texture(GLsizei width, GLsizei height, GLenum internalFormat);
    Texture(std::filesystem::path filePath);
    virtual void bind(GLint textureSlot) const;
    virtual void set(GLenum parameter, GLint setting);
    friend Framebuffer;
};

#include "framebuffer.h"
