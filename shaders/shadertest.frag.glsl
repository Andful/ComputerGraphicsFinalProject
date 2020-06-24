#version 420
layout(location=0) out vec4 outColor;

in vec3 fragPosition;
in vec3 fragNormal;
void main() {
 outColor = vec4(fragPosition, 1.0);
}
