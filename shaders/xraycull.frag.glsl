#version 120

layout(location = 3) uniform sampler2DShadow viewShadow;
layout(location = 0) uniform mat4 viewMVP;

in vec3 fragPosition; // World-space position

void main() {
    vec4 viewCoord = viewMVP * vec4(fragPosition, 1.0);
    viewCoord.xyz /= viewCoord.w;
    viewCoord.xyz = viewCoord.xyz *0.5 + 0.5;
    vec3 viewMapCoord = viewCoord.xyz;
    viewMapCoord.z -=.001;
    float distView = pow(max(1 - 2 * length(viewCoord.xy - vec2(0.5)), 0.f), 0.5);
    //here we check whether it's not occluded by the view.  if not, then we discard it.
    if (texture(viewShadow, viewMapCoord)  > 0 && distView > .5) discard;
}
