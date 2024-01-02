#pragma once

#include <glm.hpp>
#include "../glm/gtc/matrix_transform.hpp"
#include "../glm/gtc/quaternion.hpp"
#include "ShaderHandler.h"

class Camera{
public:
	Camera(ShaderHandler* shaderHandler, glm::vec3 position = glm::vec3(), glm::vec3 rotation = glm::vec3(), float FOV = 45);
	void init();
	void setPosition(glm::vec3 newPosition);
	void setRotation(glm::vec3 rotation);
	void move(glm::vec3 direction);
	void rotate(glm::vec2 rotation);//skipping Z
	void moveInDirection(glm::vec3 direction = glm::vec3(0,0,1));
	void setProjection(glm::mat4 proj);
	void Update();
	glm::vec3 getRotation() const;
	glm::vec3 getPosition() const;
	//DEBUG
	glm::mat4 getProjection();
	glm::mat4 getView();
private:
	void RotationMatrix();
	glm::vec3 translation;
	cameraBuffer cb;
	UniformBuffer pv;
	glm::vec3 position;
	glm::vec3 rotation;
	float FOV;
	ShaderHandler* shaderHandler;
};
