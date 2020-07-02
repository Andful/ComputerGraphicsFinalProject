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
layout(location = 4) uniform sampler2D tex;
layout(location = 5) uniform sampler2D texToon;

// Output for on-screen color
layout(location = 0) out vec4 outColor;

// Interpolated output data from vertex shader
in vec3 fragPosition; // World-space position
in vec3 fragNormal; // World-space normal
in vec2 fragTexCoord; // text coord


void main()
{
    // get normalized light vector
    vec3 lamb_comp = normalize( light_position - fragPosition);



    float dist_to_frag =  distance(camera_position , fragPosition)  / length(1.25 * camera_position);
    // Output the color from texture
    vec3 diffuse = texture( tex , vec2(clamp(fragPosition.y / 40, 0, 1), max(abs(dist_to_frag - 100), 0) )).xyz;


    vec4 fragLightCoord = light_mvp * vec4(fragPosition, 1.0);
    fragLightCoord.xyz /= fragLightCoord.w;
    fragLightCoord.xyz = fragLightCoord.xyz *0.5 + 0.5;
    vec3 shadowMapCoord = fragLightCoord.xyz;
    shadowMapCoord.z -=.0002;

    // compute lambertian surface color N.L* C* kd
    lamb_comp = (dot(normalize(fragNormal), lamb_comp)) * light_color * diffuse;
    // Clamping values so negative ones do not appear
    // also use abs
    lamb_comp = max((lamb_comp), 0);

    // calculate specular component ( reflection vector, incident light vec points to surface)
    //vec3 R = reflect( normalize(fragPosition - light_position) , normalize(fragNormal) );
    vec3 surf_to_camera = normalize(camera_position - fragPosition);
    // calculate halfway vector between viewer and light pos
    vec3 H = normalize( (normalize(light_position - fragPosition)) + (surf_to_camera) );
    // fix for light behind surf
    float dot_p = pow( dot(H, normalize(fragNormal)) , shininess );
    dot_p = max((dot_p), 0);


    vec3 spec_comp = dot_p * ks;


    vec3 final_brightness = abs(spec_comp); //+ abs(lamb_comp);
    float scale_factor = distance(camera_position, light_position );
    float dist = pow(max(1 - 2 * length(fragLightCoord.xy - vec2(0.5)), 0.f), 0.5);
    const int samples = 1;
    int count = 0;
    float shadowWeight = 0;
    ivec2 imageSize = textureSize(texShadow, 0);
    for(int i = -samples; i <= samples; i++)
    {
        for(int j = -samples; j <= samples; j++)
        {
            count++;
            vec3 offset = vec3(float(i)/float(imageSize.x), float(j)/float(imageSize.y), 0);
            shadowWeight += texture(texShadow, shadowMapCoord + offset);
        }
    }
    shadowWeight /= float(count);

    outColor = vec4(clamp(spec_comp + lamb_comp, 0, 1)* dist *shadowWeight, 1);


    // outColor = vec4(texture( tex , vec2(clamp(fragPosition.y / 1, 0, 1), max(abs(dist_to_frag - 100), 0) )).xyz, 1);
    //float dist = pow(max(1 - 2 * length(fragLightCoord.xy - vec2(0.5)), 0.f), 0.5);
    //float shadowMul = texture(texShadow, shadowMapCoord) * dist;
    //   outColor = texture( tex_toon , vec2(final_brightness.x * shadowMul, abs(dist_to_frag - 0.2) ));
    //    outColor = vec4(abs(vec3(dist_to_frag - 0.2)), 1.0);
}