#include "Scene.h"

Scene::Scene()
{
}

Scene::~Scene()
{
}

void Scene::init()
{
}

void Scene::setBasicVariables(DefaultVariableToScene& basic)
{
	this->basic.camera = basic.camera;
	this->basic.keyboard = basic.keyboard;
	this->basic.mouse = basic.mouse;
	this->basic.rm = basic.rm;
	this->basic.shadowMap = basic.shadowMap;
	this->basic.imGuiManager = basic.imGuiManager;
	this->basic.gfx = basic.gfx;
	this->basic.shaderHandler = basic.shaderHandler;
	this->basic.gh = basic.gh;

	this->MainCamera = basic.camera;
	this->rm = basic.rm;
	this->mouse = basic.mouse;
	this->keyboard = basic.keyboard;
	this->gfx = basic.gfx;
	this->imGuiManager = basic.imGuiManager;
	this->shaderHandler = basic.shaderHandler;
	this->gh =  basic.gh;

	defToObj.shaderHandler = basic.shaderHandler;
	defToObj.rm = basic.rm;
}

const int Scene::getNewSceneID()
{
	return newSceneID;
}

void Scene::switchScene(int newSceneID)
{
	this->newSceneID = newSceneID;
}

