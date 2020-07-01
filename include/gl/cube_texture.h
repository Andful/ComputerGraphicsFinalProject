#pragma once
#include "texture.h"


class CubeTexture : public Texture
{

public:
	CubeTexture() = default;
	CubeTexture(const CubeTexture&) = default;
	CubeTexture(std::filesystem::path filePath);
	void bind(GLint textureSlot) const override;
};