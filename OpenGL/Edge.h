#pragma once
#include <glm.hpp>
#include "ComponentList.h"
#include "Renderer.h"

class Edge
{
public:
	Edge(Renderer* renderer, glm::vec2 pos1, glm::vec2 pos2);
	void changePosition(glm::vec2 pos1, glm::vec2 pos2);
	void changePosition(glm::vec2 pos1);
	void indirectRender();
	uint32_t model;
private:
	glm::vec2 node1pos;
	glm::vec2 node2pos;
	NodeTransform nodeTransform;
	Renderer* renderer;
};