#version 420
#extension GL_ARB_explicit_uniform_location : require

layout(location = 0) uniform sampler2D imageTex;
layout(location = 1) uniform vec2 imageSize;
layout(location = 2) uniform sampler2D imageDepth;
layout(location = 0) out vec4 outColor;

in vec2 fragTexCoord;
void main() {
    vec3 color = vec3(0,0,0);
    int total = 0;
    float refDepth = texture(imageDepth, vec2(.5,.5)).x;
    float thisDepth = texture(imageDepth, fragTexCoord.xy).x;
    int SAMPLES = int(floor(abs(refDepth-thisDepth) * 12));
    for(int i = -SAMPLES; i <= SAMPLES; i++)
    {
        for(int j = -SAMPLES; j <=SAMPLES; j++)
        {
            vec2 offset = vec2(i/imageSize.x, j/imageSize.y);
            color += texture(imageTex, fragTexCoord.xy + offset*4).xyz;
            total++;
        }
    }
    color /= total;

    outColor= vec4(color, 1);
    gl_FragDepth = thisDepth;
}