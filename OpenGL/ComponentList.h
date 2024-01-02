#pragma once
	/// <summary>
	/// Add all the components that should exist in the game/application should be defined here
	/// If they are not defined here it will probably crash 
	/// </summary>
#include "Transform.h"
#include "Behavior.h"
#include "AnimationComponent.h"

class ComponentList{
public:
	ComponentList();
	void operator =(ComponentList& cl)
	{
		for (auto const& [key, val] : cl.components)
		{
			if(key == "BehaviorList")
			{
				BehaviorList* bl = new BehaviorList();
				addComponent("BehaviorList", bl);
				*bl = *(BehaviorList*)val.first;
				
				continue;
			}
			else
			{
				void* newComponent = malloc(val.second);
				memcpy(newComponent, val.first, val.second);
				components.insert(std::make_pair(key, std::pair<void*, uint32_t>(newComponent, val.second)));
			}

		}
	}
	ComponentList(ComponentList& cl)
	{
		for (auto const& [key, val] : cl.components)
		{
			if(key == "behaviorList")
			{
				continue;
			}
			void* newComponent = malloc(val.second);
			memcpy(newComponent, val.first, val.second);
			components.insert(std::make_pair(key, std::pair<void*, uint32_t>(newComponent, val.second)));
		}
	}

	virtual ~ComponentList()
	{
		for (auto const& [key, val] : components)
		{
			delete val.first;
		}
	}

	template <typename T>
	void addComponent(const std::string name, T* component)
	{
		components.insert(std::pair(name, std::pair(component, sizeof(T))));
	}

	template <typename T>
	T* getComponent(const std::string componentName)
	{
		return ((T*)(components[componentName].first));
	}

	bool hasComponent(const std::string componentName)
	{
		return components.count(componentName) > 0;
	}
private:
	std::map<std::string, std::pair<void*, uint32_t>> components;
};