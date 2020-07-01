#version 420
#extension GL_ARB_explicit_uniform_location : require
//To write post-processing effects I made use of the tutorials found here:
// http://adrien.io/opengl-course/lesson-2-lighting/
// http://adrien.io/opengl-course/post-processing/

layout(location = 0) in vec2 position;

out vec2 fragTexCoord;

void main() {
    //we want to render a flat quad to the screen so z is always 0.
    gl_Position = vec4(position.xy, 0, 1);
    fragTexCoord = position.xy *0.5 + 0.5;
}