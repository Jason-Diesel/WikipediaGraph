#version 420 core

layout (triangles, fractional_odd_spacing, ccw) in;

layout(binding = 2)uniform sampler2D HeightMapTexture;

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

layout (std140, binding = 2) uniform Material
{
    vec4 Ka;//last one is ni;
    vec4 Kd;//last one is d;
    vec4 Ks;//last one is NS;
    vec4 Ke;//last one has materialFlags;
};

in vec3 i_position[];
in vec2 i_uv[];
in vec3 i_normal[];
in vec3 i_tangent[];
in vec3 i_bitangent[];


out vec4 o_fragPos;
out vec2 o_uv;
out vec3 o_normal;
out vec3 o_tangent;
out vec3 o_bitangent;

//thanks ogldev! https://ogldev.org/www/tutorial30/tutorial30.html
vec2 interpolate2D(vec2 v0, vec2 v1, vec2 v2)
{
    return vec2(gl_TessCoord.x) * v0 + vec2(gl_TessCoord.y) * v1 + vec2(gl_TessCoord.z) * v2;
}

vec3 interpolate3D(vec3 v0, vec3 v1, vec3 v2)
{
    return vec3(gl_TessCoord.x) * v0 + vec3(gl_TessCoord.y) * v1 + vec3(gl_TessCoord.z) * v2;
}

vec3 calcPlanePointPos(vec3 normal, vec3 planepos, vec3 origin)
{
    normal = normalize(normal);
    float d = dot(normal, planepos);
    float t = (d - dot(normal, origin)) / dot(normal, normal);
    vec3 thePos = origin + (normal * t);
    return thePos;
};


void main()
{ 
    mat4 MVP = (transform * view) * projection; 
    vec3 position = interpolate3D(i_position[0], i_position[1], i_position[2]);
    o_uv = interpolate2D(i_uv[0], i_uv[1], i_uv[2]);
    o_normal = interpolate3D(i_normal[0], i_normal[1], i_normal[2]);
    o_tangent = interpolate3D(i_tangent[0], i_tangent[1], i_tangent[2]);
    o_bitangent = interpolate3D(i_bitangent[0], i_bitangent[1], i_bitangent[2]);

    //if we have a height map do this
    if((int(Ke.w) & 4) != 0){

        float height = texture(HeightMapTexture, o_uv).x;
        position += (normalize(o_normal) * height * 20);//times something here
    
        o_fragPos = vec4(position, 1) * transform;
        gl_Position = vec4(position, 1) * MVP;
        
    }
    else{
        o_fragPos = vec4(position, 1) * transform;
        gl_Position = vec4(position, 1) * MVP;//some other time we fix this
    }//else we do phong tessellation
    //else{
    //    const float alpha = 0.75;
    //    vec3 P = position;
    //    vec3 q0 = calcPlanePointPos(i_normal[0], i_position[0], position);
    //    vec3 q1 = calcPlanePointPos(i_normal[1], i_position[1], position);
    //    vec3 q2 = calcPlanePointPos(i_normal[2], i_position[2], position);
    //    mat3 PIijk = mat3(
    //        q0, q1, q2
    //    );
    //    position = vec3((1 - alpha) * P + ((alpha * gl_TessCoord.xyz) * PIijk));
    //    
    //    o_fragPos = vec4(position, 1) * transform;
    //    gl_Position = vec4(position, 1) * MVP;
    //}
    o_normal = normalize((vec4(o_normal, 0.0) * transform).xyz);
    o_tangent = normalize((vec4(o_tangent, 0.0) * transform).xyz);
    o_bitangent = normalize((vec4(o_bitangent, 0.0) * transform).xyz);
}