#include <memory>
#include <vector>
#include <map>
#include <utility>
#include <optional>

#include <glm/glm.hpp>

#include "util3D/transformable.h"

typedef struct _TransformSettings {
    std::optional<std::pair<glm::vec3, glm::vec3>> translatrion;
    std::optional<std::pair<glm::quat, glm::quat>> rotation;
    std::optional<std::pair<glm::vec3, glm::vec3>> scaling;
} TransformSettings;


class Animator {
    std::vector<std::pair<std::weak_ptr<Transformable>, std::map<float, TransformSettings>>> data;
    void setTime(float time);
    void add(std::weak_ptr<Transfirmable> transformable, std::map<float, TransformSettings> movement);
}