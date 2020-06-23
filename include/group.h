#pragma once
#include "drawable.h"
#include <glm/glm.hpp>


class Group : public Drawable
{
public:
    void draw(const glm::mat4& projection, const glm::mat4& transform);
};