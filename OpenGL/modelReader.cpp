#include "modelReader.h"
#include "ResourceManager.h"
#include <unordered_map>
#include "../glm/gtc/type_ptr.hpp"
#include <iterator>
#include <algorithm>

static glm::quat AssimpToOpenGL(const aiQuaternion& aVec4)
{
	return glm::quat(aVec4.w, aVec4.x,aVec4.y,aVec4.z);
}

static glm::vec3 AssimpToOpenGL(const aiVector3D aVec3)
{
	return glm::vec3(aVec3.x,aVec3.y,aVec3.z);
}

static glm::vec2 AssimpToOpenGL(const aiVector2D& aVec2)
{
	return glm::vec2(aVec2.x,aVec2.y);
}

static glm::mat4 AssimpToOpenGL(const aiMatrix4x4 aMat4){
    //I do not know if it should be the other way
    return glm::transpose(glm::make_mat4(&aMat4.a1));
}

void addEmptyAnimationForEmptyJoints(buildBone& bone, Animation& animation){

	if(animation.keyFrames.find(bone.name) == animation.keyFrames.end()){
		//if the bone doesn't exist in animation add it
		//DO I need two???
		KeyFrames track;
		track.positions.push_back(glm::vec3(0,0,0));
		track.rotations.push_back(glm::quat(1,0,0,0));
		track.scales.push_back(glm::vec3(1,1,1));

		track.positions.push_back(glm::vec3(0,0,0));
		track.rotations.push_back(glm::quat(1,0,0,0));
		track.scales.push_back(glm::vec3(1,1,1));
		track.positionTimestamps.push_back(0);
		track.rotationTimestamps.push_back(0);
		track.scaleTimestamps.push_back(0);

		track.positionTimestamps.push_back(animation.length);
		track.rotationTimestamps.push_back(animation.length);
		track.scaleTimestamps.push_back(animation.length);
		animation.keyFrames.insert(std::pair<std::string, KeyFrames>(bone.name, track));
	}
	else{
		//if the bone doesn't have a certain animation
		KeyFrames& track = animation.keyFrames.find(bone.name)->second;
		if(track.positions.size() <= 0){
			track.positions.push_back(glm::vec3(0, 0, 0));
			track.positionTimestamps.push_back(0);
			track.positions.push_back(glm::vec3(0, 0, 0));
			track.positionTimestamps.push_back(animation.length);
		}
		if(track.rotations.size() <= 0){
			track.rotations.push_back(glm::quat(1, 0, 0, 0));
			track.rotationTimestamps.push_back(0);
			track.rotations.push_back(glm::quat(1, 0, 0, 0));
			track.rotationTimestamps.push_back(animation.length);
		}
		if(track.scales.size() <= 0){
			track.scales.push_back(glm::vec3(1,1,1));
			track.scaleTimestamps.push_back(0);
			track.scales.push_back(glm::vec3(1,1,1));
			track.scaleTimestamps.push_back(animation.length);
		}
	}
	for(int i = 0; i < bone.childJoints.size(); i++){
		addEmptyAnimationForEmptyJoints(bone.childJoints[i], animation);
	}
}

bool loadAnimation(const aiScene* scene, std::map<std::string, Animation>& animations, buildBone& root){
    for(uint16_t a = 0; a < scene->mNumAnimations; a++){
        aiAnimation* anim = scene->mAnimations[a];
        Animation animation;

        if(anim->mTicksPerSecond != 0.0f){
            animation.tick = (float)anim->mTicksPerSecond;
	    }
	    else{
	    	animation.tick = (float)anim->mTicksPerSecond;
	    }
	    animation.length = (float)(anim->mDuration); 
	    animation.keyFrames = {};

	    for (unsigned int i = 0; i < anim->mNumChannels; i++) {
	    	aiNodeAnim* channel = anim->mChannels[i];
	    	KeyFrames track;
	    	for (unsigned int j = 0; j < channel->mNumPositionKeys; j++) {
	    		track.positionTimestamps.push_back((float)channel->mPositionKeys[j].mTime);
	    		track.positions.push_back(AssimpToOpenGL(channel->mPositionKeys[j].mValue));
	    	}
	    	for (unsigned int j = 0; j < channel->mNumRotationKeys; j++) {
	    		track.rotationTimestamps.push_back((float)channel->mRotationKeys[j].mTime);
	    		track.rotations.push_back(AssimpToOpenGL(channel->mRotationKeys[j].mValue));

	    	}
	    	for (unsigned int j = 0; j < channel->mNumScalingKeys; j++) {
	    		track.scaleTimestamps.push_back((float)channel->mScalingKeys[j].mTime);
	    		track.scales.push_back(AssimpToOpenGL(channel->mScalingKeys[j].mValue));
	    
	    	}
	    	animation.keyFrames.insert(std::pair<std::string, KeyFrames>(channel->mNodeName.C_Str(), track));
	    }
        addEmptyAnimationForEmptyJoints(root, animation);
        animations.insert(std::pair(anim->mName.C_Str(), animation));
    }
    return true;
}

bool readSkeleton(buildBone& joint, aiNode* node, std::unordered_map<std::string, std::pair<int, glm::mat4>>& offsetMatrices)
{
    if (offsetMatrices.find(node->mName.C_Str()) != offsetMatrices.end()) { // if node is actually a bone
		joint.name = node->mName.C_Str();
        joint.id = offsetMatrices[joint.name].first;
        glm::mat4 off = offsetMatrices[joint.name].second;
		joint.inverseBindPoseMatrix = glm::transpose(off);
		for (uint16_t i = 0; i < node->mNumChildren; i++) {
			buildBone child;
			//child.parent = &joint;
			if(readSkeleton(child, node->mChildren[i], offsetMatrices)){
				joint.childJoints.push_back(child);
			}
		}
		return true;
	}
	else { // find bones in children
		for (uint32_t i = 0; i < node->mNumChildren; i++) {
			if (readSkeleton(joint, node->mChildren[i], offsetMatrices)) {
				return true;
			}
	
		}
	}
	return false;
}

void loadBoneDataToVertecies(std::vector<AnimationVertex>& vertecies, const aiMesh* pMesh, std::unordered_map<std::string, std::pair<int, glm::mat4>>& offsetMatrices)
{
    std::vector<uint16_t> boneCounts;
	boneCounts.resize(vertecies.size());

    for(uint8_t i = 0; i < pMesh->mNumBones; i++){
        aiBone* bone = pMesh->mBones[i];
        
        offsetMatrices[bone->mName.C_Str()] = {i, AssimpToOpenGL(bone->mOffsetMatrix) };

        for(uint32_t w = 0; w < bone->mNumWeights; w++){
            uint32_t id = bone->mWeights[w].mVertexId;
			float weight = bone->mWeights[w].mWeight;

            boneCounts[id]++;
			switch (boneCounts[id]) {
			case 1:
				vertecies[id].m_boneIDs.x = i;
				vertecies[id].m_boneWeights.x = weight;
				break;
			case 2:
				vertecies[id].m_boneIDs.y = i;
				vertecies[id].m_boneWeights.y = weight;
				break;
			case 3:
				vertecies[id].m_boneIDs.z = i;
				vertecies[id].m_boneWeights.z = weight;
				break;
            case 4:
                vertecies[id].m_boneIDs.w = i;
				vertecies[id].m_boneWeights.w = weight;
                break;
			default:
				break;

			}
        }
    }
    //normalize weight in vertecies
    for(int i = 0; i < vertecies.size(); i++){
        float totalWeight = 
            vertecies[i].m_boneWeights.x + 
            vertecies[i].m_boneWeights.y + 
            vertecies[i].m_boneWeights.z +
            vertecies[i].m_boneWeights.w;

        vertecies[i].m_boneWeights.x = vertecies[i].m_boneWeights.x / totalWeight;
        vertecies[i].m_boneWeights.y = vertecies[i].m_boneWeights.y / totalWeight;
        vertecies[i].m_boneWeights.z = vertecies[i].m_boneWeights.z / totalWeight;
        vertecies[i].m_boneWeights.w = vertecies[i].m_boneWeights.w / totalWeight;
    }
}

void loadMaterial(const aiScene* pScene, std::vector<Material>& material, ResourceManager* rm){
    material.resize(pScene->mNumMaterials);

    //Just beacuse I found a bug with a object that doesn't have a material but says it has
    bool actually_has_material = false;

    for(uint32_t i = 0; i < pScene->mNumMaterials; i++){
        const aiMaterial* pMaterial = pScene->mMaterials[i];
        if(pMaterial->GetTextureCount(aiTextureType_DIFFUSE) > 0){
            aiString path;
            if(pMaterial->GetTexture(aiTextureType_DIFFUSE, 0, &path, NULL, NULL, NULL, NULL, NULL) == AI_SUCCESS){
                //load diffuse Texture
                actually_has_material = true;
                material[i].Albedo = rm->getTexture(path.C_Str());
                material[i].materialFlags = (MaterialFlags)(material[i].materialFlags | MaterialFlags::Albedo);
            }
        }
        else{
             material[i].Albedo = rm->getTexture("def");
        }
        if(pMaterial->GetTextureCount(aiTextureType_LIGHTMAP) > 0){
            aiString path;
            if(pMaterial->GetTexture(aiTextureType_LIGHTMAP, 0, &path, NULL, NULL, NULL, NULL, NULL) == AI_SUCCESS){
                //load AO Texture
                actually_has_material = true;
                material[i].AmbientOcclusion = rm->getTexture(path.C_Str());
                material[i].materialFlags = (MaterialFlags)(material[i].materialFlags | MaterialFlags::AmbientOcclusion);
            }
        }
        // unsure if this should be aiTextureType_DISPLACEMENT
        if(pMaterial->GetTextureCount(aiTextureType_DISPLACEMENT) > 0){
            aiString path;
            if(pMaterial->GetTexture(aiTextureType_DISPLACEMENT, 0, &path, NULL, NULL, NULL, NULL, NULL) == AI_SUCCESS){
                //load Heightmap Texture
                actually_has_material = true;
                material[i].HeightMap = rm->getTexture(path.C_Str());
                material[i].tessellate = true;
                material[i].materialFlags = (MaterialFlags)(material[i].materialFlags | MaterialFlags::HeightMap);
            }
        }
        if(pMaterial->GetTextureCount(aiTextureType_NORMALS) > 0){
            aiString path;
            if(pMaterial->GetTexture(aiTextureType_NORMALS, 0, &path, NULL, NULL, NULL, NULL, NULL) == AI_SUCCESS){
                //load normal Texture
                actually_has_material = true;
                material[i].NormalMap = rm->getTexture(path.C_Str());
                material[i].materialFlags = (MaterialFlags)(material[i].materialFlags | MaterialFlags::NormalMap);
            }
        }
        float ns;
        aiColor3D kd,ka,ks,ke;
		float ni, d;
        ni = 0;
		pMaterial->Get(AI_MATKEY_COLOR_AMBIENT, ka);
		pMaterial->Get(AI_MATKEY_COLOR_SPECULAR, ks);
		pMaterial->Get(AI_MATKEY_COLOR_DIFFUSE, kd);
		pMaterial->Get(AI_MATKEY_COLOR_EMISSIVE, ke);
		pMaterial->Get(AI_MATKEY_SHININESS, ns);
		pMaterial->Get(AI_MATKEY_OPACITY, d);
        
        if(actually_has_material)
        {
            material[i].Ka.x = ka.r;
            material[i].Ka.y = ka.g;
            material[i].Ka.z = ka.b;
            
            material[i].Kd.x = kd.r;
            material[i].Kd.y = kd.g;
            material[i].Kd.z = kd.b;
            
            material[i].Ks.x = ks.r;
            material[i].Ks.y = ks.g;
            material[i].Ks.z = ks.b;
            
            material[i].Ke.x = ke.r;
            material[i].Ke.y = ke.g;
            material[i].Ke.z = ke.b;
            
            material[i].d = d;
            material[i].Ni = ni;
            material[i].Ns = ns;
        }
    }
}

Mesh loadMeshFromFile(const aiMesh* pMesh)
{
    std::vector<Vertex> vertex;
    std::vector<uint32_t> indecies;

    vertex.reserve(pMesh->mNumVertices);
    indecies.reserve(pMesh->mNumFaces * 3);

    aiVector3D TexCoord(0,0,0);
    for(uint32_t i = 0; i < pMesh->mNumVertices; i++){
        glm::vec3 pos, norm, tangent, bitangent;
        pos.x = pMesh->mVertices[i].x;
        pos.y = pMesh->mVertices[i].y;
        pos.z = pMesh->mVertices[i].z;

        norm.x = pMesh->mNormals[i].x;
        norm.y = pMesh->mNormals[i].y;
        norm.z = pMesh->mNormals[i].z;

        tangent.x = pMesh->mTangents[i].x;
        tangent.y = pMesh->mTangents[i].y;
        tangent.z = pMesh->mTangents[i].z;

        bitangent.x = pMesh->mBitangents[i].x;
        bitangent.y = pMesh->mBitangents[i].y;
        bitangent.z = pMesh->mBitangents[i].z;

        if(pMesh->HasTextureCoords(0)){
            TexCoord = pMesh->mTextureCoords[0][i];
        }

        vertex.push_back(
            Vertex(
                pos,
                glm::vec2(TexCoord.x, TexCoord.y),
                norm, 
                tangent,
                bitangent
            )
        );
    }

    for(uint32_t i = 0; i < pMesh->mNumFaces; i++){
        indecies.push_back(pMesh->mFaces[i].mIndices[0]);
        indecies.push_back(pMesh->mFaces[i].mIndices[1]);
        indecies.push_back(pMesh->mFaces[i].mIndices[2]);
    }

    uint32_t vertexArray = CreateVertexArray();
    uint32_t vertexBuffer = CreateVertexBuffer(vertex);
    uint32_t indeciesBuffer = CreateIndeciesBuffer(indecies);

    return Mesh(
        0, 
        pMesh->mNumVertices, 
        vertexBuffer, 
        (uint32_t)indecies.size(), 
        indeciesBuffer,
        vertexArray,
        TypeOfMesh::Default
    );;
}

Mesh loadAnimatedMesh(const aiMesh* pMesh, std::unordered_map<std::string, std::pair<int, glm::mat4>>& offsetMatrices)
{
    std::vector<AnimationVertex> vertex;
    std::vector<uint32_t> indecies;

    vertex.reserve(pMesh->mNumVertices);
    indecies.reserve(pMesh->mNumFaces * 3);

    aiVector3D TexCoord(0,0,0);
    glm::vec3 pos, norm, tangent, bitangent;
    for(uint32_t i = 0; i < pMesh->mNumVertices; i++){
        pos.x = pMesh->mVertices[i].x;
        pos.y = pMesh->mVertices[i].y;
        pos.z = pMesh->mVertices[i].z;

        norm.x = pMesh->mNormals[i].x;
        norm.y = pMesh->mNormals[i].y;
        norm.z = pMesh->mNormals[i].z;

        tangent.x = pMesh->mTangents[i].x;
        tangent.y = pMesh->mTangents[i].y;
        tangent.z = pMesh->mTangents[i].z;

        bitangent.x = pMesh->mBitangents[i].x;
        bitangent.y = pMesh->mBitangents[i].y;
        bitangent.z = pMesh->mBitangents[i].z;

        if(pMesh->HasTextureCoords(0)){
            TexCoord = pMesh->mTextureCoords[0][i];
        }

        vertex.push_back(
            AnimationVertex(
                pos,
                glm::vec2(TexCoord.x, TexCoord.y),
                norm, 
                tangent,
                bitangent
            )
        );
    }


    for(uint32_t i = 0; i < pMesh->mNumFaces; i++){
        indecies.push_back(pMesh->mFaces[i].mIndices[0]);
        indecies.push_back(pMesh->mFaces[i].mIndices[1]);
        indecies.push_back(pMesh->mFaces[i].mIndices[2]);
    }

    loadBoneDataToVertecies(vertex, pMesh, offsetMatrices);

    uint32_t vertexArray = CreateVertexArray();
    uint32_t vertexBuffer = CreateAnimationVertexBuffer(vertex);
    uint32_t indeciesBuffer = CreateIndeciesBuffer(indecies);

    Mesh theMesh = Mesh(
        0, 
        pMesh->mNumVertices, 
        vertexBuffer, 
        (uint32_t)indecies.size(), 
        indeciesBuffer,
        vertexArray,
        TypeOfMesh::Animated
    );

    return theMesh;
}

void buildTheSkeleton(std::vector<Bone>& skeleton, buildBone rootBone, int parentID)
{
    Bone newBone;
    newBone.name = rootBone.name;
    newBone.parentIndex = parentID;
    newBone.inverseBindPoseMatrix = rootBone.inverseBindPoseMatrix;
    skeleton[rootBone.id] = newBone;
    for(int i = 0; i < rootBone.childJoints.size(); i++){
        buildTheSkeleton(skeleton, rootBone.childJoints[i], rootBone.id);
    }
}

Model* loadModelFromFile(const std::string& modelFile, ResourceManager* rm)
{
    if(modelFile.substr(modelFile.find_last_of(".") + 1) == "OEM") {
        return loadModelFromEngine(modelFile, rm);
    }
    Assimp::Importer importer;
    const aiScene* pScene = importer.ReadFile(modelFile.c_str(),
        aiProcessPreset_TargetRealtime_Fast | aiProcess_FlipUVs
    );
    if(!pScene){
        return nullptr;
    }
    Model* theReturnModel;
    if(pScene->HasAnimations()){
        theReturnModel = new AnimatedModel();
    }
    else{
        theReturnModel = new Model();
    }
    
    theReturnModel->getMeshes().reserve(pScene->mNumMeshes);

    //come on
    std::vector<Material> materials;
    loadMaterial(pScene, materials, rm);

    std::vector<materialConstBuffer> mcb;
    mcb.resize(materials.size());

    for(int i = 0; i < mcb.size(); i++){
        mcb[i] = materials[i];//special operator
    }

    std::unordered_map<std::string, std::pair<int, glm::mat4>> boneInfo = {};
    for(uint16_t i = 0; i < pScene->mNumMeshes; i++){
        if(pScene->mMeshes[i]->HasBones()){
            theReturnModel->getMeshes().push_back(loadAnimatedMesh(pScene->mMeshes[i], boneInfo));
        }
        else{
            theReturnModel->getMeshes().push_back(loadMeshFromFile(pScene->mMeshes[i]));
        }
        theReturnModel->getMeshes()[theReturnModel->getMeshes().size() - 1].material = materials[pScene->mMeshes[i]->mMaterialIndex];
        theReturnModel->getMeshes()[theReturnModel->getMeshes().size() - 1].mcb = CreateUniformBuffer(mcb[pScene->mMeshes[i]->mMaterialIndex]);
    }
    if(pScene->HasAnimations()){
        buildBone bone;
        //
        readSkeleton(bone, pScene->mRootNode, boneInfo);
        loadAnimation(pScene, ((AnimatedModel*)theReturnModel)->getAnimations(), bone);
        //build sksleton array
        ((AnimatedModel*)theReturnModel)->getSkeleton().resize(boneInfo.size());
        buildTheSkeleton(((AnimatedModel*)theReturnModel)->getSkeleton(), bone, -1);
    }


    return theReturnModel;
}

Model* loadModelFromEngine(const std::string& modelFile, ResourceManager* rm)
{
    uint32_t nrOfMaterials, nrOfTextures, sizeofString, nrOfMeshes, materialIndex;
    VerteciesType vertexType;
    Model* model = new Model();
    std::vector<Material> materials;
    std::vector<materialConstBuffer> mcb;

    std::ifstream file(modelFile, std::ios::in | std::ios::binary);

    if(!file.is_open()){
        std::cout << "couldn't open file" << std::endl;
        return nullptr;
    }

    file.read((char*)&nrOfMaterials, sizeof(uint32_t));//nrOfMaterials
    materials.resize(nrOfMaterials);

    //for every material
    for(int m = 0; m < nrOfMaterials; m++){
        file.read((char*)&materials[m].materialFlags, sizeof(MaterialFlags));

        file.read((char*)&nrOfTextures, sizeof(uint32_t));

        std::vector<MaterialFlags> materialFlags;
        readVectorFromFile(file, materialFlags);
        for(int i = 0; i < nrOfTextures; i++){

            std::string filename;
            readStringFromFile(file, filename);

            switch(materialFlags[i]){
            case MaterialFlags::Albedo:
                materials[m].Albedo = rm->getTexture(filename);
                break;
            case MaterialFlags::AmbientOcclusion:
                materials[m].AmbientOcclusion = rm->getTexture(filename);
                break;
            case MaterialFlags::HeightMap:
                materials[m].HeightMap = rm->getTexture(filename);
                break;
            case MaterialFlags::NormalMap:
                materials[m].NormalMap = rm->getTexture(filename);
                break;
            default:
                std::cout << "error something wong" << std::endl;
                break;
            }
        }
        file.read((char*)&materials[m].Ns, sizeof(float));

        file.read((char*)&materials[m].Ka, sizeof(glm::fvec3));
        file.read((char*)&materials[m].Kd, sizeof(glm::fvec3));
        file.read((char*)&materials[m].Ks, sizeof(glm::fvec3));
        file.read((char*)&materials[m].Ke, sizeof(glm::fvec3));

        file.read((char*)&materials[m].Ni, sizeof(float));
        file.read((char*)&materials[m].d, sizeof(float));

        file.read((char*)&materials[m].tessellate, sizeof(bool));
        file.read((char*)&materials[m].tessellationLevel, sizeof(float));
    }

    mcb.resize(materials.size());
    for(int i = 0; i < mcb.size(); i++){
        mcb[i] = materials[i];//special operator
    }

    file.read((char*)&vertexType, sizeof(vertexType));
    file.read((char*)&nrOfMeshes, sizeof(uint32_t));

    if(vertexType == VerteciesType::normalVertecies){
        for(int i = 0; i < nrOfMeshes; i++){
            uint32_t vertexArray = CreateVertexArray();
            std::vector<Vertex> vertecies;
            std::vector<uint32_t> indecies;
            
            readVectorFromFile(file, vertecies);
            readVectorFromFile(file, indecies);
            uint32_t vertexBuffer = CreateVertexBuffer(vertecies);
            uint32_t indeciesBuffer = CreateIndeciesBuffer(indecies);
            file.read((char*)&materialIndex, sizeof(uint32_t));
            Mesh mesh(
                materialIndex,
                vertecies.size(),
                vertexBuffer,
                indecies.size(),
                indeciesBuffer,
                vertexArray,
                TypeOfMesh::Default
            );
            mesh.material = materials[materialIndex];
            mesh.mcb = CreateUniformBuffer(mcb[materialIndex]);
            model->getMeshes().push_back(mesh);
        }
    }
    else{
        std::cout << "haven't taken care of this yet" << std::endl;
    }

    return model;
}

void readStringFromFile(std::ifstream& file, std::string& str)
{
    uint32_t stringSize;
    file.read((char*)&stringSize, sizeof(uint32_t));
    str.resize(stringSize);
    file.read((char*)&str[0], stringSize);
}

