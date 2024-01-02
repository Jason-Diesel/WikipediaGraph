#version 420 core

layout(location = 0) in vec3 position;
layout(location = 1) in vec2 uv;
layout(location = 2) in vec3 normal;
layout(location = 3) in vec3 tangent;
layout(location = 4) in vec3 bitangent;

layout (std140, binding = 1) uniform Transform
{
    mat4 transform;
};

layout (std140, binding = 5) uniform LightData
{
    mat4 projection;
    mat4 view;
};

void main()
{
    mat4 MVP = (transform * view) * projection;
	gl_Position = vec4(position.xyz, 1.0) * MVP;
}