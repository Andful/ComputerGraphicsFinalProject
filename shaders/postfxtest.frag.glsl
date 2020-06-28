#version 420
#extension GL_ARB_explicit_uniform_location : require

layout(location = 0) uniform sampler2D imageTex;

layout(location = 0) out vec4 outColor;

in vec2 fragTexCoord;

void main() {
    vec4 color = texture(imageTex, fragTexCoord.xy);
    outColor= vec4(1-color.xyz, 1);
    //outColor=vec4(1, 1, 1, 1);
}
