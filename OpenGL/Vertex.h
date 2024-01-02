#pragma once
#include <glm.hpp>

//Vertex with UV
struct Vertex{
	Vertex(){
	}
	Vertex(glm::vec3 pos, glm::vec2 UV, glm::vec3 normals, glm::vec3 tangent, glm::vec3 bitangent):
		m_position(pos), m_texChoords(UV), m_normals(normals), m_tangent(tangent), m_bitangent(bitangent)
	{
	}
	glm::vec3 m_position;
	glm::vec2 m_texChoords;
	glm::vec3 m_normals;
	glm::vec3 m_tangent;
	glm::vec3 m_bitangent;
	
};

struct AnimationVertex
{
	AnimationVertex(glm::vec3 pos, glm::vec2 UV, glm::vec3 normals, glm::vec3 tangent, glm::vec3 bitangent):
		m_position(pos), m_texChoords(UV), m_normals(normals), m_tangent(tangent), m_bitangent(bitangent)
	{
		m_boneIDs = glm::vec4(-1,-1,-1,-1);
		m_boneWeights = glm::vec4(0,0,0,0);
	}
	glm::vec3 m_position;
	glm::vec2 m_texChoords;
	glm::vec3 m_normals;
	glm::vec3 m_tangent;
	glm::vec3 m_bitangent;

	glm::vec4 m_boneIDs;
	glm::vec4 m_boneWeights;
};

struct Vertex2D{
	Vertex2D(glm::vec2 positions)
	{
		m_position = positions;
	}
	glm::vec2 m_position;
};
