#pragma once
#include <glm.hpp>
#include <vector>
#include <string>
#include <unordered_map>
#include <map>
#include "../glm/gtc/quaternion.hpp"

struct KeyFrames{
	std::vector<float> positionTimestamps;
	std::vector<float> rotationTimestamps;
	std::vector<float> scaleTimestamps;

	std::vector<glm::vec3> positions = {};
	std::vector<glm::quat> rotations = {};
	std::vector<glm::vec3> scales = {};
};

class Animation {
public:
	float length = 0;
	float tick = 1.0f;
	std::map<std::string, KeyFrames> keyFrames;
};

struct Bone {
	std::string name;
	int parentIndex = -1;
	int id = -1;
	
	glm::mat4 inverseBindPoseMatrix;//never change this
	glm::mat4 FinalTransformation;	//can change this
};

struct buildBone {
	std::vector<buildBone> childJoints;
	//Bone* parent = nullptr;
	std::string name;
	int id = -1;
	glm::mat4 inverseBindPoseMatrix;
	glm::mat4 boneMatrix;
	
};
