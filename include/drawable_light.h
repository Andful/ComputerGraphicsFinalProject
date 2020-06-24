#pragma once

#include "drawable.h"
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

class DrawableLight : public Drawable {
private:
	glm::vec3 lightColor{};
public:
	explicit DrawableLight(glm::vec3 color);
	DrawableLight(glm::vec3 color, const glm::vec3& baseTrans);
	const glm::vec3& getColor() const;
	void draw(const ICamera& camera, const Scene& scene, const DrawableLight &light) const;
	void update(const glm::mat4& transform, Scene& scene) override;

	void drawDepth(const ICamera &projection, const Scene &scene) const;
};