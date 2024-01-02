#include "SpotLight.h"
#include <iostream>

glm::mat4 SpotLight::getLightViewProj()
{
    return getLightView() * projectonMatrix;
}

glm::mat4 SpotLight::getLightView()
{
	glm::vec3 direction;
	direction.x = cos(rotation.y) * cos(rotation.x);
	direction.y = sin(rotation.x);
	direction.z = sin(rotation.y) * cos(rotation.x);
	
	glm::vec3 cameraFront = glm::normalize(direction);
	glm::vec3 cameraRight = glm::normalize(glm::cross(glm::vec3(0,1,0), cameraFront));
	return glm::transpose(glm::lookAt(position, position + cameraFront, glm::cross(direction, cameraRight)));
}
