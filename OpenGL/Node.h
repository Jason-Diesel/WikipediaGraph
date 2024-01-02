#pragma once
#include <glm.hpp>
#include "ComponentList.h"
#include "Renderer.h"

#define screenSpaceX 1920.f
#define screenSpaceY 1080.f

class Node
{
public:
	Node(Renderer* renderer, glm::vec2 position, const std::string& name);
	virtual ~Node();
	void createNewConnectionEdge(Node* node);
	void setNewPosition(glm::vec2 pos);
public:
	//Data
	bool searched;
	std::string name;
	std::vector<Node*> nodeConnections;
public:
	//Rendering
	NodeTransform nodeTransform;
	Renderer* renderer;
};
