#version 450

layout(location = 0) uniform mat4 mvpMatrix;

layout(location = 0) in vec4 position;

void main()
{
    gl_Position = mvpMatrix * position;
}
