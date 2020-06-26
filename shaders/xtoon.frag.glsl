#version 420
#extension GL_ARB_explicit_uniform_location : require

// Global variables for lighting calculations
//layout(location = 1) uniform vec3 viewPos;
layout(location = 3) uniform sampler2D tex_toon;
layout(location = 4) uniform bool hasTexCoords;


layout(location = 5) uniform vec3 ks;
layout(location = 6 ) uniform vec3 light_pos;
layout(location = 7) uniform vec3  light_color;
layout(location = 8) uniform vec3 camera_pos;
layout(location = 9) uniform float shininess;
layout(location = 10) uniform vec3 kd;



layout(location = 11) uniform sampler2DShadow texShadow;
layout(location = 12) uniform mat4 lightMVP;

layout(location = 13) uniform sampler2DShadow viewShadow;
layout(location = 14) uniform mat4 viewMVP;

// Output for on-screen color
layout(location = 0) out vec4 outColor;

// Interpolated output data from vertex shader
in vec3 fragPosition; // World-space position
in vec3 fragNormal; // World-space normal
in vec2 fragTexCoord; // text coord


void main()
{
    vec4 viewCoord = viewMVP * vec4(fragPosition, 1.0);
    viewCoord.xyz /= viewCoord.w;
    viewCoord.xyz = viewCoord.xyz *0.5 + 0.5;
    vec3 viewMapCoord = viewCoord.xyz;
    viewMapCoord.z -=.001;
    float distView = pow(max(1 - 2 * length(viewCoord.xy - vec2(0.5)), 0.f), 0.5);
    //here we check whether it's not occluded by the view.  if not, then we discard it.
    //if (texture(viewShadow, viewMapCoord)  > 0 && distView > .5) discard;


    vec4 fragLightCoord = lightMVP * vec4(fragPosition, 1.0);
    fragLightCoord.xyz /= fragLightCoord.w;
    fragLightCoord.xyz = fragLightCoord.xyz *0.5 + 0.5;
    vec3 shadowMapCoord = fragLightCoord.xyz;
    shadowMapCoord.z -=.01;



    // get normalized light vector
    vec3 lamb_comp = normalize( fragPosition - light_pos);
    // compute lambertian surface color N.L* C* kd
    lamb_comp = (dot(normalize(fragNormal), lamb_comp)) * light_color * kd;

    // calculate specular component ( reflection vector, incident light vec points to surface)
    //vec3 R = reflect( normalize(fragPosition - light_pos) , normalize(fragNormal) );
    vec3 surf_to_camera = normalize(camera_pos - fragPosition);
    // calculate halfway vector between viewer and light pos
    vec3 H = normalize( (normalize(light_pos - fragPosition)) + (surf_to_camera) );
    // fix for light behind surf
    float dot_p = pow( dot(H, normalize(fragNormal)) , shininess );
    if( dot_p < 0){
            dot_p = 0;
    }

    vec3 spec_comp = dot_p * ks;


    vec3 final_brightness = abs(spec_comp); //+ abs(lamb_comp);
    float scale_factor = distance(camera_pos, light_pos );
    

    float dist_to_frag =  distance(camera_pos , fragPosition)  / length(1.25 * camera_pos); 
    // Output the color from texture
    float dist = pow(max(1 - 2 * length(fragLightCoord.xy - vec2(0.5)), 0.f), 0.5);
    float shadowMul = texture(texShadow, shadowMapCoord) * dist;
    outColor = texture( tex_toon , vec2(final_brightness.x, abs(dist_to_frag - 0.2) ));
    //    outColor = vec4(abs(vec3(dist_to_frag - 0.2)), 1.0);
}