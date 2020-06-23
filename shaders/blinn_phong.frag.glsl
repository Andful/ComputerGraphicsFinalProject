#version 420
#extension GL_ARB_explicit_uniform_location : require

// Global variables for lighting calculations
//layout(location = 1) uniform vec3 viewPos;
layout(location = 3) uniform sampler2D colorMap;
layout(location = 4) uniform bool hasTexCoords;


layout(location = 5) uniform vec3 ks;
layout(location = 6 ) uniform vec3 light_pos;
layout(location = 7) uniform vec3  light_color;
layout(location = 8) uniform vec3 camera_pos;
layout(location = 9) uniform float shininess;
layout(location = 10) uniform vec3 kd;




// Output for on-screen color
layout(location = 0) out vec4 outColor;

// Interpolated output data from vertex shader
in vec3 fragPosition; // World-space position
in vec3 fragNormal; // World-space normal
in vec2 fragTexCoord; // text coord


void main()
{
      // get normalized light vector
    vec3 lamb_comp = normalize( light_pos - fragPosition );


    // compute lambertian surface color N.L* C* kd
    lamb_comp = (dot(normalize(fragNormal), lamb_comp)) * light_color * kd;

    // Clamping values so negative ones do not appear
    if(lamb_comp.x < 0.0f){
        lamb_comp = vec3(0.0f);
    }

    // calculate specular component ( reflection vector, incident light vec points to surface)
    //vec3 R = reflect( normalize(fragPosition - light_pos) , normalize(fragNormal) );
    vec3 surf_to_camera = normalize(camera_pos - fragPosition);
    // calculate halfway vector between viewer and light pos
    vec3 H = normalize( (normalize(light_pos - fragPosition)) + (surf_to_camera) );
    // fix for light behind surf
    float dot_p = pow( dot(H, normalize(fragNormal)) , shininess);
    if( dot_p < 0){
            dot_p = 0;
    }

    vec3 spec_comp = dot_p * ks;


    outColor = vec4(abs(spec_comp + lamb_comp), 1.0);
    //outColor = vec4(fragPosition, 1.0);

}