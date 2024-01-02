#version 420 core

layout(location = 0) in vec2 position;
//instanced
layout(location = 1) in vec4 colors;
layout(location = 2) in mat4 transform;

out vec3 o_color;

layout (std140, binding = 6) uniform Camera2D
{
    vec4 cameraOffset;
};

void main()
{
	vec4 pos = (vec4(vec3((position.xy), 1), 1.0f) * transform);
	pos.xy *= cameraOffset.z;
	pos.xy += cameraOffset.xy; 
	gl_Position = pos;
	o_color = colors.xyz;
}