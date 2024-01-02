#include "SceneHandler.h"

SceneHandler::SceneHandler(Scene* StartScene):
	currentScene(StartScene)
{
}

SceneHandler::~SceneHandler()
{
	delete currentScene;
}

void SceneHandler::Update(float dt)
{
	currentScene->update(dt);
}

void SceneHandler::sceneInit()
{
	currentScene->init();
}

void SceneHandler::Render()
{
	currentScene->render();
}

void SceneHandler::setBasicDefaultVariables(DefaultVariableToScene& basic)
{
	this->basic = &basic;
	currentScene->setBasicVariables(basic);
}


void SceneHandler::switchScene(const int sceneID)
{
	//nothing here
	switch (sceneID)
	{
	case S_TestScene:
		
		break;
	default:
		break;
	}
	delete currentScene;
	currentScene = nextScene;
	currentScene->setBasicVariables(*basic);
	currentScene->init();
}

