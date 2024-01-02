#include "GameObjectHandler.h"

GameObjectHandler::GameObjectHandler()
{
}

GameObjectHandler::~GameObjectHandler()
{
    for(int i = 0; i < m_gameObjectVector.size(); i++){
        delete m_gameObjectVector[i];
    }
}

void GameObjectHandler::setDefToGameObject(DefToGameObject& defToGameObject)
{
    this->defToGameObject = defToGameObject;
}

void GameObjectHandler::clean()
{
    for(int i = 0; i < m_gameObjectVector.size(); i++){
        delete m_gameObjectVector[i];
    }
    m_gameObjectMap.clear();
}

GameObject* GameObjectHandler::createGameObject(std::string name, bool rendershadow)
{
    GameObject* T = new GameObject(defToGameObject);
    addGameObject(T, name, rendershadow);
    return T;
}

GameObject* GameObjectHandler::addGameObject(GameObject* gameObject, std::string name, bool renderShadow)
{
    createNameID(name);
    m_gameObjectMap.insert(std::pair(name, gameObject));
    m_gameObjectVector.push_back(gameObject);
    m_gameObjectShouldRenderShadow.push_back(renderShadow);

    return gameObject;
}

GameObject* GameObjectHandler::getGameObject(const std::string name)
{
    if(m_gameObjectMap.count(name) < 1){
        std::cerr << "Error: cannot find object " << name << std::endl;
        return nullptr;
    }
    return m_gameObjectMap[name];
}

GameObject* GameObjectHandler::getGameObject(const int index)
{
    if(m_gameObjectVector.size() <= index){
        std::cerr << "Error: cannot find object at index " << index << std::endl;
        return nullptr;
    }
    return m_gameObjectVector[index];
}

GameObject* GameObjectHandler::dubbblicateGameObject(GameObject* gameObject, std::string name, bool rendershadow)
{
    createNameID(name);

    GameObject* t = new GameObject(gameObject);
    m_gameObjectMap.insert(std::pair(name, t));
    m_gameObjectVector.push_back(t);
    m_gameObjectShouldRenderShadow.push_back(rendershadow);
    return t;
}

GameObject* GameObjectHandler::dubbblicateGameObject(const int index, std::string name)
{
    GameObject* T = getGameObject(index);
    if(T == nullptr){
        return nullptr;
    }
    return dubbblicateGameObject(T, name, m_gameObjectShouldRenderShadow[index]);
}

GameObject* GameObjectHandler::dubbblicateGameObject(const std::string& name, std::string newname, bool rendershadow)
{
    GameObject* T = getGameObject(name);
    if(T == nullptr){
        return nullptr;
    }
    return dubbblicateGameObject(T, name, rendershadow);
}

bool GameObjectHandler::removeGameObject(const int index)
{
    if(m_gameObjectVector.size() <= index){
        return false;
    }
    for (auto const& [key, val] : m_gameObjectMap)
    {
        if(val == m_gameObjectVector[index]){
            m_gameObjectMap.erase(key);
            break;
        }
    }
    m_gameObjectVector.erase(m_gameObjectVector.begin() + index);
    m_gameObjectShouldRenderShadow.erase(m_gameObjectShouldRenderShadow.begin() + index);
    return true;
}

bool GameObjectHandler::removeGameObject(const std::string& name)
{
    if(m_gameObjectMap.count(name) < 1){
        return false;
    }
    for(int i = 0; i < m_gameObjectVector.size(); i++)
    {
        if(m_gameObjectVector[i] == m_gameObjectMap[name])
        {
            m_gameObjectVector.erase(m_gameObjectVector.begin() + i);
            m_gameObjectShouldRenderShadow.erase(m_gameObjectShouldRenderShadow.begin() + i);
            break;
        }
    }
    m_gameObjectMap.erase(name);
    return true;
}

bool GameObjectHandler::removeGameObject(const int index, const std::string& name)
{
    if(m_gameObjectMap.count(name) < 1){
        return false;
    }
    if(m_gameObjectVector.size() <= index){
        return false;
    }

    m_gameObjectVector.erase(m_gameObjectVector.begin() + index);
    m_gameObjectShouldRenderShadow.erase(m_gameObjectShouldRenderShadow.begin() + index);
    m_gameObjectMap.erase(name);

    return true;
}

void GameObjectHandler::update(float dt)
{
    //TODO: Multithread this shit/ maybe even do it with the render
    for(int i = 0; i < m_gameObjectVector.size(); i++){
        m_gameObjectVector[i]->update(dt);
    }
}

void GameObjectHandler::render()
{
    //TODO: add renderer here
    //FOR NOW
    for(int i = 0; i < m_gameObjectVector.size(); i++){
        m_gameObjectVector[i]->directRender();
    }
}

void GameObjectHandler::createNameID(std::string &name)
{
    if(name == ""){
        name = "gameObjectWID__" + std::to_string(m_gameObjectVector.size());
    }
}
