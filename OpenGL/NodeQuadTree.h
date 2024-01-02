#pragma once
#include "Node.h"

class NodeQuadTree
{
	//Top left is 0,0
public:
	NodeQuadTree(uint32_t desiredDepth, glm::vec2 size, glm::vec2 LeftTopPosition);
	virtual ~NodeQuadTree();
	bool inseartNode(Node* node);
	std::vector<Node*> getNodesFromQuadTree(const glm::vec2 pos);
private:
	uint32_t depth;
	NodeQuadTree* Branches[4];//(top left)(top right)(bot left)(bot right)
	glm::vec2 position;
	glm::vec2 size;
	std::vector<Node*> nodes;
	void setNode(Node* node, int branchID);
	void createBranch(int branchID);
	std::vector<Node*> checkBranch(int branchID, const glm::vec2& pos);
};