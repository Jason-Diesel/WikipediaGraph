#pragma once
#include <glm.hpp>
#include "../glm/gtc/matrix_transform.hpp"
#include "../glm/gtc/quaternion.hpp"

enum LightType { e_PointLight = 1, e_DirectionlLight = 2, e_SpotLight = 3 };

class Light{
public:
	glm::vec3 position;
	glm::vec3 color;
	float softness = 0;//not used in pointLight
	LightType lightType;
public:
	virtual glm::mat4 getLightViewProj() = 0;
	glm::mat4 getProjection();
//protected:
public:
	glm::mat4 projectonMatrix;
};