#include "NodeQuadTree.h"

NodeQuadTree::NodeQuadTree(uint32_t desiredDepth, glm::vec2 size, glm::vec2 LeftTopPosition)
{
    this->position = LeftTopPosition;
    this->size = size;
    depth = desiredDepth;
}

NodeQuadTree::~NodeQuadTree()
{
    for (int i = 0; i < 4; i++)
    {
        if (Branches[i] != nullptr)
        {
            delete Branches[i];
        }
    }
}

bool NodeQuadTree::inseartNode(Node* node)
{
    if (depth == 0) {
        nodes.push_back(node);
        return true;
    }
    if (node->nodeTransform.position.x < position.x ||
        node->nodeTransform.position.x > position.x + size.x ||
        node->nodeTransform.position.y < position.y ||
        node->nodeTransform.position.y > position.y + size.y)
    {
        return false;
    }

    if (node->nodeTransform.position.x < position.x + (size.x/2)) {
        //left
        if (node->nodeTransform.position.y < position.y + (size.y/2)) {
            //top
            setNode(node, 0);
        }
        else {
            //bot
            setNode(node, 2);
        }
    }
    else {
        //right
        if (node->nodeTransform.position.y < position.y + (size.y / 2)) {
            //top
            setNode(node, 1);
        }
        else {
            //bot
            setNode(node, 3);
        }
    }
    return true;
}

std::vector<Node*> NodeQuadTree::getNodesFromQuadTree(glm::vec2 pos)
{
    if(depth == 0)
    {
        return this->nodes;
    }

    if (pos.x < position.x ||
        pos.x > position.x + size.x ||
        pos.y < position.y ||
        pos.y > position.y + size.y)
    {
        return std::vector<Node*>();
    }

    if (pos.x < position.x + (size.x/2)) {
        //left
        if (pos.y < position.y + (size.y/2)) {
            //top
            return checkBranch(0, pos);
        }
        else {
            //bot
            return checkBranch(2, pos);
        }
    }
    else {
        //right
        if (pos.y < position.y + (size.y / 2)) {
            //top
            return checkBranch(1, pos);
        }
        else {
            //bot
            return checkBranch(3, pos);
        }
    }
}

void NodeQuadTree::setNode(Node* node, int branchID)
{
    if (Branches[branchID] == nullptr)
    {
        createBranch(branchID);
    }

    Branches[branchID]->inseartNode(node);
}

void NodeQuadTree::createBranch(int branchID)
{
    glm::vec2 branchSize = glm::vec2(size.x / 2.f, size.y / 2.f);
    glm::vec2 branchPos;
    switch (branchID)
    {
    case 0:
        branchPos = position;
        break;
    case 1:
        branchPos = position + glm::vec2(size.x/2,0);
        break;
    case 2:
        branchPos = position + glm::vec2(0, size.y / 2);
        break;
    case 3:
        branchPos = position + glm::vec2(size.x / 2, size.y / 2);
        break;
    default:
        break;
    }
    Branches[branchID] = new NodeQuadTree(depth - 1, branchSize, branchPos);
}

std::vector<Node*> NodeQuadTree::checkBranch(int branchID, const glm::vec2& pos)
{
    if(Branches[branchID] == nullptr)
    {
        return std::vector<Node*>();
    }

    return Branches[branchID]->getNodesFromQuadTree(pos);
}
