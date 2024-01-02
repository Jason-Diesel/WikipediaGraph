#pragma once
#include "ErrorHelper.h"
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm.hpp>
#include <map>
#include <vector>
#include "ShaderHandler.h"


class Graph
{
public:
	Graph();
	//add node or an edge both are the same
	void addNode(NodeTransformData& node);
	void addEdge(NodeTransformData& edge);
	
	void render();
private:
	const int sizeUpdate = 2000;//change this value later

	uint32_t nrOfNodeInstances;
	uint32_t nrOfEdgeInstances;

	bool changeNodeTransformSize;
	bool changeEdgeTransformSize;
	
	std::vector<NodeTransformData> NodeTransformationData;
	std::vector<NodeTransformData> EdgeTransformationData;
	//
	Buffer indeciesBuffer;
	uint32_t NodeQuadBufferVA;//vertexArray
	uint32_t QuadVB;//vertexBuffer
	uint32_t NodeInstanceVB;//instanceBuffer;

	uint32_t EdgeQuadBufferVA;//vertexArray
	uint32_t EdgeInstanceVB;//instanceBuffer;
};