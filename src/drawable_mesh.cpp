#include "drawable_mesh.h"
#include "camera.h"

DrawableMesh::DrawableMesh(const Mesh& _mesh, const Shader& _shader, const Shader& _vertexShader, const Texture& _texture, const Shader& _xRayShader, const Texture& _xToonTex, const Shader& _xRayCullShader) {
    mesh = _mesh;
    shader = _shader;
    vertexShader = _vertexShader;
    texture = _texture;
    xRayShader = _xRayShader;
    xToonTex = _xToonTex;
    xRayCullShader = _xRayCullShader;
}

void DrawableMesh::drawShadowMap(const Scene &scene, const DrawableLight &light) const
{
	vertexShader.bind();
	glUniformMatrix4fv(0, 1, GL_FALSE, glm::value_ptr(light.getCameraMVP() * world_transform));
	glUniformMatrix4fv(1, 1, GL_FALSE, glm::value_ptr(world_transform));
	glUniformMatrix3fv(2, 1, GL_FALSE, glm::value_ptr(glm::inverseTranspose(glm::mat3(world_transform))));
	mesh.draw();
}

void DrawableMesh::drawDepth(const Camera &camera, const Scene &scene) const
{
	//xray calculations need to be done when we generate depth info or else bad juju will occur.
	if (scene.useXRay)
	{
		vertexShader.bind();
		glBindFramebuffer(GL_FRAMEBUFFER, camera.getFramebuffer());
		glEnable(GL_DEPTH_TEST);
		glViewport(0, 0, camera.getWidth(), camera.getHeight());
		mesh.draw();

		//now we will make the actual depth buffer by removing stuff from the first round.
		glBindFramebuffer(GL_FRAMEBUFFER, 0);
		xRayCullShader.bind();
		glUniformMatrix4fv(0, 1, GL_FALSE, glm::value_ptr(
				camera.getProjectionMatrix() * camera.getInverseWorldTransform() * world_transform));
		glUniformMatrix4fv(1, 1, GL_FALSE, glm::value_ptr(world_transform));
		glUniformMatrix3fv(2, 1, GL_FALSE, glm::value_ptr(glm::inverseTranspose(glm::mat3(world_transform))));
		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D, camera.getTexShadow());
		glUniform1i(3, 1); //this is very bad please fix
		mesh.draw();
	}
	else
	{
		vertexShader.bind();
		glUniformMatrix4fv(0, 1, GL_FALSE, glm::value_ptr(
				camera.getProjectionMatrix() * camera.getInverseWorldTransform() * world_transform));
		glUniformMatrix4fv(1, 1, GL_FALSE, glm::value_ptr(world_transform));
		glUniformMatrix3fv(2, 1, GL_FALSE, glm::value_ptr(glm::inverseTranspose(glm::mat3(world_transform))));
		mesh.draw();
	}


}
void DrawableMesh::draw(const Camera& camera, const Scene& scene, const DrawableLight &light) const
{
	//Decide whether or not to use the special xray shader.
	if(scene.useXRay)
	{
		glActiveTexture(GL_TEXTURE2);
		glBindTexture(GL_TEXTURE_2D,  camera.getTexShadow());
		xRayShader.bind();
		glUniform1i(13, 2);
		glUniformMatrix4fv(14, 1, GL_FALSE, glm::value_ptr(camera.getProjectionMatrix() * camera.getInverseWorldTransform() * world_transform));
		xToonTex.bind(0);
		glUniform1i(3, 0);
	}
	else
	{
		shader.bind();
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
	}

	glUniformMatrix4fv(0, 1, GL_FALSE, glm::value_ptr(
			        camera.getProjectionMatrix() * camera.getInverseWorldTransform() * world_transform));
	glUniformMatrix4fv(1, 1, GL_FALSE, glm::value_ptr(world_transform));
	glUniformMatrix3fv(2, 1, GL_FALSE, glm::value_ptr(glm::inverseTranspose(glm::mat3(world_transform))));

	glUniform3fv(5, 1, glm::value_ptr(glm::vec3(0.5, 0.5, 0.5)));

	glUniform3fv(6, 1, glm::value_ptr(light.getWorldPosition()));
	glUniform3fv(7, 1, glm::value_ptr(light.getColor()));
	glUniform3fv(8, 1, glm::value_ptr(camera.getWorldPosition()));
	glUniform1f(9, 10.f);
	glUniform3fv(10, 1, glm::value_ptr(glm::vec3(0.4, 0.4, 0.4)));
	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, light.getTexShadow());
	glUniform1i(11, 1); //this is very bad please fix
	glUniformMatrix4fv(12, 1, GL_FALSE, glm::value_ptr(light.getCameraMVP()));
	mesh.draw();
}
