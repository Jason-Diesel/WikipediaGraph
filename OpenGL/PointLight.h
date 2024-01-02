#pragma once
#include "Light.h"

class PointLight : public Light
{
	//position exist in Light
	//color exist in Light
	// 
	//Nothing more is done here
	//everything exist in light
public:
	PointLight(glm::vec3 position, glm::vec3 color = glm::vec3(1,1,1))
	{
		this->projectonMatrix = glm::mat4(1);
		this->lightType = LightType::e_PointLight;
		this->color = color;
		this->position = position;
	}
	glm::mat4 getLightViewProj(){
		return glm::mat4(1);
	}
};
