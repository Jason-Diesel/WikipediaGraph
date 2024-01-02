#pragma once
#include "ErrorHelper.h"
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm.hpp>
#include <map>
#include <vector>
#include "ShaderHandler.h"
#include "Graph.h"

class Renderer
{
public:
	Renderer(ShaderHandler* shaderHandler);
	void addNode(NodeTransformData& node);
	void addEdge(NodeTransformData& edge);
	void render();
private:

	ShaderHandler* shaderHandler;
	Graph graph;
};