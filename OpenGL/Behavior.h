#pragma once
#include "Components.h"
#include <vector>
#include <map>
#include <string>
#include <iostream>

struct TLVarieble
{
	TLVarieble(){
		addr = nullptr;
		size = 0;
	}
	template<typename T>
	TLVarieble(T* variable)
	{
		addr = variable;
		size = sizeof(T);
	}
	void* addr;
	uint32_t size;
};

class Behavior{
public:
	Behavior();
	virtual ~Behavior() = 0; //should be pure virtual but I want it on the stack
	virtual void init();
	virtual void update(float dt);
	void addVariable(TLVarieble var, std::string variableName);
	void setSize(uint32_t size);
	size_t getSize() const;
protected:
	template <typename T>
	T* getVariable(const std::string name){
		return (T*)(variables[name].addr);
	}

	std::map<std::string, TLVarieble> variables;
	uint32_t size;
private:
	
};

class BehaviorList : public Components{
public:
	BehaviorList();
	virtual ~BehaviorList();
	void operator=(BehaviorList &other);
	void update(float dt);
	
	template <typename T>
	void addBehavior(T* newBehavior,  std::string behaviorName, std::vector<std::pair<std::string, TLVarieble>>* variables = nullptr)
	{
		Behavior* nb = dynamic_cast<Behavior*>(newBehavior);
		if(nb == nullptr){
			std::cout << "Warning cannot add behavior " << behaviorName << std::endl;
			return;
		}
		nb->setSize(sizeof(T));
		behaviors.insert(std::pair(behaviorName, newBehavior));
		if(variables != nullptr){
		    for(int i = 0; i < variables->size(); i++){
		        nb->addVariable(variables->at(i).second, variables->at(i).first);
		    }
		}
		nb->init();
	}
	//void addBehavior(Behavior* newBehavior, std::string behaviorName, std::vector<std::pair<std::string, TLVarieble>>* variables = nullptr);
	void addVariebleToBehavior(TLVarieble var, const std::string& variableName, const std::string& behaviorName, bool autoDelete = false);
private:
	std::map<std::string, Behavior*> behaviors;
	std::vector<TLVarieble> variables;
};

