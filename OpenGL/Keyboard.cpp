#include "Keyboard.h"

Keyboard::Keyboard(GLFWwindow* wnd)
{
	this->wnd = wnd;
	for(int i = 0; i < 349; i++){
		LastKeyAction[i] = false;
		currentKeyAction[i] = false;
	}
}

void Keyboard::update()
{
	//is memcpy faster?
	for(int i = 0; i < 349; i++){
		LastKeyAction[i] = currentKeyAction[i];
	}
}

bool Keyboard::getKeyDown(unsigned char key)
{
	currentKeyAction[key] = (glfwGetKey(this->wnd, key) == GLFW_PRESS);
	return currentKeyAction[key];
}

bool Keyboard::getKeyDown(int key)
{
	currentKeyAction[key] = (glfwGetKey(this->wnd, key) == GLFW_PRESS);
	return currentKeyAction[key];
}

bool Keyboard::getKeyUp(unsigned char key)
{
	currentKeyAction[key] = (glfwGetKey(this->wnd, key) == GLFW_RELEASE);
	return currentKeyAction[key];
}

bool Keyboard::getKeyUp(int key)
{
	currentKeyAction[key] = (glfwGetKey(this->wnd, key) == GLFW_RELEASE);
	return currentKeyAction[key];
}

bool Keyboard::getKeyJustDown(unsigned char key)
{
	return (getKeyDown(key) && LastKeyAction[key] != currentKeyAction[key]);
}

bool Keyboard::getKeyJustDown(int key)
{
	return (getKeyDown(key) && LastKeyAction[key] != currentKeyAction[key]);
}

bool Keyboard::getKeyReleased(unsigned char key)
{
	return (getKeyUp(key) && LastKeyAction[key] != currentKeyAction[key]);
}

bool Keyboard::getKeyReleased(int key)
{
	return (getKeyUp(key) && LastKeyAction[key] != currentKeyAction[key]);
}
