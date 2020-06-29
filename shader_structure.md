# Shader Structure

## Vertex Shader

```glsl
layout(std140, binding = 0) uniform CameraUniform {
    mat4 mvp;
    vec3 camera_position;
};

layout(std140, binding = 1) uniform WorldTransformationMatrix {
    mat4 world_transform;
    mat3 normal_transform;
};

layout(std140, binding = 2) uniform LightInformation {
    vec3 light_position;
    vec3 light_color;
    bool casts_shadow;
    mat4 light_mvp;
};

layout(std140, binding = 3) uniform GeometryParameters {
    1...
    2...
    3...
};
    
layout(std140, binding = 4) uniform MaterialParameters {
    1...
    2...
    3...
};

layout(location = 0) uniform sampler2D colorMap;
layout(location = 1) uniform sampler2DShadow texShadow;

out vec3 fragPosition;
out vec3 fragNormal;
out vec2 fragTexCoord;

layout(location = 0) in vec3 position;
layout(location = 1) in vec3 normal;
layout(location = 2) in vec2 texCoord;

void main()
{
    gl_Position = mvpMatrix * vec4(position, 1);
    
    fragPosition = (world_transform * vec4(position, 1)).xyz;
    fragNormal = normalModelMatrix * normal;
    fragTexCoord = texCoord;
}

```

