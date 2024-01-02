#pragma once
#define CURL_STATICLIB
#include <iostream>
#include <string>
#include <regex>
#include <curl/curl.h>
#include <map>
#include <queue>
#include "NodeQuadTree.h"

class WebsiteSearcher
{
public:
	WebsiteSearcher(std::string firstURL, Renderer* renderer);
	~WebsiteSearcher();

	void setQuadTree(NodeQuadTree* QT);
	void printWebsites();
	void search();
private:
	NodeQuadTree* QT;
	//Objects
	CURL* curl;
	std::map<std::string, Node*> websites;
	std::map<std::string, bool> DefaultWebsites;
	std::queue<Node*> searchStack;
	Renderer* renderer;

	//Functions
	void searchWebsite(Node* wsd);
	std::string creteWikiLink(std::string link);
	std::string createName(std::string link);//TODO : create this to save memory/ yes it will cost computetial power but idk
	//glm::vec2 getNewNodePosition(Node* oldNode, uint32_t currentMatch, uint32_t nrOfMatches);
	glm::vec2 getNewNodePosition(Node* oldNode, uint64_t nrOfNodes);

	//just for debug
	void WarningCannotAddToQT();
};