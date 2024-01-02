#pragma once
#include "Scene.h"
#include "WikiGraphScene.h"

class SceneHandler{
public:
	SceneHandler(Scene* StartScene);
	virtual ~SceneHandler();
	void Update(float dt);
	void sceneInit();
	void Render();
	void setBasicDefaultVariables(DefaultVariableToScene& basic);
private:
	void switchScene(const int sceneID);
	DefaultVariableToScene* basic;
	Scene* currentScene;
	Scene* nextScene;
};
