#pragma once
#include <memory>

#include "disable_all_warnings.h"
DISABLE_WARNINGS_PUSH()
#include <GL/glew.h>
DISABLE_WARNINGS_POP()

#include "texture.h"

class Framebuffer;

class FramebufferBindGuard
{
private:
    FramebufferBindGuard(const FramebufferBindGuard&) = delete;
    FramebufferBindGuard(GLuint m);
public:
    operator bool() const;
    ~FramebufferBindGuard();
    friend Framebuffer;
};

class Framebuffer
{
    private:
        std::shared_ptr<GLuint> m_framebuffer = nullptr;
    public:
        Framebuffer() = default;
        Framebuffer(const Texture& texture, GLenum attachment);
        void bind() const;
        void unbind() const;
        FramebufferBindGuard bindGuard() const;
};