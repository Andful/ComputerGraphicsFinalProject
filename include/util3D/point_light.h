#include "util3D/light.h"
#include "util3D/transformable.h"

class PointLight : public Light, public Transformable {
public:
    PointLight();
    PointLight(const glm::vec3& color);
    void update(const glm::mat4& transform) override;
    void addedToScene(Scene& _scene, std::shared_ptr<Transformable>& self) override;
};