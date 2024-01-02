#pragma once
#include "Keyboard.h"

enum MouseButton{
		LEFT = GLFW_MOUSE_BUTTON_LEFT,
		MIDDLE = GLFW_MOUSE_BUTTON_MIDDLE,
		RIGHT = GLFW_MOUSE_BUTTON_RIGHT
	};

class Mouse{
public:
	
	Mouse(GLFWwindow* wnd);
	void Update();
	double getScrollDelta();
	double getScroll();
	glm::vec2 getMouseDelta() const;
	glm::vec2 getMousePosition() const;
	void hideMouseCursor(bool hide);
	void stickMouse();
	bool isClicked(MouseButton button);
	//bool isJustClicked(MouseButton button);
private:
	static Mouse& instance();
	GLFWwindow* wnd;
	glm::vec2 mouseDelta;
	double scrollDelta;
	double lastScroll;
	double scroll;
	bool mouseStuck;
};