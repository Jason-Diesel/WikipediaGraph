#pragma once
#include "Material.h"

enum class TypeOfMesh {
	Default,
	Animated
};

class Mesh{
public:
	Mesh();
	Mesh(uint32_t materialIndex,
		uint32_t nrOfVertecies,
		uint32_t vertexBuffer,
		uint32_t nrOfIndecies,
		uint32_t indeciesBuffer,
		uint32_t vertexArray,
		TypeOfMesh meshType
		);
	TypeOfMesh GetModelType() const;
public:
	TypeOfMesh typeOfMesh;
	Material material;
	uint32_t mcb; //materialConstBuffer does not handle textures

	uint32_t m_materialIndex;

	uint32_t m_nrOfVertecies;
	uint32_t m_vertexBuffer;

	uint32_t m_nrOfIndecies;
	uint32_t m_indeciesBuffer;

	uint32_t m_vertexarray;
};