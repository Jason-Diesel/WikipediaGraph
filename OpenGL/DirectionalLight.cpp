#include "DirectionalLight.h"

DirectionalLight::DirectionalLight(glm::vec3 position, glm::vec3 rotation, glm::vec2 WH, glm::vec3 color, glm::vec2 scale, float softness):
	rotation(rotation),
	WidthHeight(WH)
{
	this->position = position;
	this->color = color;
	this->softness = softness;
	this->lightType = LightType::e_DirectionlLight;
	projectonMatrix = glm::transpose(glm::orthoLH(-(WH.x/2.f) * scale.x, (WH.x/2.f) * scale.x, -(WH.y/2.f) * scale.y, (WH.y/2.f) * scale.y, 0.1f, 2000.f));
}

glm::mat4 DirectionalLight::getLightViewProj()
{
	return getLightView() * projectonMatrix;
}

glm::mat4 DirectionalLight::getLightView()
{
	glm::vec3 direction;
	direction.x = cos(rotation.y) * cos(rotation.x);
	direction.y = sin(rotation.x);
	direction.z = sin(rotation.y) * cos(rotation.x);
	
	glm::vec3 cameraFront = glm::normalize(direction);
	glm::vec3 cameraRight = glm::normalize(glm::cross(glm::vec3(0,1,0), cameraFront));
	return glm::transpose(glm::lookAt(position, position + cameraFront, glm::cross(direction, cameraRight)));
}
