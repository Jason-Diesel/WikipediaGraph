#include "Engine.h"
#include "ErrorHelper.h"

Engine::Engine()
	:m_sceneHandler(new WikiGraphScene()),
	m_gameOver(false)
{
	dt.restartClock();
	
	basicToScene.rm = new ResourceManager();
	basicToScene.gh = &gh;
	basicToScene.mouse = new Mouse(gfx.getCurrentActiveWindow());
	basicToScene.keyboard = new Keyboard(gfx.getCurrentActiveWindow());
	
	basicToScene.camera = new Camera(&this->shaderHandler);
	this->shaderHandler.setResourceManager(basicToScene.rm);
	basicToScene.shadowMap = new ShadowMap(&shaderHandler);
	setUpDefaultShaders();
	basicToScene.gfx = &this->gfx;
	
	this->shaderHandler.setCurrentshader("defShaderProgram");
	basicToScene.shaderHandler = &this->shaderHandler;
	
	basicToScene.imGuiManager = &this->imGuiManager;
	imGuiManager.init();
	
	m_sceneHandler.setBasicDefaultVariables(basicToScene);
	DefToGameObject t = {&this->shaderHandler, basicToScene.rm};
	gh.setDefToGameObject(t);
	basicToScene.camera->init();
	m_sceneHandler.sceneInit();
	
}

Engine::~Engine()
{
	delete basicToScene.camera;
	delete basicToScene.keyboard;
	delete basicToScene.mouse;
	delete basicToScene.rm;
	delete basicToScene.shadowMap;
}

void Engine::Run()
{
	
	//for FPS counter
	float currentTimeToUpdateFPS = 0;
	float TimeToUpdateFPS = 0.3f;
	uint32_t counter = 0;

	//GAME LOOP
	while(!m_gameOver){

		//If no windows exist delete app
		#ifdef TurnOfWithWindow
		    if(gfx.GetNrOfWindows() <= 0)
			{
			    m_gameOver = true;
			    return;
	        }
        #else
		    
        #endif // TurnOfWithWindow

		dt.restartClock();

		//FPS COUNTER////////////////////////
		currentTimeToUpdateFPS += (float)dt.dt();
		counter++;
		if(currentTimeToUpdateFPS >= TimeToUpdateFPS){
			float fps = 1/(currentTimeToUpdateFPS / (float)counter);
			glfwSetWindowTitle(gfx.getWindowByIndex(0), std::to_string((int)fps).c_str());


			currentTimeToUpdateFPS -= TimeToUpdateFPS;
			counter = 0;
		}
		////////////////////////////
			
		if(basicToScene.keyboard->getKeyDown(GLFW_KEY_ESCAPE)){
			m_gameOver = true;
		}

		glClearColor(0.1f,0.1f,0.1f,1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		glClear(GL_DEPTH_BUFFER_BIT);

		//update
		basicToScene.mouse->Update();
		basicToScene.keyboard->update();
		m_sceneHandler.Update((float)dt.dt());
		gh.update((float)dt.dt());

		//render shadows
		basicToScene.shadowMap->renderShadow();
		gfx.setDefaultViewPort();


		//render real object
		shaderHandler.setCurrentshader("defShaderProgram");
		basicToScene.shadowMap->updateLightMatrices();
		m_sceneHandler.Render();
		gh.render();

		//render IMGUI
		imGuiManager.render();

		//Mouse Shit should be in scenes
		if(basicToScene.keyboard->getKeyReleased(GLFW_KEY_TAB)){
			basicToScene.mouse->stickMouse();
		}

		glfwSwapBuffers(gfx.getCurrentActiveWindow());
		glfwPollEvents();
		gfx.UpdateWindows();
	}
}

void Engine::setUpDefaultShaders()
{
	uint32_t shadowVertex = basicToScene.rm->getShader("ShadowMapVertexShader.vert");
	uint32_t shadowPixel = basicToScene.rm->getShader("ShadowMapPixelShader.frag");
	basicToScene.shadowMap->addShaderProgram(basicToScene.rm->createShaderProgram("ShadowMapProgram", shadowVertex, shadowPixel));

	uint32_t tessellationVertex = basicToScene.rm->getShader("Tesselation.vert");
	uint32_t tessellationControl = basicToScene.rm->getShader("TessellationControlShader.tesc");
	uint32_t tessellationEvaluation = basicToScene.rm->getShader("TessellationEvaluationShader.tese");

	basicToScene.rm->createShaderProgram("DefTessellation", tessellationVertex, tessellationControl, tessellationEvaluation, basicToScene.rm->getShader("BasicPixelShader.frag"));
	
}
