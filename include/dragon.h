#pragma once

#include "drawable.h"
#include "mesh.h"
#include "shader.h"
#include "texture.h"

class Dragon : public Drawable {
private:
    Mesh mesh;
    Shader shader;
    Texture texture;
public:
    Dragon(Mesh mesh, Shader shader, Texture texture) {
        this -> mesh = mesh;
        this -> shader = shader;
        this -> texture = texture;
    }

    void draw(const glm::mat4& transform) {

    }
}