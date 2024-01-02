#include "Camera.h"

Camera::Camera(ShaderHandler* shaderHandler, glm::vec3 position, glm::vec3 rotation, float FOV):
	FOV(FOV), position(position), rotation(rotation)
{
	cb.p = glm::transpose(glm::perspectiveFovLH(glm::radians(FOV), 16.f, 9.f, 0.1f, 2000.f));
	//cb.p = glm::transpose(glm::orthoLH(0.f, 1920.f, 0.f, 1080.f, 0.1f, 2000.f));
	//cb.v = glm::lookAt(position, rotation, glm::vec3(0.f,1.f,0.f));
	cb.v = glm::lookAt(position, rotation, glm::vec3(0.f,0.f,-1.f));
	this->shaderHandler = shaderHandler;
}

void Camera::init()
{
	pv.init(cb, "Matrices", 0);
}

void Camera::setPosition(glm::vec3 newPosition)
{
	this->position = newPosition;
}

void Camera::setRotation(glm::vec3 rotation)
{
	this->rotation = rotation;
}

void Camera::move(glm::vec3 direction)
{
	this->position += direction;
}

void Camera::rotate(glm::vec2 rotation)
{
	this->rotation.x += rotation.y * 0.1f;
	this->rotation.y -= rotation.x * 0.1f;
}

void Camera::moveInDirection(glm::vec3 direction)
{
	this->translation = direction;
	glm::mat4 rotationMatrix = glm::rotate(glm::mat4(1.0f), rotation.y, glm::vec3(0.0f, 1.0f, 0.0f)) *
                           glm::rotate(glm::mat4(1.0f), rotation.x, glm::vec3(1.0f, 0.0f, 0.0f));
	translation = glm::vec3(rotationMatrix * glm::vec4(translation, 1.0f));
	this->position.x -= translation.x;
	this->position.z -= translation.z;
}

void Camera::setProjection(glm::mat4 proj)
{
	cb.p = proj;
}

void Camera::Update()
{
	RotationMatrix();
	cb.camPos = glm::vec4(position, 1.0f);
	pv.UpdateData(cb);
	pv.setUniform(shaderHandler->getCurrentShader());
}

glm::vec3 Camera::getRotation() const
{
	return this->rotation;
}

glm::vec3 Camera::getPosition() const
{
	return this->position;
}

glm::mat4 Camera::getProjection()
{
	return cb.p;
}

glm::mat4 Camera::getView()
{
	return cb.v;
}

void Camera::RotationMatrix()
{
	glm::vec3 direction;
	direction.x = cos(rotation.y) * cos(rotation.x);
	direction.y = sin(rotation.x);
	direction.z = sin(rotation.y) * cos(rotation.x);
	
	glm::vec3 cameraFront = glm::normalize(direction);
	glm::vec3 cameraRight = glm::normalize(glm::cross(glm::vec3(0,1,0), cameraFront));
	
	cb.v = glm::transpose(glm::lookAt(position, position + cameraFront, glm::cross(direction, cameraRight)));
}





