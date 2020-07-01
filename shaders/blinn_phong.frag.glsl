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

layout(location = 1) uniform sampler2DShadow texShadow;





// Output for on-screen color
layout(location = 0) out vec4 outColor;

// Interpolated output data from vertex shader
in vec3 fragPosition; // World-space position
in vec3 fragNormal; // World-space normal
in vec2 fragTexCoord; // text coord


void main()
{
    // get normalized light vector
    vec3 lamb_comp = normalize( light_position - fragPosition );

    vec4 fragLightCoord = light_mvp * vec4(fragPosition, 1.0);
    fragLightCoord.xyz /= fragLightCoord.w;
    fragLightCoord.xyz = fragLightCoord.xyz *0.5 + 0.5;
    float fragLightDepth = fragLightCoord.z;
    vec3 shadowMapCoord = fragLightCoord.xyz;
    shadowMapCoord.z -=.001;

    //if(abs(fragLightDepth - shadowMapDepth) > .0001) outColor = vec4(0,0,0, 1);

    // compute lambertian surface color N.L* C* kd
    lamb_comp = (dot(normalize(fragNormal), lamb_comp)) * light_color * kd;

    // Clamping values so negative ones do not appear
    lamb_comp = max(lamb_comp, 0);

    // calculate specular component ( reflection vector, incident light vec points to surface)
    //vec3 R = reflect( normalize(fragPosition - light_pos) , normalize(fragNormal) );
    vec3 surf_to_camera = normalize(camera_position - fragPosition);
    // calculate halfway vector between viewer and light pos
    vec3 H = normalize((normalize(light_position - fragPosition)) + (surf_to_camera));
    // fix for light behind surf
    float dot_p = pow(dot(H, normalize(fragNormal)), shininess);
    dot_p = max(dot_p, 0);

    vec3 spec_comp = dot_p * ks;

    float dist = pow(max(1 - 2 * length(fragLightCoord.xy - vec2(0.5)), 0.f), 0.5);
    outColor = vec4(clamp(spec_comp + lamb_comp, 0, 1) * dist, 1.0) * texture(texShadow, shadowMapCoord);
    //outColor = vec4(1.0, 1.0, 1.0, 1.0);
}