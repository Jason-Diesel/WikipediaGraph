#pragma once

#include <glm.hpp>

enum MaterialFlags{
	NONE = 0, 
	Albedo = 1,
	AmbientOcclusion = 2,
	HeightMap = 4, 
	NormalMap = 8
};

struct Material{
	//flags
	MaterialFlags materialFlags;
	//textures
	uint32_t Albedo; 
	uint32_t AmbientOcclusion; 
	uint32_t HeightMap; 
	uint32_t NormalMap; 

	float Ns;//defines the focus of specular highlights in the material. Ns values normally range from 0 to 1000, with a high value resulting in a tight, concentrated highlight.
	glm::vec3 Ka;
	glm::vec3 Kd;
	glm::vec3 Ks;
	glm::vec3 Ke;
	float Ni;//defines the optical density (aka index of refraction) in the current material. The values can range from 0.001 to 10. A value of 1.0 means that light does not bend as it passes through an object.
	float d;//specifies a factor for dissolve, how much this material dissolves into the background. A factor of 1.0 is fully opaque. A factor of 0.0 is completely transparent.
	
	bool tessellate;//Phong tessellation without heightmap, but if heightMap exist this will be ignored
	float tessellationLevel;
	Material(){
		tessellate = false;
		Albedo = 0;
		AmbientOcclusion = 0;
		HeightMap = 0;
		NormalMap = 0;
		materialFlags = MaterialFlags::NONE;
		Ns = 100.0f; 
		Ka = glm::vec3(0.5f,0.5f,0.5f);
		Kd = glm::vec3(0.5f,0.5f,0.5f);
		Ks = glm::vec3(0.5f,0.5f,0.5f);
		Ke = glm::vec3(0.5f,0.5f,0.5f);
		Ni = 1.0f;
		d = 1.0f;
	}
};
