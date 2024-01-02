#include "Mesh.h"

Mesh::Mesh()
{
}


Mesh::Mesh(
    uint32_t materialIndex, 
    uint32_t nrOfVertecies,
    uint32_t vertexBuffer, 
    uint32_t nrOfIndecies, 
    uint32_t indeciesBuffer,
    uint32_t vertexArray,
    TypeOfMesh meshType
):
    m_materialIndex(materialIndex),
    m_nrOfVertecies(nrOfVertecies),
    m_vertexBuffer(vertexBuffer),
    m_nrOfIndecies(nrOfIndecies),
    m_indeciesBuffer(indeciesBuffer),
    m_vertexarray(vertexArray),
    typeOfMesh(meshType)
{
}

TypeOfMesh Mesh::GetModelType() const
{
    return this->typeOfMesh;
}
