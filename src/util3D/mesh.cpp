#include <glm/gtc/matrix_inverse.hpp>

#include "util3D/mesh.h"
#include "util3D/scene.h"
#include "util3D/geometry.h"
#include "util3D/material.h"

Mesh::Mesh(const Mesh& mesh) : Transformable(mesh) {
	geometry = mesh.geometry;
	material = mesh.material;
	shader = mesh.shader;
	depthShader = mesh.depthShader;
	data = mesh.data;
	ubo = std::unique_ptr<GLuint, std::function<void(GLuint*)>>(new GLuint(), [](GLuint* p){
        glDeleteBuffers(1, p);
        delete p;
    });
	glCreateBuffers(1, ubo.get());
	glBindBuffer(GL_UNIFORM_BUFFER, *ubo);
	glBufferData(GL_UNIFORM_BUFFER, sizeof(WorldTransformationUniformData), &data, GL_DYNAMIC_DRAW);
	glBindBuffer(GL_UNIFORM_BUFFER, 0);
}

Mesh::Mesh(const std::shared_ptr<Geometry>& _geometry,const std::shared_ptr<Material>& _material) {
	ubo = std::unique_ptr<GLuint, std::function<void(GLuint*)>>(new GLuint(), [](GLuint* p){
        glDeleteBuffers(1, p);
        delete p;
    });
	glCreateBuffers(1, ubo.get());
	glBindBuffer(GL_UNIFORM_BUFFER, *ubo);
	glBufferData(GL_UNIFORM_BUFFER, sizeof(WorldTransformationUniformData), &data, GL_DYNAMIC_DRAW);
	glBindBuffer(GL_UNIFORM_BUFFER, 0);

    geometry = _geometry;
	material = _material;
	shader = Shader(geometry->getVertexShader(), material -> getFragmentShader());
	depthShader = Shader(geometry->getVertexShader());
}

const Geometry& Mesh::getGeometry() const {
	return *geometry;
}

const Material& Mesh::getMaterial() const {
	return *material;
}

const Shader& Mesh::getShader() const {
	return shader;
}

const Shader& Mesh::getDepthShader() const {
	return depthShader;
}

void Mesh::addedToScene(Scene& _scene, std::shared_ptr<Transformable>& self) {
	Transformable::addedToScene(_scene, self);
	_scene.meshes.push_back(std::dynamic_pointer_cast<Mesh>(self));
}


void Mesh::update(const glm::mat4& transform) {
	Transformable::update(transform);
	data.world_transform = getWorldTransform();
	data.normal_transform = glm::inverseTranspose(glm::mat3(data.world_transform));
	glBindBuffer(GL_UNIFORM_BUFFER, *ubo);
    glBufferSubData(
        GL_UNIFORM_BUFFER,
        0,
        sizeof(WorldTransformationUniformData),
        static_cast<const void*>(&data));
    glBindBuffer(GL_UNIFORM_BUFFER, 0);
}

void Mesh::bind() const {
	glBindBufferBase(GL_UNIFORM_BUFFER, 1, *ubo);
}