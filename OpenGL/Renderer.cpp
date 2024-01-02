#include "Renderer.h"

Renderer::Renderer(ShaderHandler* shaderHandler):
	graph()
{
	this->shaderHandler = shaderHandler;
}

void Renderer::addNode(NodeTransformData& node)
{
	graph.addNode(node);
}

void Renderer::addEdge(NodeTransformData& edge)
{
	graph.addEdge(edge);
}

void Renderer::render()
{
	shaderHandler->setCurrentshader("Quad");
	this->graph.render();
}
