#pragma once
#include "Graphics.h"
#include "GameObject.h"
#include "DirectionalLight.h"
#include "SpotLight.h"
#include "PointLight.h"
#include "Node.h"

class ImGuiManager{
public:
	ImGuiManager();
	void init();
	void render();

	void setNodeInfo(Node* node);
private:
	uint32_t Image;
	glm::vec2 textureWidthHeight;

	void renderNodeInfo();
private:
	Node* node;
};