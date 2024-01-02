#pragma once
#include "Model.h"
#include "Graphics.h"

class AnimatedModel : public Model{
public:
	AnimatedModel();
	~AnimatedModel();
	void DirectRender(GLuint Topology);
	void getPose(float time, const std::string& animationName, BoneConstantBuffer& poses);
	std::vector<Bone>& getSkeleton();
	std::map<std::string, Animation>& getAnimations();
private:
	std::map<std::string, Animation> animations;
	std::vector<Bone> skeleton;

};