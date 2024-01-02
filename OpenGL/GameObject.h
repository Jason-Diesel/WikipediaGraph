#pragma once
#include <glm.hpp>
#include "ComponentList.h"
#include "AnimatorModel.h"
#include "ShaderHandler.h"

struct DefToGameObject{
	ShaderHandler* shaderHandler;
	ResourceManager* rm;
};

class GameObject{
public:
	//Gonna need to add model
	GameObject(DefToGameObject& def, glm::vec3 Position = glm::vec3(), glm::vec3 Rotation = glm::vec3(), glm::vec3 Scale = glm::vec3());
	GameObject(GameObject* GameObject);
	virtual ~GameObject();
	void SetShaderProgram(uint32_t shaderProgram);
	void directRender();
	void directRenderShadow();
	void addModel(Model* model);
	void setMaterial(Material mat, int index = -1);
	Material& getMaterial(int index = 0);
	void update(float dt);
	bool hasAnimation();

	template <typename T>
	void addComponent(const std::string& componentName, T* component)
	{
		compList.addComponent(componentName, component);
	}
	void addBehavior(const std::string behaviorName, Behavior* behavior, std::vector<std::pair<std::string, TLVarieble>>* variables = nullptr);
	template <typename T>
	T* getComponent(const std::string componentName){
		return compList.getComponent<T>(componentName);
	}

private:
	Model* model;
	uint32_t shaderProgram;

	ShaderHandler* shaderHandler;

	ComponentList compList;
};
