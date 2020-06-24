#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/string_cast.hpp>
#include <glm/gtc/matrix_inverse.hpp>

#include "drawable.h"
#include "mesh.h"
#include "shader.h"
#include "texture.h"
#include "camera.h"

class DrawableMesh : public Drawable {
private:
    Mesh mesh;
    Shader shader;
    Texture texture;
    Shader vertexShader;
public:
    DrawableMesh(const Mesh& _mesh, const Shader& _shader, const Shader& _vertexShader, const Texture& _texture);
    void draw(const ICamera& camera, const Scene& scene, const DrawableLight &light) const;
    void drawDepth(const ICamera &camera, const Scene &scene) const;
};