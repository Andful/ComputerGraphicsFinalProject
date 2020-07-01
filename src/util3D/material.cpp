#include "util3D/material.h"
#include "util3D/geometry.h"

Material::Material() {
    ubo = std::shared_ptr<GLuint>(new GLuint(), [](GLuint *p){
        glDeleteBuffers(1,p);
        delete p;
    });
    glCreateBuffers(1, ubo.get());
}

void Material::initUniformBuffer() const {
    glBindBuffer(GL_UNIFORM_BUFFER, *ubo);
	glBufferData(GL_UNIFORM_BUFFER, getUniformDataSize(), getUniformData(), GL_STATIC_DRAW);
	glBindBuffer(GL_UNIFORM_BUFFER, 0);
}

void Material::updateUniformData() const {
    glBindBuffer(GL_UNIFORM_BUFFER, *ubo);
    glBufferSubData(GL_UNIFORM_BUFFER,
        0,
        getUniformDataSize(),
        getUniformData());
    glBindBuffer(GL_UNIFORM_BUFFER, 0);
}

void Material::bind() const {
    glBindBufferBase(GL_UNIFORM_BUFFER, 4, *ubo);
}

void Material::draw(const Scene& scene, const Geometry& geometry) const {
    geometry.draw();
}