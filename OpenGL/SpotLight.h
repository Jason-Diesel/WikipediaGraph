#pragma once
#include "Light.h"

class SpotLight : public Light{
	//position exist in Light
	//color exist in Light
	//
	//
public:
	glm::vec3 rotation;
	glm::vec2 WidthHeight;
	glm::mat4 getLightViewProj();
	glm::mat4 getLightView();

	SpotLight(glm::vec3 position, glm::vec3 rotation, glm::vec2 WH = glm::vec2(180, 180), glm::vec3 color = glm::vec3(1,1,1), float FOV = 90):
	rotation(rotation),
	WidthHeight(WH)
	{
		this->position = position;
		this->color = color;
		this->lightType = LightType::e_SpotLight;
		projectonMatrix = glm::transpose(glm::perspectiveFovLH(glm::radians(FOV), WH.x, WH.y, 0.1f, 2000.f));
	}
};