#version 420
#extension GL_ARB_explicit_uniform_location : require

layout(std140, binding = 0) uniform CameraUniform {
    mat4 mvp;
    vec3 camera_position;
};
layout(location = 0) in vec3 position;
out vec3 texCoords;

void main()
{
    gl_Position = mvp * vec4(position, 1);
    texCoords = position;
}