#pragma once
#include "drawable.h"

class ICamera : public Drawable
{
public:
    virtual void prerender();
    void render(const Scene&);
    virtual void postrender();
	void draw(const Camera&, const Scene& scene, const DrawableLight &light) const;
	void drawDepth(const Camera& cam, const Scene& scene) const;
    virtual glm::mat4 getProjectionMatrix() const = 0;
    virtual ~ICamera();

};