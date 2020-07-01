#include "gl/cube_texture.h"
#include "disable_all_warnings.h"
DISABLE_WARNINGS_PUSH()
#include <fmt/format.h>
#include <stb_image.h>
DISABLE_WARNINGS_POP()

CubeTexture::CubeTexture(std::filesystem::path filePath)
{
    if (!std::filesystem::exists(filePath))
        throw ImageLoadingException(fmt::format("File {} does not exist", filePath.string().c_str()));

    // this gives path for folder

    // Load images from disk to CPU memory.
    std::string face[6] = { "right.jpg","left.jpg", "top.jpg","bottom.jpg","back.jpg", "front.jpg" };



    // Create a texture on the GPU with 3 channels with 8 bits each.
    m_texture = std::shared_ptr<GLuint>(new GLuint(), [](GLuint* p) {
        glDeleteTextures(1, p);
        delete p;
        });
    glCreateTextures(GL_TEXTURE_CUBE_MAP, 1, m_texture.get());

    int width, height, channels;
    for (int i = 0; i < 6; i++)
    {
        stbi_uc* pixels = stbi_load((filePath.string() + face[i]).c_str(), &width, &height, &channels, 3);
        if (!pixels)
            throw ImageLoadingException(fmt::format("Failed to load image file {}", (filePath.string() + face[i]).c_str()));

        assert(width > 0 && height > 0);

        glTexImage2D(
            GL_TEXTURE_CUBE_MAP_POSITIVE_X + i,
            0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, pixels
        );


    }
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
}

void CubeTexture::bind(GLint textureSlot) const 
{
    glActiveTexture(GL_TEXTURE0 + GLenum(textureSlot));
    glBindTexture(GL_TEXTURE_2D, *m_texture);
}