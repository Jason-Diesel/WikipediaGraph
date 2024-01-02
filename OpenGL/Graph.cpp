#include "Graph.h"

Graph::Graph()
{
	nrOfNodeInstances = 0;
	nrOfEdgeInstances = 0;

	//create instance buffer
	std::vector<Vertex2D> vertecies;
	vertecies.push_back(Vertex2D(glm::vec2(-1, -1)));
	vertecies.push_back(Vertex2D(glm::vec2(-1, 1)));
	vertecies.push_back(Vertex2D(glm::vec2(1, 1)));
	vertecies.push_back(Vertex2D(glm::vec2(1, -1)));

	NodeQuadBufferVA = CreateVertexArray();
	QuadVB = CreateVertexBuffer2D(vertecies);

	NodeTransformationData.resize(sizeUpdate);
	NodeInstanceVB = CreateInstanceBuffer(this->NodeTransformationData);

	EdgeQuadBufferVA = CreateVertexArray();

	CreateVertexBuffer2D(vertecies);

	EdgeTransformationData.resize(sizeUpdate);
	EdgeInstanceVB = CreateInstanceBuffer(this->EdgeTransformationData);

	std::vector<uint32_t> indecies;
	indecies.push_back(1);
	indecies.push_back(2);
	indecies.push_back(0);
	indecies.push_back(3);
	indeciesBuffer.CreateIndeciesBuffer_(indecies);

}

void Graph::addNode(NodeTransformData& node)
{
	this->NodeTransformationData[nrOfNodeInstances] = node;
	nrOfNodeInstances++;
	changeNodeTransformSize = true;
	if (nrOfNodeInstances >= NodeTransformationData.size() - 1)
	{
		NodeTransformationData.resize(NodeTransformationData.size() + sizeUpdate);
	}
}

void Graph::addEdge(NodeTransformData& edge)
{
	this->EdgeTransformationData[nrOfEdgeInstances] = edge;
	nrOfEdgeInstances++;
	changeEdgeTransformSize = true;
	if (nrOfEdgeInstances >= EdgeTransformationData.size() - 1)
	{
		EdgeTransformationData.resize(EdgeTransformationData.size() + sizeUpdate);
	}
}

void Graph::render()
{
	if(changeNodeTransformSize){
		changeNodeTransformSize = false;
		UpdateInstanceBuffer(NodeInstanceVB, NodeTransformationData);
	}
	if(changeEdgeTransformSize){
		changeEdgeTransformSize = false;
		UpdateInstanceBuffer(EdgeInstanceVB, EdgeTransformationData);
	}
	//render edges
	GLTest(glBindVertexArray(EdgeQuadBufferVA));
	GLTest(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indeciesBuffer.Get()));
	glDrawElementsInstanced(GL_TRIANGLE_STRIP, 4, GL_UNSIGNED_INT, nullptr, nrOfEdgeInstances);

	//render nodes
	GLTest(glBindVertexArray(NodeQuadBufferVA));
	GLTest(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indeciesBuffer.Get()));
	glDrawElementsInstanced(GL_TRIANGLE_STRIP, 4, GL_UNSIGNED_INT, nullptr, nrOfNodeInstances);
}
