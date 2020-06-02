#include <memory>
#include <exception>
#include "icamera.h"

void ICamera::render()
{
    this -> prerender();
    if (parents.size() == 1)
    {
        glm::mat4 transformation = getInverseTransform();

        std::shared_ptr<Drawable> node = parents[0].lock();
        transformation = node->getInverseTransform()*transformation;
        while(node -> parents.size() > 0)
        {   
            if (node -> parents.size() == 1 && !node -> parents[0].expired())
            {
                node = node -> parents[0].lock();
                transformation = node->getInverseTransform()*transformation;
            }
            else
            {
                throw std::logic_error("Camera has multiple parents");
            }  
        }
        node -> render(this->getProjectionMatrix(), transformation);
    }
    else
    {
        throw std::logic_error("Camera has multiple parents");
    }

    this -> postrender();
}

void ICamera::draw(const glm::mat4& projection, const glm::mat4& transform){}

void ICamera::postrender(){}

ICamera::~ICamera(){}