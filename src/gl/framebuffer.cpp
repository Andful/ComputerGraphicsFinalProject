#include "gl/framebuffer.h"

FramebufferBindGuard::FramebufferBindGuard(GLuint m)
{
    glBindFramebuffer(GL_FRAMEBUFFER, m);
}

FramebufferBindGuard::operator bool() const
{
    return true;
}

FramebufferBindGuard::~FramebufferBindGuard()
{
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

Framebuffer::Framebuffer(const Texture& texture, GLenum attachment)
{
    m_framebuffer = std::shared_ptr<GLuint>(new GLuint(),[](GLuint *p){
        glDeleteFramebuffers(1, p);
        delete p;
    });
    glCreateFramebuffers(1, m_framebuffer.get());
    glNamedFramebufferTexture(*m_framebuffer, attachment, *(texture.m_texture), 0);
}

void Framebuffer::addAttachment(const Texture& texture, GLenum attachment)
{
    glNamedFramebufferTexture(*m_framebuffer, attachment, *(texture.m_texture), 0);
}

void Framebuffer::bind() const
{
    glBindFramebuffer(GL_FRAMEBUFFER, *m_framebuffer);
}

void Framebuffer::unbind() const
{
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

FramebufferBindGuard Framebuffer::bindGuard() const
{
    return FramebufferBindGuard(*m_framebuffer);
}