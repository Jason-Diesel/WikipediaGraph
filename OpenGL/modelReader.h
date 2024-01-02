#pragma once
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include "ResourceManager.h"

class Model;
class Mesh;
class AnimatedModel;

enum VerteciesType{
	animationVertecies,
	normalVertecies
};

struct MaterialSave{
    MaterialFlags materialFlags;
    std::vector<std::string> fileNames;
    std::vector<MaterialFlags> TextureType;
    float Ns;
    glm::fvec3 Ka;
	glm::fvec3 Kd;
	glm::fvec3 Ks;
	glm::fvec3 Ke;
	float Ni;
	float d;
	
	bool tessellate;
	float tessellationLevel;
};

//load Model from fbx, obj and so forth
Mesh loadMeshFromFile(const aiMesh* pMesh, std::vector<Vertex>& vertex, std::vector<uint32_t>& indecies);
Model* loadModelFromFile(const std::string& modelFile, ResourceManager* rm);

Model* loadModelFromEngine(const std::string& modelFile, ResourceManager* rm);

//doesn't work with string or dynamic typenames
template <typename T>
void writeVectorFromFile(std::ofstream& file, std::vector<T> vec){
    uint32_t uw = (uint32_t)vec.size();
    file.write((char*)&uw, sizeof(uint32_t));
    file.write((char*)&vec[0], sizeof(T) * uw);
}

template <typename T>
void readVectorFromFile(std::ifstream& file, std::vector<T>& vec){
    uint32_t uw = (uint32_t)vec.size();
    file.read((char*)&uw, sizeof(uint32_t));
    vec.resize(uw);
    file.read((char*)&vec[0], sizeof(T) * uw);
}

void readStringFromFile(std::ifstream& file, std::string& str);

