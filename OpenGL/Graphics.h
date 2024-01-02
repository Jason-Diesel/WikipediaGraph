#pragma once
#include <vector>
#include <string>
#include <windows.h>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm.hpp>
#include <map>

#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>
#include "Buffer.h"


class Graphics{
public:
	Graphics();
	virtual ~Graphics();
	bool UpdateWindows();
	void CreateAWindow(uint16_t Width = 640, uint16_t Height = 480, std::string Title = "", bool fullScreen = false);
	void SetActiveWindow(uint8_t ActiveWindow);
	void vSync(bool enable);
	bool isVsynced()const;
	void setDefaultViewPort();
	void enableWireframeMode(bool enable);
	uint32_t GetNrOfWindows();
	GLFWwindow* getCurrentActiveWindow();
	GLFWwindow* getWindowByIndex(int index);
	glm::ivec2 getWindowCurrentWH() const;
	glm::ivec2 getWindowByIndexWH(int index) const;
	//uint32_t getUniformBuffer(std::string bufferName);
private:
	void setUpImGui();
	//void setUpBuffers();
private:
	uint8_t currentActiveWindow;
	std::vector<GLFWwindow*> windows;
	std::vector<glm::ivec2> WindowWH;
	bool vSynced;
};