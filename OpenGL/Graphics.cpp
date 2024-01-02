#include "Graphics.h"
#include <iostream>

Graphics::Graphics()
{
	if (!glfwInit()){
		std::cout << "glfwInit() error" << std::endl;
		exit(-1);
	}

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	//glEnable(GL_CULL_FACE);  
	//glCullFace(GL_BACK);  

	CreateAWindow(1920, 1080);
	//CreateAWindow(720, 400);
    currentActiveWindow = 0;

	if(glewInit() != GLEW_OK){
		std::cout << "glewInit() error" << std::endl;
        exit(-1);
    }

	//glEnable(GL_DEPTH_TEST);
	//glEnable(GL_CULL_FACE);
	//glCullFace(GL_FRONT);  
	//glFrontFace(GL_CCW);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	vSynced = true;

	setUpImGui();
}

Graphics::~Graphics()
{
	glfwTerminate();
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();
}

bool Graphics::UpdateWindows()
{
	for(int i = 0; i < windows.size(); i++){
		if(glfwWindowShouldClose(windows[i])){
			windows.erase(windows.begin() + i);
		}
	}
	return windows.size() < 1;
}

void Graphics::CreateAWindow(uint16_t Width, uint16_t Height, std::string Title, bool fullScreen)
{
	////Do more here
	WindowWH.push_back(glm::vec2(Width, Height));
	windows.push_back(glfwCreateWindow(Width, Height, Title.c_str(), glfwGetPrimaryMonitor(), NULL));
	//windows.push_back(glfwCreateWindow(Width, Height, Title.c_str(), NULL, NULL));
	glfwMakeContextCurrent(windows[windows.size() - 1]);
}

void Graphics::SetActiveWindow(uint8_t ActiveWindow)
{
	currentActiveWindow = ActiveWindow;
}

void Graphics::vSync(bool enable)
{
	if(enable){
		glfwSwapInterval(1);
		vSynced = true;
	}
	else{
		glfwSwapInterval(0);
		vSynced = false;
	}
}

bool Graphics::isVsynced() const
{
	return vSynced;
}

void Graphics::setDefaultViewPort()
{
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
	glViewport(0,0, WindowWH[currentActiveWindow].x, WindowWH[currentActiveWindow].y);
}

void Graphics::enableWireframeMode(bool enable)
{
	if(enable){
		glPolygonMode( GL_FRONT_AND_BACK, GL_LINE );
	}
	else{
		glPolygonMode( GL_FRONT_AND_BACK, GL_FILL );
	}
}

uint32_t Graphics::GetNrOfWindows()
{
	return (uint32_t)windows.size();
}

GLFWwindow* Graphics::getCurrentActiveWindow()
{
	return windows[currentActiveWindow];
}

GLFWwindow* Graphics::getWindowByIndex(int index)
{
	return windows[index];
}

glm::ivec2 Graphics::getWindowCurrentWH() const
{
	return WindowWH[currentActiveWindow];
}

glm::ivec2 Graphics::getWindowByIndexWH(int index) const
{
	return WindowWH[index];
}

void Graphics::setUpImGui()
{
	IMGUI_CHECKVERSION();
	ImGui::CreateContext(); 
	ImGuiIO& io = ImGui::GetIO(); (void)io;
	io.DisplaySize = ImVec2((float)getWindowCurrentWH().x, (float)getWindowCurrentWH().y);
	io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;

	ImGui::StyleColorsDark();
	if(!ImGui_ImplGlfw_InitForOpenGL(windows[currentActiveWindow], true)){
		std::cout << "error with glfw" << std::endl;
	}
	if(!ImGui_ImplOpenGL3_Init("#version 330")){
		std::cout << "version" << std::endl;
	}
}