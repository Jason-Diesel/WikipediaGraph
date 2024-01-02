#pragma once
#include "Camera.h"
#include "ShadowMap.h"
#include "Keyboard.h"
#include "Mouse.h"
#include "ShaderHandler.h"
#include "ImGuiManager.h"
#include "GameObjectHandler.h"

struct DefaultVariableToScene{
	Camera* camera;
	ResourceManager* rm;
	Mouse* mouse;
	Keyboard* keyboard;
	ShadowMap* shadowMap;
	Graphics* gfx;
	ImGuiManager* imGuiManager;
	ShaderHandler* shaderHandler;
	GameObjectHandler* gh;
};