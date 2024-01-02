#pragma once
#include "GameObject.h"
#include "DefaultVariableToScene.h"

enum SceneHandlerCalls{
	NOTHING,
	SWITCH_SCENE,
};
enum SceneID{
	S_TestScene = 0,
};


class Scene{
public:
	Scene();
	virtual ~Scene();
	virtual void init();
	virtual SceneHandlerCalls update(float dt) = 0;
	virtual void render() = 0;
public:
	//FROM ENGINE TO SCENE
	void setBasicVariables(DefaultVariableToScene& basic);
	//FROM SCENE TO ENGINE
	const int getNewSceneID();
protected:
	void switchScene(int sceneID);
	DefaultVariableToScene basic;
	DefToGameObject defToObj;

	Camera* MainCamera;
	ResourceManager* rm;
	Mouse* mouse;
	Keyboard* keyboard;
	Graphics* gfx;
	ImGuiManager* imGuiManager;
	ShaderHandler* shaderHandler;
	GameObjectHandler *gh;
private:
	int newSceneID;
};