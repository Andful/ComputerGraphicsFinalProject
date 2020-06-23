#include "drawable_mesh.h"

DrawableMesh::DrawableMesh(const Mesh& _mesh, const Shader& _shader, const Texture& _texture) {
    mesh = _mesh;
    shader = _shader;
    texture = _texture;
}

void DrawableMesh::draw(const glm::mat4& projectionMatrix, const glm::mat4& transform,
		                const glm::vec3& camera_pos, const Light& light) {
    shader.bind();
    glUniformMatrix4fv(0, 1, GL_FALSE, glm::value_ptr(projectionMatrix*transform));
    glUniformMatrix4fv(1, 1, GL_FALSE, glm::value_ptr(transform));
    glUniformMatrix3fv(2, 1, GL_FALSE, glm::value_ptr(glm::inverseTranspose(glm::mat3(transform))));
    if (mesh.hasTextureCoords()) {
        texture.bind(0);
        glUniform1i(3, 0);
        glUniform1i(4, GL_TRUE);
    } else {
        glUniform1i(4, GL_FALSE);
    }
    mesh.draw();
}
