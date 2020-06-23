#pragma once
#include "drawable.h"

class ICamera : public Drawable
{
public:
    virtual glm::mat4 getProjectionMatrix() = 0;
    virtual void prerender() = 0;
    void render();
    virtual void postrender();
	void draw(const glm::mat4 &projection, const glm::mat4 &transform);
    virtual ~ICamera();

};