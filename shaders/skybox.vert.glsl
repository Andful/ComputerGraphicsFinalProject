#version 420
#extension GL_ARB_explicit_uniform_location : require

layout(location = 0) uniform mat4 mvpMatrix;
layout(location = 1) uniform mat4 modelMatrix;
// Normals should be transformed differently than positions:
// https://paroj.github.io/gltut/Illumination/Tut09%20Normal%20Transformation.html
layout(location = 2) uniform mat3 normalModelMatrix;

layout(location = 0) in vec3 position;


out vec3 texCoords;

void main()
{
    gl_Position = mvpMatrix * vec4(position, 1);
    texCoords = position;
}
