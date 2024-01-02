#include "AnimatorModel.h"

std::pair<uint32_t, float> getTimeFraction(const std::vector<float>& times, float& dt) {
	uint32_t segment = 0;
	while (dt > times[segment]){
		segment++;
	}
	float start = times[segment - 1];
	float end = times[segment];
	float frac = (dt - start) / (end - start);
	return {segment, frac};
}

AnimatedModel::AnimatedModel()
{
    this->typeOfModel = TypeOfModel::Animated;
    TransformBuffer = CreateUniformBuffer(Transform().toMat4());
}

AnimatedModel::~AnimatedModel()
{
}

void AnimatedModel::DirectRender(GLuint Topology)
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
        //TODO : change this right here
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

void printMatrix(glm::mat4 m, std::string name){
    std::cout << name <<"-------------------------" << std::endl;
        std::cout << m[0].x << ", " << m[0].y << ", " << m[0].z << ", " << m[0].w << std::endl;
        std::cout << m[1].x << ", " << m[1].y << ", " << m[1].z << ", " << m[1].w << std::endl;
        std::cout << m[2].x << ", " << m[2].y << ", " << m[2].z << ", " << m[2].w << std::endl;
        std::cout << m[3].x << ", " << m[3].y << ", " << m[3].z << ", " << m[3].w << std::endl;
    std::cout << "-------------------------" << std::endl;
}

void AnimatedModel::getPose(float time, const std::string& animationName, BoneConstantBuffer& poses)
{
    std::pair<uint32_t, float> fp;
    Animation currentAnimation = animations[animationName];
    time = time * currentAnimation.tick;
    glm::vec3 vec31, vec32;
    glm::quat vec41, vec42;
    glm::mat4 position, rotation, scale;

    float nTime = fmod(time, currentAnimation.length);
    if(nTime == 0){nTime += 0.00000001f;}

    for(int i = 0; i < skeleton.size(); i++){
        Bone& CurrentBone = skeleton[i];
        KeyFrames keyframe =  currentAnimation.keyFrames[CurrentBone.name];
        //calculate position
        fp = getTimeFraction(keyframe.positionTimestamps, nTime);
        vec31 = keyframe.positions[fp.first - 1];
        vec32 = keyframe.positions[fp.first];
        position = glm::translate(glm::mat4(1), glm::mix(vec31, vec32, fp.second));

        //calculate rotation
        fp = getTimeFraction(keyframe.rotationTimestamps, nTime);
        vec41 = keyframe.rotations[fp.first - 1];
        vec42 = keyframe.rotations[fp.first];
        rotation = glm::mat4_cast(glm::slerp(vec41, vec42, fp.second));

        //calculate scale
        fp = getTimeFraction(keyframe.scaleTimestamps, nTime);
        vec31 = keyframe.scales[fp.first - 1];
        vec32 = keyframe.scales[fp.first];
        scale = glm::scale(glm::mat4(1), glm::mix(vec31, vec32, fp.second));

        glm::mat4 pt(1);
        if(CurrentBone.parentIndex != -1){
            pt = skeleton[CurrentBone.parentIndex].FinalTransformation;
        }
        glm::mat4 str = (scale * rotation);
        glm::mat4 mat = glm::transpose(position * str);

        //std::cout << "id:" << i << std::endl;
        //printMatrix(mat, "mat");

        CurrentBone.FinalTransformation = mat * pt;
        //printMatrix(CurrentBone.FinalTransformation, "newParent");
        //printMatrix( CurrentBone.inverseBindPoseMatrix, "inverse");
        poses.poses[i] = glm::transpose(CurrentBone.inverseBindPoseMatrix * CurrentBone.FinalTransformation);
        //printMatrix(poses.poses[i], "final");
    }
}

std::vector<Bone>& AnimatedModel::getSkeleton()
{
    return skeleton;
}

std::map<std::string, Animation>& AnimatedModel::getAnimations()
{
    return animations;
}
