#pragma once

#include <map>
#include <memory>
#include <GL/glew.h>
#include "drawable.h"
#include "group.h"
#include "shader.h"

class DrawableLight;
class Camera;

class Scene: public Drawable 
{
private:
	//define statics for quad, probably should make this an object later
	const static int quadTriCount = 2;
	constexpr static unsigned int quadTriList[] = {0, 1, 2, 2, 1, 3};
	constexpr static float quadVerts[] = {-1.0, -1.0, 0, 1.0, -1.0,0,  -1.0, 1.0, 0, 1.0, 1.0, 0};
	//constexpr static float quadVerts[] = {-1.0, -1.0, 1.0, -1.0,  -1.0, 1.0, 1.0, 1.0};


	GLuint ibo, vbo, vao;

    std::vector<std::shared_ptr<DrawableLight>> lightData;
    GLuint framebuffers[2], depthtextures[2], colortextures[2];
    int TEX_WIDTH, TEX_HEIGHT;
    std::vector<std::shared_ptr<Shader>> postShaders = {};

public:
	bool useXRay = true;
	int samples = 0;
    Scene(int, int);
    const std::vector<std::shared_ptr<DrawableLight>>& getLightData() const;
    void addLight(const std::shared_ptr<DrawableLight>& light);
    void draw(const Camera& camera, const Scene& scene, const DrawableLight& light) const;
	void drawDepth(const Camera& camera,const Scene& scene) const;
    using Drawable::update;
    void update();

	void render(Camera& camera) const;

	void toggleXRay();

	void addPostShader(const std::shared_ptr<Shader> &shader);
};