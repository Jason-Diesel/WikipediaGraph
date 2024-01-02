#include "GameObject.h"

GameObject::GameObject(DefToGameObject& def, glm::vec3 Position, glm::vec3 Rotation, glm::vec3 Scale):
	model(nullptr)
{
	shaderHandler = def.shaderHandler;

	shaderProgram = def.rm->getShaderProgram("defShaderProgram");
	compList.addComponent("Transform", new Transform());
}

//does not copy Behaviors
GameObject::GameObject(GameObject* GameObject)
{
	this->shaderHandler = GameObject->shaderHandler;
	this->model = GameObject->model;
	this->shaderProgram = GameObject->shaderProgram;

	//compList.insert(std::pair<std::string, Components*>("Transform", new Transform()));
	this->compList = GameObject->compList;
	//for (auto const& [key, val] : GameObject->compList)
	//{
	//	std::cout << sizeof(*val) << std::endl;
	//	this->compList.insert(std::pair(key, new Components(*val)));
	//}
}

GameObject::~GameObject()
{
}

void GameObject::SetShaderProgram(uint32_t shaderProgram)
{
	this->shaderProgram = shaderProgram;
}

void GameObject::directRender()
{
	shaderHandler->setCurrentshader(shaderProgram);

	shaderHandler->updateUniformBuffer("Transform", getComponent<Transform>("Transform")->toMat4());
	if(model != nullptr){
		if(model->GetModelType() == TypeOfModel::Animated){
			AnimationComponent* animComp = getComponent<AnimationComponent>("AnimationComponent");
			BoneConstantBuffer poses;
			((AnimatedModel*)model)->getPose(
					animComp->time,
					animComp->animationName,
				poses
				);
			shaderHandler->updateUniformBuffer("Skeleton", poses);
		}
		model->DirectRender();
	}
	
}

void GameObject::directRenderShadow()
{
	shaderHandler->updateUniformBuffer("Transform", getComponent<Transform>("Transform")->toMat4());
	if(model != nullptr){
		if(hasAnimation()){
			shaderHandler->setCurrentshader("DefShadowSkeletalAnimation");

			AnimationComponent* animComp = getComponent<AnimationComponent>("AnimationComponent");
			BoneConstantBuffer poses;
			((AnimatedModel*)model)->getPose(
					animComp->time,
					animComp->animationName,
				poses
				);
			shaderHandler->updateUniformBuffer("Skeleton", poses);
		}
		else{
			shaderHandler->setCurrentshader("ShadowMapProgram");
		}
		model->DirectRenderShadow();
	}
}

void GameObject::addModel(Model* model)
{
	this->model = model;
	if(model->GetModelType() == TypeOfModel::Animated)
	{
		AnimationComponent *animComp = new AnimationComponent();
		animComp->animationName = ((AnimatedModel*)model)->getAnimations().begin()->first;
		addComponent("AnimationComponent", animComp);

	}
}

void GameObject::setMaterial(Material mat, int index)
{
	if(index < 0){
		for(int i = 0; i < model->getMeshes().size(); i++){
			model->getMeshes()[i].material = mat;
		}
	}
	else{
		model->getMeshes()[index].material = mat;
	}
}

Material& GameObject::getMaterial(int index)
{
	if (index < 0 || index > model->getMeshes().size() - 1) {
		std::cout << "cannot get that mesh index" << std::endl;
		return model->getMeshes()[0].material;
	}
	return model->getMeshes()[index].material;
}


void GameObject::addBehavior(const std::string behaviorName, Behavior* behavior, std::vector<std::pair<std::string, TLVarieble>>* variables)
{
	if(!compList.hasComponent("BehaviorList")){
		compList.addComponent("BehaviorList", new BehaviorList());
	}
	compList.getComponent<BehaviorList>("BehaviorList")->addBehavior(behavior, behaviorName, variables);
}

void GameObject::update(float dt)
{
	if(compList.hasComponent("BehaviorList")){
		compList.getComponent<BehaviorList>("BehaviorList")->update(dt);
	}
	if(compList.hasComponent("AnimationComponent")){
		compList.getComponent<AnimationComponent>("AnimationComponent")->update(dt);

	}
	
}

bool GameObject::hasAnimation()
{
	return model != nullptr && model->GetModelType() == TypeOfModel::Animated;
}
