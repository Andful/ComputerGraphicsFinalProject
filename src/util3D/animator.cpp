#include "util3D/animator.h"

void Animator::setTime(float time) {
    for (std::pair<std::weak_ptr<Transformable>, std::map<float, TransformSettings>>& e: data) {
        Transformable& transformable = *(e.first.lock());
        std::map<float, TransformSettings>& transformation  = (e.second);

        upper = 
    }
}

void Animator::add(std::weak_ptr<Transformable> transformable, std::map<float, TransformSettings> movement) {
    data.push_back(std::make_pair(transformable, movement));
}