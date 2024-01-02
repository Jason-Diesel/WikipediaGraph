#pragma once
#include "GameObject.h"


class GameObjectHandler{
public:
	GameObjectHandler();
	virtual ~GameObjectHandler();
	void setDefToGameObject(DefToGameObject& defToGameObject);
	void clean();

	GameObject* createGameObject(std::string name = "", bool rendershadow = true);
	GameObject* addGameObject(GameObject* gameObject, std::string name = "", bool renderShadow = true);
	//GameObject* addStaticGameObject(GameObject* gameObject, std::string name = "");

	GameObject* getGameObject(const std::string name);
	GameObject* getGameObject(const int index);

	GameObject* dubbblicateGameObject(GameObject* gameObject, std::string name = "", bool rendershadow = true);
	GameObject* dubbblicateGameObject(const int index, std::string name = "");
	GameObject* dubbblicateGameObject(const std::string& name, std::string newname = "", bool rendershadow = true);

	bool removeGameObject(const int index);
	bool removeGameObject(const std::string& name);
	//just much faster
	bool removeGameObject(const int index, const std::string& name);

	void update(float dt);
	void render();
	void renderShadow();

private:
	void createNameID(std::string &name);
	DefToGameObject defToGameObject;
	std::map<std::string, GameObject*> m_gameObjectMap;
	std::vector<GameObject*> m_gameObjectVector;
	std::vector<bool> m_gameObjectShouldRenderShadow;
};