#version 420 core

layout(location = 0) in vec3 position;
layout(location = 1) in vec2 uv;
layout(location = 2) in vec3 normal;
layout(location = 3) in vec3 tangent;
layout(location = 4) in vec3 bitangent;
layout(location = 5) in vec4 boneID;
layout(location = 6) in vec4 boneWeights;

out vec4 o_fragPos;
out vec2 o_uv;
out vec3 o_normal;
out vec3 o_tangent;
out vec3 o_bitangent;

layout (std140, binding = 1) uniform Transform
{
    mat4 transform;
};

layout (std140, binding = 4) uniform Skeleton
{
    mat4 BoneTransformations[60];
};

layout (std140, binding = 5) uniform LightData
{
    mat4 projection;
    mat4 view;
};

void main()
{
	mat4 MVP = (transform * view) * projection;

    vec4 totalPosition = vec4(0.0f);
	for(int i = 0; i < 4; i++)
    {
        if(boneID[i] < -0.5) 
            continue;
        if(boneID[i] >= 60) 
        {
            totalPosition = vec4(position,1.0f);
            break;
        }
        vec4 localPosition = BoneTransformations[int(boneID[i])] * vec4(position,1.0f);
        totalPosition += localPosition * boneWeights[i];
    }
    

	gl_Position = totalPosition * MVP;
}