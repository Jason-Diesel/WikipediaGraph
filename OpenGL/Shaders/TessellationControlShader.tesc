#version 420 core

layout (vertices=3) out;

layout (std140, binding = 0) uniform Matrices
{
    mat4 projection;
    mat4 view;
	vec4 cameraPos;
};

layout (std140, binding = 1) uniform Transform
{
    mat4 transform;
};

in vec3 o_position[];
in vec2 o_uv[];
in vec3 o_normal[];
in vec3 o_tangent[];
in vec3 o_bitangent[];

out vec3 i_position[];
out vec2 i_uv[];
out vec3 i_normal[];
out vec3 i_tangent[];
out vec3 i_bitangent[];

float GetTessLevel(float Distance0, float Distance1)
{
    float AvgDistance = (Distance0 + Distance1) / 2.0;

    float MaxDistance = 100;
    float McDDistance = 5;//maccers is oppisete of max (swedish Australia joke)
    float MaxLod = 12;
    float McDLod = 1;

    if (AvgDistance > MaxDistance)
    {
        AvgDistance = MaxDistance - 0.1;
    }
    AvgDistance -= MaxDistance;
    AvgDistance = -AvgDistance;
    
    float proc = AvgDistance / MaxDistance;
    return proc * MaxLod;
}

void main()
{
    // ----------------------------------------------------------------------
    // pass attributes through
    gl_out[gl_InvocationID].gl_Position = gl_in[gl_InvocationID].gl_Position;
    i_position[gl_InvocationID] = o_position[gl_InvocationID];
    i_uv[gl_InvocationID] = o_uv[gl_InvocationID];
    i_normal[gl_InvocationID] = o_normal[gl_InvocationID];
    i_tangent[gl_InvocationID] = o_tangent[gl_InvocationID];
    i_bitangent[gl_InvocationID] = o_bitangent[gl_InvocationID];

    float EyeToVertexDistance0 = distance(cameraPos.xyz, (vec4(i_position[0],1) * transform).xyz);
    float EyeToVertexDistance1 = distance(cameraPos.xyz, (vec4(i_position[1],1) * transform).xyz);
    float EyeToVertexDistance2 = distance(cameraPos.xyz, (vec4(i_position[2],1) * transform).xyz);

    gl_TessLevelOuter[0] = GetTessLevel(EyeToVertexDistance1, EyeToVertexDistance2);
    gl_TessLevelOuter[1] = GetTessLevel(EyeToVertexDistance2, EyeToVertexDistance0);
    gl_TessLevelOuter[2] = GetTessLevel(EyeToVertexDistance0, EyeToVertexDistance1);

    gl_TessLevelInner[0] = gl_TessLevelOuter[2];
}