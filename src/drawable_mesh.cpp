#include "drawable_mesh.h"

DrawableMesh::DrawableMesh(const Mesh& _mesh, const Shader& _shader, const Texture& _texture) {
    mesh = _mesh;
    shader = _shader;
    texture = _texture;
}

void DrawableMesh::draw(const glm::mat4& projectionMatrix, const glm::mat4& transform) {
	shader.bind();

	//glEnable(GL_BLEND);
//	glBlendEquation(GL_FUNC_ADD);
	for(auto &li : this->scene->getLights())
	{
		auto lightobj = li.get();
		glUniformMatrix4fv(0, 1, GL_FALSE, glm::value_ptr(projectionMatrix * transform));
		glUniformMatrix4fv(1, 1, GL_FALSE, glm::value_ptr(transform));
		glUniformMatrix3fv(2, 1, GL_FALSE, glm::value_ptr(glm::inverseTranspose(glm::mat3(transform))));
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
		glUniform3fv(5, GL_FALSE, glm::value_ptr(glm::vec3(0.5, 0.5, 0.5)));
		glm::vec4 lightpos =  this->scene->getCamera()->getTransform() * glm::vec4(lightobj->getTranslation(), 1);
		glUniform3fv(6, GL_FALSE, glm::value_ptr(glm::vec3(lightpos.x, lightpos.y, lightpos.z)));
		glUniform3fv(7, GL_FALSE, lightobj->getColor());
		glUniform3fv(8, GL_FALSE, this->scene->getCameraPos());
		glUniform1f(9, .4f);
		glUniform3fv(10, GL_FALSE, glm::value_ptr(glm::vec3(0.4, 0.4, 0.4)));

		mesh.draw();
	}
	//glDisable(GL_BLEND);
}
