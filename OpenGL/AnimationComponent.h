#pragma once
#include "Components.h"

struct AnimationComponent : public Components{
	float time;
	std::string animationName;
	void update(float dt){
		time += dt;
	}
	void setAnimation(const std::string& animationName){
		this->animationName = animationName;
	}
};