#include <memory>
#include <exception>
#include <stdexcept>
#include "icamera.h"

void ICamera::prerender() {}

void ICamera::render(const Scene& scene)
{
}

void ICamera::draw(const Camera& camera,const Scene& scene, const DrawableLight &light) const {}
void ICamera::drawDepth(const Camera &projection, const Scene &scene) const {}

void ICamera::postrender(){}

ICamera::~ICamera(){}