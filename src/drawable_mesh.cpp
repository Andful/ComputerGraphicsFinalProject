#include "drawable_mesh.h"

DrawableMesh::DrawableMesh(const Mesh& _mesh, const Shader& _shader, const Shader& _vertexShader, const Texture& _texture) {
    mesh = _mesh;
    shader = _shader;
    vertexShader = _vertexShader;
    texture = _texture;
}

void DrawableMesh::drawDepth(const ICamera &camera, const Scene &scene) const
{
	glDepthMask(GL_TRUE);
	glDepthFunc(GL_LEQUAL);
	glColorMask(GL_FALSE,GL_FALSE, GL_FALSE, GL_FALSE);
	vertexShader.bind();
	glUniformMatrix4fv(0, 1, GL_FALSE, glm::value_ptr(
			camera.getProjectionMatrix() * camera.getInverseWorldTransform() * world_transform));
	glUniformMatrix4fv(1, 1, GL_FALSE, glm::value_ptr(world_transform));
	glUniformMatrix3fv(2, 1, GL_FALSE, glm::value_ptr(glm::inverseTranspose(glm::mat3(world_transform))));
	mesh.draw();

}
void DrawableMesh::draw(const ICamera& camera, const Scene& scene, const DrawableLight &light) const
{
	glColorMask(GL_TRUE, GL_TRUE, GL_TRUE, GL_TRUE); // Enable color writes.
	glDepthMask(GL_FALSE); // Disable depth writes.
	glDepthFunc(GL_EQUAL); // Only draw a pixel if it's depth matches the value stored in the depth buffer.
	glEnable(GL_BLEND); // Enable blending.
	glBlendFunc(GL_SRC_ALPHA, GL_ONE); // Additive blending.
	shader.bind();

		glUniformMatrix4fv(0, 1, GL_FALSE, glm::value_ptr(
				camera.getProjectionMatrix() * camera.getInverseWorldTransform() * world_transform));
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

		glUniform3fv(6, 1, glm::value_ptr(light.getWorldPosition()));
		glUniform3fv(7, 1, glm::value_ptr(light.getColor()));
		glUniform3fv(8, 1, glm::value_ptr(camera.getWorldPosition()));
		glUniform1f(9, 10.f);
		glUniform3fv(10, 1, glm::value_ptr(glm::vec3(0.4, 0.4, 0.4)));
		mesh.draw();
	glDepthFunc(GL_LEQUAL);
	glDepthMask(GL_TRUE);
	glDisable(GL_BLEND);
}
