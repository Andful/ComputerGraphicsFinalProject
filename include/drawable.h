#include <vector>
#include <memory>
#include <glm/glm.hpp>

class Drawable {
private:
    glm::mat4 transform_m;
    glm::mat4 translate_m;
    glm::mat4 rotation_m;
    std::vector<std::shared_ptr<Drawable>> children;
public:
    void translate(vec3 translate)
};