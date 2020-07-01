
#version 420
#extension GL_ARB_explicit_uniform_location : require

layout(location = 3) uniform sampler2DShadow shadow;
layout(location = 4) uniform samplerCube skybox;

in vec3 texCoords;

layout(location = 0) out vec4 fragColor;

void main()
{
    fragColor = texture(skybox, texCoords);
}