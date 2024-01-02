#pragma once
#include "Light.h"

class DirectionalLight : public Light
{
	//position exist in Light
	//color exist in Light
public:
	DirectionalLight(glm::vec3 position, glm::vec3 rotation, glm::vec2 WH = glm::vec2(180, 180), glm::vec3 color = glm::vec3(1,1,1), glm::vec2 scale = glm::vec2(1,1), float softness = 0);
	glm::mat4 getLightViewProj();
	glm::mat4 getLightView();
	glm::vec3 rotation;
	glm::vec2 WidthHeight;
};