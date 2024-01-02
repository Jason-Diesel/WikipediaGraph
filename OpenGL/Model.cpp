#include "Model.h"

Model::Model()
{
    typeOfModel = TypeOfModel::Default;
    TransformBuffer = CreateUniformBuffer(Transform().toMat4());
}

Model::~Model()
{
}

std::vector<Mesh>& Model::getMeshes()
{
    return meshes;
}

void Model::DirectRender(GLuint Topology)
{

    for(int i = 0; i < meshes.size(); i++){

        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, meshes[i].material.Albedo);
        glActiveTexture(GL_TEXTURE1);
        glBindTexture(GL_TEXTURE_2D, meshes[i].material.AmbientOcclusion);
        glActiveTexture(GL_TEXTURE2);
        glBindTexture(GL_TEXTURE_2D, meshes[i].material.HeightMap);
        glActiveTexture(GL_TEXTURE3);
        glBindTexture(GL_TEXTURE_2D, meshes[i].material.NormalMap);

        materialConstBuffer a;
        a = meshes[i].material;
        UpdateUniformBuffer(a, meshes[i].mcb);
        setUniform("Material", meshes[i].mcb, 2);

		GLTest(glBindVertexArray(meshes[i].m_vertexarray));
		GLTest(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, meshes[i].m_indeciesBuffer));
        if(meshes[i].material.tessellate || (meshes[i].material.materialFlags & MaterialFlags::HeightMap)){
            GLTest(glDrawElements(GL_PATCHES, meshes[i].m_nrOfIndecies, GL_UNSIGNED_INT, nullptr));
        }
        else{
            GLTest(glDrawElements(Topology, meshes[i].m_nrOfIndecies, GL_UNSIGNED_INT, nullptr));
        }
        
	}
}

void Model::DirectRenderShadow()
{
    for (int i = 0; i < meshes.size(); i++) 
    {
		GLTest(glBindVertexArray(meshes[i].m_vertexarray));
		GLTest(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, meshes[i].m_indeciesBuffer));
        GLTest(glDrawElements(GL_TRIANGLES, meshes[i].m_nrOfIndecies, GL_UNSIGNED_INT, nullptr));
	}
}

void Model::setTransform(Transform transform)
{
    UpdateUniformBuffer(glm::transpose(transform.toMat4()), TransformBuffer);
    setUniform("Transform", TransformBuffer, 1);
}

TypeOfModel Model::GetModelType() const
{
    return typeOfModel;
}
