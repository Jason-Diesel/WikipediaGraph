#include "Behavior.h"
#include <iostream>

Behavior::Behavior()
{
    std::cout << "size of this: " << sizeof(this) << std::endl;
    size = sizeof(this);
}

Behavior::~Behavior()
{
}

void Behavior::init()
{
}

void Behavior::update(float dt)
{
}

void Behavior::addVariable(TLVarieble var, std::string variableName)
{
    variables.insert(std::pair(variableName, var));
}

void Behavior::setSize(uint32_t size)
{
    this->size = size;
}

size_t Behavior::getSize() const
{
    return this->size;
}

BehaviorList::BehaviorList()
{
}

BehaviorList::~BehaviorList()
{
    for(int i = 0; i < variables.size(); i++){
        delete variables[i].addr;
    }
    for (auto & x : behaviors)
    {
        delete x.second;
    }
}

void BehaviorList::operator=(BehaviorList& other)
{
    for (auto & x : other.behaviors)
    { 
        //printf("size of behavio %zd", x.second->getSize());
        void* newBehavior = malloc(x.second->getSize());
        memcpy(newBehavior, x.second, x.second->getSize());
        behaviors.insert(std::pair(x.first, (Behavior*)newBehavior));
        ((Behavior*)newBehavior)->init();
    }
}

void BehaviorList::update(float dt)
{
	for (auto & x : behaviors)
    {
        x.second->update(dt);
    }
}

//void BehaviorList::addBehavior(Behavior* newBehavior, std::string behaviorName, std::vector<std::pair<std::string, TLVarieble>>* variables)
//{
//    behaviors.insert(std::pair(behaviorName, newBehavior));
//    if(variables != nullptr){
//        for(int i = 0; i < variables->size(); i++){
//            newBehavior->addVariable(variables->at(i).second, variables->at(i).first);
//        }
//    }
//    newBehavior->init();
//}

void BehaviorList::addVariebleToBehavior(TLVarieble var, const std::string& variableName, const std::string& behaviorName, bool autoDelete)
{
    behaviors.find(behaviorName)->second->addVariable(var, variableName);
    if(autoDelete){
        variables.push_back(var);
    }
}
