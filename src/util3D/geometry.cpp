#include <iostream>
#include <stack>
#include <vector>
#include "disable_all_warnings.h"
DISABLE_WARNINGS_PUSH()
#include <assimp/Importer.hpp>
#include <assimp/postprocess.h>
#include <assimp/scene.h>
#include <fmt/format.h>
#include <glm/gtc/matrix_inverse.hpp>
#include <glm/mat3x3.hpp>
#include <glm/mat4x4.hpp>
#include <glm/vec4.hpp>
#include <gsl/span>
DISABLE_WARNINGS_POP()
#include "util3D/geometry.h"

Geometry::Geometry() {
    ubo = std::shared_ptr<GLuint>(new GLuint(),[](GLuint *p){
        glDeleteBuffers(1,p);
        delete p;
    });
    glCreateBuffers(1, ubo.get());
}

void Geometry::initUniformBuffer() const {
    glBindBuffer(GL_UNIFORM_BUFFER, *ubo);
	glBufferData(GL_UNIFORM_BUFFER, getUniformDataSize(), getUniformData(), GL_STATIC_DRAW);
	glBindBuffer(GL_UNIFORM_BUFFER, 0);
}

void Geometry::updateUniformData() const {
    glBindBuffer(GL_UNIFORM_BUFFER, *ubo);
    glBufferSubData(GL_UNIFORM_BUFFER,
        0,
        getUniformDataSize(),
        getUniformData());
    glBindBuffer(GL_UNIFORM_BUFFER, 0);
}

void Geometry::bind() const {
    glBindBufferBase(GL_UNIFORM_BUFFER, 3, *ubo);
}
