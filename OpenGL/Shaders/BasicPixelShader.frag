#version 420 core
        
layout(location = 0) out vec4 finalPixel;

in vec4 o_fragPos;
in vec2 o_uv;
in vec3 o_normal;
in vec3 o_tangent;
in vec3 o_bitangent;

//texture materials
layout(binding = 0)uniform sampler2D ambientTexture;
layout(binding = 1)uniform sampler2D AOTexture;
layout(binding = 2)uniform sampler2D HeightMapTexture;
layout(binding = 3)uniform sampler2D NormalMapTexture;
layout(binding = 4)uniform sampler2DArray ShadowMaps;

//DEBUG SHIT
const vec3 c_lightColor = vec3(1,1,1);
const vec4 c_lightPos = vec4(0,20,0,0);//w is what kind of light it is

layout (std140, binding = 0) uniform Matrices
{
    mat4 projection;
    mat4 view;
	vec4 cameraPos;
};

layout (std140, binding = 2) uniform Material
{
    vec4 Ka;//last one is ni;
    vec4 Kd;//last one is d;
    vec4 Ks;//last one is NS;
    vec4 Ke;//last one has materialFlags;
};

const int MAXNUMBEROFLIGHTS = 6;
layout (std140, binding = 3) uniform ShadowData
{
    vec4 lightPos[MAXNUMBEROFLIGHTS];//4:th element is what type of light it is
	vec4 lightColors[MAXNUMBEROFLIGHTS];//4:th element is how hard the shadows should be
	mat4 lightViewProjection[MAXNUMBEROFLIGHTS];
	int nrOfLight;
};

float shadowLevel(float bias, int lightIndex, vec3 shadowMapChoords){
    const int shadowSoftness = int(lightColors[lightIndex].w);
    const vec2 pixelSize = vec2(1,1) / textureSize(ShadowMaps, lightIndex).xy;
    float shadowReturn = 0;
    
    if(shadowSoftness <= 0)
    {
        float sm = texture(ShadowMaps, vec3(shadowMapChoords.xy, lightIndex)).r;
        if(sm + bias < shadowMapChoords.z){
            shadowReturn = 1.0;
        }
        return shadowReturn;
    }
    for(int y = -shadowSoftness; y < shadowSoftness; y++){
        for(int x = -shadowSoftness; x < shadowSoftness; x++){
            float sm = texture(ShadowMaps, vec3(shadowMapChoords.xy + vec2(x,y) * pixelSize, lightIndex)).r;

            if(sm + bias < shadowMapChoords.z){
                shadowReturn += 1.0;
            }
        }
    }

    return shadowReturn / shadowSoftness;
}

void main(){ 
    vec3 newNormal = o_normal;
    if((int(Ke.w) & 8) != 0 && int(Kd.w) == 0){
        mat3 TBN = mat3(
            o_tangent, 
            o_bitangent, 
            o_normal
            );
    
        vec3 normalSample = texture(NormalMapTexture, o_uv).xyz;
        newNormal.x = normalSample.x * 2.0 - 1.0;
        newNormal.y = normalSample.y * 2.0 - 1.0;
        newNormal.z = normalSample.z * 2.0 - 1.0;
    
        newNormal = normalize(TBN * newNormal);
    }

    vec3 PixelLight = vec3(0,0,0); 
    vec4 color = texture(ambientTexture, o_uv);
    vec3 viewDir = normalize(cameraPos.xyz - o_fragPos.xyz);
    
    for(int i = 0; i < nrOfLight; i++){
        
        vec3 lightDir = normalize(lightPos[i].xyz - o_fragPos.xyz);
        float dist = length(lightPos[i].xyz - o_fragPos.xyz);
        
        vec3 ambientLight = Ka.xyz * lightColors[i].xyz;
        
        vec4 shadowHomo = o_fragPos * lightViewProjection[i];
        vec4 shadowMapCoords = vec4(shadowHomo.xyz / shadowHomo.w, 1);
        shadowMapCoords = shadowMapCoords * 0.5 + 0.5;

        
        double SM = texture(ShadowMaps, vec3(shadowMapCoords.xy, i)).r;
         
        float bias = max(0.05 * (1.0 - dot(newNormal, lightDir)), 0.005);
        
        float shadow = 0.0;
          
        if (lightPos[i].w == 1 ||
                shadowMapCoords.z <= 1.0f &&//E
				shadowMapCoords.x < 1 && shadowMapCoords.x > 0 &&
				shadowMapCoords.y < 1 && shadowMapCoords.y > 0 &&
                dot(o_normal.xyz, lightDir.xyz) > -0.1)  
        {
            if(lightPos[i].w != 1){
                shadow = shadowLevel(bias, i, shadowMapCoords.xyz);
            }

            vec3 defuse_light;
            float ammount_diffuse = max(dot(newNormal, lightDir), 0.0f);
            defuse_light = ammount_diffuse * Kd.xyz * lightColors[i].xyz;
            
            vec3 reflectDir = reflect(-lightDir, newNormal);
            float spec = pow(max(dot(viewDir, reflectDir), 0.0), Ks.w + 0.000001);
            vec3 specular = Ks.xyz * spec;
            
            PixelLight += clamp(ambientLight + defuse_light * (1.0 - shadow), 0.0, 1.0) + specular * (1.0 - shadow);
        }
        else{
            PixelLight += ambientLight;
        }    
    }
    finalPixel = vec4(PixelLight * color.xyz, color.a);
    

    //vec3 PixelLight = vec3(0,0,0); 
    //vec4 color = texture(ambientTexture, o_uv);
    //
    //vec3 viewDir = normalize(cameraPos.xyz - o_fragPos.xyz);
    //vec3 lightDir = normalize(c_lightPos.xyz - o_fragPos.xyz);
    //float dist = length(c_lightPos.xyz - o_fragPos.xyz);
    //
    //vec3 ambientLight = Ka.xyz * c_lightColor;
    //
    //vec3 defuse_light;
    //float ammount_diffuse = max(dot(o_normal, lightDir), 0.0f);
    //defuse_light = ammount_diffuse * Kd.xyz * c_lightColor;
    //
    //vec3 reflectDir = reflect(-lightDir, o_normal);
    //float spec = pow(max(dot(viewDir, reflectDir), 0.0), Ks.w + 0.000001);
    //vec3 specular = Ks.xyz * spec;
    //
    //PixelLight = clamp(ambientLight + defuse_light, 0.0, 1.0) + specular;
    //
    //
    //finalPixel = vec4(PixelLight * color.xyz, color.a);
}