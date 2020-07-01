#version 420
#extension GL_ARB_explicit_uniform_location : require

layout(std140, binding = 0) uniform CameraUniform {
    mat4 mvp;
    vec3 camera_position;
};
layout(std140, binding = 1) uniform WorldTransformationMatrix {
    mat4 world_transform;
    mat3 normal_transform;
};

layout(std140, binding = 2) uniform LightInformation {
    mat4 light_mvp;
    vec3 light_color;
    vec3 light_position;
    uint casts_shadow;
};

layout(std140, binding = 4) uniform MaterialParameters {
    vec3 ks;
    float shininess;
    vec3 kd;
};
layout(location = 0) in vec3 position;
out vec3 texCoords;

void main()
{

    vec4 pos = mvp * vec4(position + world_transform[3].xyz, 1);
    gl_Position = pos.xyww;

    texCoords = position;
}