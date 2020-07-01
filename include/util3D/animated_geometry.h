#include "util3D/geometry.h"

class AnimatedGeometry :public Geometry{
private:
    bool m_hasTextureCoords { false };
    int animation_index = 0;
    std::vector<GLsizei> m_numIndices = {};
    std::shared_ptr<std::vector<GLuint>> m_ibo = nullptr;
    std::shared_ptr<std::vector<GLuint>> m_vbo = nullptr;
    std::shared_ptr<std::vector<GLuint>> m_vao = nullptr;
    VertexShader vertex_shader;
    void load(std::filesystem::path path);
public:
    AnimatedGeometry() = default;
    AnimatedGeometry(const AnimatedGeometry&) = default;
    AnimatedGeometry(std::filesystem::path filePath);
    bool hasTextureCoords() const;
    const VertexShader& getVertexShader() const override;
    // Bind VAO and call glDrawElements.
    void draw() const;
    void updateFrame();
    virtual const void* getUniformData() const;
    virtual GLsizeiptr getUniformDataSize() const;
    virtual ~AnimatedGeometry() = default;
};
