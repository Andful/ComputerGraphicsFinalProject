#version 420
#extension GL_ARB_explicit_uniform_location : require

layout(location = 0) uniform sampler2D imageTex;
layout(location = 1) uniform vec2 imageSize;
layout(location = 2) uniform int SAMPLES;
layout(location = 0) out vec4 outColor;

in vec2 fragTexCoord;
void main() {
    outColor = vec4(1 - texture(imageTex, fragTexCoord).xyz, 1);
    gl_FragDepth = texture(imageDepth, fragTexCoord.xy).x;
    ;

}
