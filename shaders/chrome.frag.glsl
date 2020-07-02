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

layout(location = 3) uniform sampler2DShadow texShadow;
layout(location = 4) uniform samplerCube envmap;
layout(location = 5) uniform sampler2D textoon;

// Output for on-screen color
layout(location = 0) out vec4 outColor;

// Interpolated output data from vertex shader
in vec3 fragPosition; // World-space position
in vec3 fragNormal; // World-space normal
in vec2 fragTexCoord; // text coord



void main() {
    vec3 surf_to_camera = normalize(fragPosition - camera_position);
    vec3 reflection = reflect(surf_to_camera, normalize(fragNormal));
    vec4 surfaceColor = texture(envmap, reflection);
    outColor = vec4(surfaceColor.xyz, 1);
}