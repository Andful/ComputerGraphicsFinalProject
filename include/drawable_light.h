#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <GL/glew.h>
#include "drawable.h"
#include "LightCamera.h"

class DrawableLight : public Drawable {
private:
	glm::vec3 lightColor{};
	std::vector<std::shared_ptr<LightCamera>> lightCamera;
	GLuint texShadow, framebuffer;
public:
	DrawableLight(glm::vec3 color, const glm::vec3& baseTrans);
	const glm::vec3& getColor() const;
	void draw(const ICamera& camera, const Scene& scene, const DrawableLight &light) const;
	void update(const glm::mat4& transform, Scene& scene) override;
	void drawDepth(const ICamera &projection, const Scene &scene) const;

	GLuint getFrameBuffer() const;
	GLuint getTexShadow() const;

	const int TEX_WIDTH = 4096;
	const int TEX_HEIGHT = 4096;

	glm::mat4 getCameraMVP() const;
};