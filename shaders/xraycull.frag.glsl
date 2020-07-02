#version 420
#extension GL_ARB_explicit_uniform_location : require
layout(std140, binding = 0) uniform CameraUniform {
    mat4 mvp;
    vec3 camera_position;
};

layout(location = 3) uniform sampler2DShadow viewShadow;
//layout (location = 4) uniform mat4 mvp;

in vec3 fragPosition; // World-space position
layout(location = 0) out vec4 outColor;
void main() {
    vec4 viewCoord = mvp * vec4(fragPosition, 1.0);
    viewCoord.xyz /= viewCoord.w;
    viewCoord.xyz = viewCoord.xyz *0.5 + 0.5;
    vec3 viewMapCoord = viewCoord.xyz;
    viewMapCoord.z -=.0002;
    float distView = pow(max(1 - 2 * length(viewCoord.xy - vec2(0.5)), 0.f), 0.5);
    //here we check whether it's not occluded by the view.  if not, then we discard it.
    if (texture(viewShadow, viewMapCoord) > 0 && distView >.5) discard;
    //this is just for test purposes
}
