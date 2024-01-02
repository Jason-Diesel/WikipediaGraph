#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm.hpp>

class Keyboard{
public:
	Keyboard(GLFWwindow* wnd);
	void update();
	bool getKeyDown(unsigned char key);
	bool getKeyDown(int key);
	bool getKeyUp(unsigned char key);
	bool getKeyUp(int key);
	bool getKeyJustDown(unsigned char key);
	bool getKeyJustDown(int key);
	bool getKeyReleased(unsigned char key);
	bool getKeyReleased(int key);
private:
	bool currentKeyAction[349] = {false};
	bool LastKeyAction[349] = {false};
	GLFWwindow* wnd;
};