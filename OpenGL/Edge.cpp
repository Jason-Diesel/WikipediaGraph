#include "Edge.h"

Edge::Edge(Renderer* renderer, glm::vec2 pos1, glm::vec2 pos2)
{
	changePosition(pos1, pos2);
	this->renderer = renderer;
}

void Edge::changePosition(glm::vec2 pos1, glm::vec2 pos2)
{
	this->node1pos = pos1;
	this->node2pos = pos2;
	nodeTransform.scale.x = glm::length(pos1 - pos2)/2;
	nodeTransform.scale.y = 0.01;
	
	nodeTransform.color = glm::vec3(1,0,0);
	

	glm::vec2 midPoint = (pos1 - pos2);
	nodeTransform.rotation = atan2f(midPoint.y, midPoint.x);
	midPoint.x /= 2;
	midPoint.y /= 2;
	midPoint += pos2;
	nodeTransform.position = midPoint;
}

void Edge::changePosition(glm::vec2 pos1)
{
	this->node1pos = pos1;
	nodeTransform.scale.x = glm::length(pos1 - node2pos)/2;
	nodeTransform.scale.y = 0.01;
	
	nodeTransform.color = glm::vec3(1,0,0);
	

	glm::vec2 midPoint = (pos1 - node2pos);
	nodeTransform.rotation = atan2f(midPoint.y, midPoint.x);
	midPoint.x /= 2;
	midPoint.y /= 2;
	midPoint += node2pos;
	nodeTransform.position = midPoint;
}

void Edge::indirectRender()
{
	//renderer->inderectRender(0, nodeTransform);
}
