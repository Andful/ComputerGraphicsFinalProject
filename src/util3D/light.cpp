#include "util3D/light.h"
#include <functional>

Light::Light() {
    ubo = std::unique_ptr<GLuint, std::function<void(GLuint*)>>(new GLuint(), [](GLuint* p){
        glDeleteBuffers(1, p);
        delete p;
    });
    glCreateBuffers(1, ubo.get());
}

void Light::updateUniformData() const {
    glBindBuffer(GL_UNIFORM_BUFFER, *ubo);
	glBufferData(GL_UNIFORM_BUFFER,sizeof(LightUniformData), &data, GL_DYNAMIC_DRAW); 
	glBindBuffer(GL_UNIFORM_BUFFER, 0);
}

void Light::bind() {
    glBindBufferBase(GL_UNIFORM_BUFFER, 2, *ubo);
}