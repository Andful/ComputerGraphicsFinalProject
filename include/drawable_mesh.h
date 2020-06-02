#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/string_cast.hpp>
#include <glm/gtc/matrix_inverse.hpp>

#include "drawable.h"
#include "mesh.h"
#include "shader.h"
#include "texture.h"

class DrawableMesh : public Drawable {
private:
    Mesh mesh;
    Shader shader;
    Texture texture;
public:
    DrawableMesh(const Mesh& _mesh, const Shader& _shader, const Texture& _texture);
    void draw(const glm::mat4& projectionMatrix, const glm::mat4& transform);
};