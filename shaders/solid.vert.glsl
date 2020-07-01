#version 420
#extension GL_ARB_explicit_uniform_location : require

layout(location = 0) uniform mat4 mvpMatrix;
layout(location = 0) in vec3 position;

void main()
{
    gl_Position = mvpMatrix * vec4(position, 1);
}