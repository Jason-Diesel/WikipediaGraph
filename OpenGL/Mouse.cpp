#include "Mouse.h"
#include <iostream>

static double scroller = 0;
static bool scrolled = false;

void scroll_callBack(GLFWwindow* window, double xoffset, double yoffset)
{
    scroller += yoffset;
    scrolled = true;
}

Mouse::Mouse(GLFWwindow* wnd):
mouseDelta(0,0),
scrollDelta(0),
lastScroll(0),
scroll(1)
{
    mouseStuck = true;
    this->wnd = wnd;
    glfwSetCursorPos(this->wnd, (double)(1024/2), (double)(768/2));
    glfwSetScrollCallback(wnd, scroll_callBack);
}

void Mouse::Update()
{
    
    if(scrolled)
    {
        if((scroller - lastScroll) < 0){
            scroll = std::max(0.0, scroll * 0.95);
        }
        else{
            scroll += 0.05f;
        }
        scrolled = false;
    }
    scrollDelta = scroller;
    
    if(mouseStuck){
        double xpos, ypos;
        glfwGetCursorPos(this->wnd, &xpos, &ypos);
        mouseDelta.x = (float)xpos - (1024.f/2.f);
        mouseDelta.y = (float)ypos - (768.f/2.f);
        glfwSetCursorPos(this->wnd, (double)(1024/2), (double)(768/2));
    }
    else{
        mouseDelta = glm::vec2(0,0);
    }
    lastScroll = scrollDelta;
}

double Mouse::getScrollDelta()
{
    return scrollDelta - lastScroll;
}

double Mouse::getScroll()
{
    return this->scroll;
}

glm::vec2 Mouse::getMouseDelta() const
{
    return mouseDelta;
}

glm::vec2 Mouse::getMousePosition() const
{
    double x,y;
    glfwGetCursorPos(this->wnd, &x, &y);
    return glm::vec2(x,y);
}

void Mouse::hideMouseCursor(bool hide)
{
}

void Mouse::stickMouse()
{
    glfwSetCursorPos(this->wnd, (double)(1024/2), (double)(768/2));
    mouseStuck = !mouseStuck;
}

bool Mouse::isClicked(MouseButton button)
{
    return glfwGetMouseButton(this->wnd, button) & GLFW_PRESS;
}

//bool Mouse::isJustClicked(MouseButton button)
//{
//    return glfwGetMouseButton(this->wnd, button) & GLFW_PRESS;
//}

Mouse& Mouse::instance(){
		static Mouse mouse(nullptr);
		return mouse;
	}

