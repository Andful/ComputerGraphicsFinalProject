#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <GL/glew.h>
#include "drawable.h"
//#include "LightCamera.h"

class LightCamera;

class DrawableLight : public Drawable {
private:
	glm::vec3 lightColor{};
	std::vector<std::shared_ptr<LightCamera>> lightCamera;
public:
	DrawableLight(glm::vec3 color, const glm::vec3& baseTrans);
	const glm::vec3& getColor() const;
	void draw(const Camera& camera, const Scene& scene, const DrawableLight &light) const;
	void update(const glm::mat4& transform, Scene& scene) override;
	void drawDepth(const Camera &projection, const Scene &scene) const;

	GLuint getFrameBuffer() const;
	GLuint getTexShadow() const;
	glm::mat4 getCameraMVP() const;

	int getWidth();

	int getHeight();
};