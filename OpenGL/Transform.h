#pragma once
#include "Components.h"
#include "glm.hpp"
#include "../glm/gtc/matrix_transform.hpp"


struct Transform : public Components{
	Transform():
	position(0),
	rotation(0),
	scale(1){}

	glm::vec3 position;
	glm::vec3 rotation;
	glm::vec3 scale;
	glm::mat4 toMat4(){
		glm::mat4 pos(
			1.f, 0.f, 0.f, position.x,
			0.f, 1.f, 0.f, position.y,
			0.f, 0.f, 1.f, position.z,
			0.f, 0.f, 0.f, 1.f
		);
		glm::mat4 scaleM(
			scale.x, 0.0f, 0.0f, 0.0f,
			0.0f, scale.y, 0.0f, 0.0f,
			0.0f, 0.0f, scale.z, 0.0f,
			0.0f, 0.0f, 0.0f, 1.0f
		);
		glm::mat4 rot(1.0f);
		rot = glm::rotate(rot, rotation.x, glm::vec3(0.0f, 0.0f, 1.0f));     // Roll around Z-axis
		rot = glm::rotate(rot, rotation.y, glm::vec3(1.0f, 0.0f, 0.0f));   // Pitch around X-axis
		rot = glm::rotate(rot, rotation.z, glm::vec3(0.0f, 1.0f, 0.0f)); 
		glm::mat4 modelMatrix = scaleM * (rot * pos);
		return modelMatrix;
	}
};