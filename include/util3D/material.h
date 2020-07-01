#pragma once
#include <functional>

#include <GL/glew.h>

#include "util3D/scene.h"
#include "util3D/transformable.h"
#include "util3D/camera.h"
#include "gl/texture.h"

class Camera;
class Shader;

class Material {
private:
    std::shared_ptr<GLuint> ubo;
public:
    Material();
    virtual const FragmentShader& getFragmentShader() = 0;
    virtual const FragmentShader& getXrayCullShader() = 0;
    virtual const FragmentShader& getXrayShader() = 0;
    virtual const void* getUniformData() const = 0;
    virtual GLsizeiptr getUniformDataSize() const = 0;
    void initUniformBuffer() const;
    void updateUniformData() const;
    void bind() const;
    virtual void draw(const Scene& scene, const Geometry& geometry) const;
    virtual ~Material() = default;
};