#version 420
#extension GL_ARB_explicit_uniform_location : require

layout(location = 0) uniform sampler2D imageTex;
layout(location = 1) uniform vec2 imageSize;
layout(location = 2) uniform int SAMPLES;
layout(location = 0) out vec4 outColor;

in vec2 fragTexCoord;
void main() {
    vec3 color = vec3(0,0,0);
    int total = 0;
    for(int i = -SAMPLES; i <= SAMPLES; i++)
    {
        for(int j = -SAMPLES; j <=SAMPLES; j++)
        {
            vec2 offset = vec2(i/imageSize.x, j/imageSize.y);
            color += texture(imageTex, fragTexCoord.xy + offset).xyz;
            total++;
        }
    }
    color /= total;
    outColor= vec4(color.xyz, 1);
}
