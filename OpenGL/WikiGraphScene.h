#pragma once
#include "Scene.h"
#include "Renderer.h"
#include "WebsiteSearcher.h"

class WikiGraphScene : public Scene{
public:
	WikiGraphScene();
	virtual ~WikiGraphScene();
	void init();
	SceneHandlerCalls update(float dt);
	void render();
private:
	float updateSearch;
	bool searching;

	NodeQuadTree QT;
	camera2DBuffer cam2D;
	Renderer* renderer;
	WebsiteSearcher* webSearcher;
	Node* getNodeCollision(glm::vec2& position, std::vector<Node*>& nodes);
};
