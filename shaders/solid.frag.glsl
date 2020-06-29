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
    vec3 light_position;
    vec3 light_color;
    bool casts_shadow;
    mat4 light_mvp;
};

layout(std140, binding = 4) uniform MaterialParameters {
    vec3 color;
};

layout(location = 0) out vec4 outColor;

void main() {
 outColor = vec4(color, 0.0);
}