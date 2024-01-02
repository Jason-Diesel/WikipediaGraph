#include "Node.h"


Node::Node(Renderer* renderer, glm::vec2 position, const std::string& name)
{
	this->name = name;

	this->renderer = renderer;
	this->searched = false;
	this->nodeTransform.position = glm::vec2(position.x/screenSpaceX, position.y/screenSpaceY);
	this->nodeTransform.rotation = 0;
	this->nodeTransform.scale = glm::vec2(100/screenSpaceX, 100/screenSpaceY);
	this->nodeTransform.color = glm::vec3(1, 1, 1);

	NodeTransformData data;
	data.colors = glm::vec4(1, 0, 0, 1);//TODO : maybe another color based category
	data.Transform2d = nodeTransform.toMat4();
	renderer->addNode(data);
}

Node::~Node()
{
}

void Node::createNewConnectionEdge(Node* node)
{
	NodeTransform temp;
	glm::vec2 node1pos = nodeTransform.position;
	glm::vec2 node2pos = node->nodeTransform.position;
	temp.scale.x = glm::length(node1pos - node2pos) / 2;
	temp.scale.y = 0.01;

	temp.color = glm::vec3((float)(rand() % 100) / 100, (float)(rand() % 100) / 100, (float)(rand() % 100) / 100);

	glm::vec2 midPoint = (node1pos - node2pos);
	temp.rotation = atan2f(midPoint.y, midPoint.x);
	midPoint.x /= 2;
	midPoint.y /= 2;
	midPoint += node2pos;
	temp.position = midPoint;
	//create edge for renderer
	NodeTransformData data;
	data.colors = glm::vec4(temp.color, 1);
	data.Transform2d = temp.toMat4();
	this->renderer->addEdge(data);
}

void Node::setNewPosition(glm::vec2 pos)
{
	nodeTransform.position = glm::vec2(pos.x/screenSpaceX, -pos.y/screenSpaceY);
}
