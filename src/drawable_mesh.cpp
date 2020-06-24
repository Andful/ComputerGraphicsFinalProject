#include "drawable_mesh.h"

DrawableMesh::DrawableMesh(const Mesh& _mesh, const Shader& _shader, const Texture& _texture) {
    mesh = _mesh;
    shader = _shader;
    texture = _texture;
}

void DrawableMesh::draw(const ICamera& camera, const Scene& scene) const {
	shader.bind();
	glUniformMatrix4fv(0, 1, GL_FALSE, glm::value_ptr(camera.getProjectionMatrix() * camera.getInverseWorldTransform() * world_transform));
	glUniformMatrix4fv(1, 1, GL_FALSE, glm::value_ptr(world_transform));
	glUniformMatrix3fv(2, 1, GL_FALSE, glm::value_ptr(glm::inverseTranspose(glm::mat3(world_transform))));
	if (mesh.hasTextureCoords())
	{
		texture.bind(0);
		glUniform1i(3, 0);
		glUniform1i(4, GL_TRUE);
	}
	else
	{
		glUniform1i(4, GL_FALSE);
	}
	glUniform3fv(5, 1, glm::value_ptr(glm::vec3(0.5, 0.5, 0.5)));
	
	glUniform3fv(6, 1, glm::value_ptr(scene.getLightData()[0]));
	glUniform3fv(7, 1, glm::value_ptr(scene.getLightData()[1]));
	glUniform3fv(8, 1, glm::value_ptr(camera.getWorldPosition()));
	glUniform1f(9, .4f);
	glUniform3fv(10, 1, glm::value_ptr(glm::vec3(0.4, 0.4, 0.4)));
	mesh.draw();
	//std::cout << glm::to_string() << std::endl;
	/*shader.bind();
	glUniformMatrix4fv(0, 1, GL_FALSE, glm::value_ptr(camera.getProjectionMatrix() * world_transform));
	glUniformMatrix4fv(1, 1, GL_FALSE, glm::value_ptr(world_transform));
	glUniformMatrix3fv(2, 1, GL_FALSE, glm::value_ptr(glm::inverseTranspose(glm::mat3(world_transform))));
	if (mesh.hasTextureCoords())
	{
		texture.bind(0);
		glUniform1i(3, 0);
		glUniform1i(4, GL_TRUE);
	}
	else
	{
		glUniform1i(4, GL_FALSE);
	}
	mesh.draw();*/
	//glDisable(GL_BLEND);
}
