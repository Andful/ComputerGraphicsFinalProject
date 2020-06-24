#pragma once
#include "drawable.h"

class ICamera : public Drawable
{
public:
    virtual void prerender() = 0;
    void render(const Scene&);
    virtual void postrender();
	void draw(const ICamera&, const Scene& scene) const;
    virtual glm::mat4 getProjectionMatrix() const = 0;
    virtual ~ICamera();

};