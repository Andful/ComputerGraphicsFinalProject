#include <glm/glm.hpp>

#include "gl/texture.h"
#include "gl/framebuffer.h"

#include "util3D/light.h"
#include "util3D/camera.h"
#include "util3D/transformable.h"

class DirectionalLight : public Light, public Camera {
private:
    Texture texture;
    Framebuffer framebuffer;

    glm::mat4 projectionMatrix;
    glm::ivec2 dimensions;
    
public:
    DirectionalLight(const glm::mat4& _projectionMatrix, const glm::vec3& color, const glm::ivec2& _dimensions);
    void update(const glm::mat4& transform) override;
    const glm::mat4& getProjectionMatrix() const override;
    void addedToScene(Scene& _scene, std::shared_ptr<Transformable>& self) override;
    void renderMesh(const Scene& scene, const Mesh& mesh) const override;
    void prerender() override;
    void postrender() override;
    void bind() override;
};