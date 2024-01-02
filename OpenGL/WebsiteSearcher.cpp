#include "WebsiteSearcher.h"

size_t WriteCallback(void* contents, size_t size, size_t nmemb, std::string* output) {
    size_t totalSize = size * nmemb;
    output->append(static_cast<char*>(contents), totalSize);
    return totalSize;
}

WebsiteSearcher::WebsiteSearcher(std::string firstURL, Renderer* renderer)
{
    curl = curl_easy_init();
    if (!curl) {
        std::cerr << "Error initializing libcurl." << std::endl;
        exit(-1);
        return;
    }
    this->renderer = renderer;
    Node* wsd = new Node(renderer, glm::vec2(0,0), firstURL);

    websites.insert(std::pair(firstURL, wsd));
    searchStack.push(wsd);
}

WebsiteSearcher::~WebsiteSearcher()
{
    curl_easy_cleanup(curl);
    for (const auto& [key, val] : websites)
    {
        delete val;
    }
}

void WebsiteSearcher::setQuadTree(NodeQuadTree* QT)
{
    this->QT = QT;
    if (!QT->inseartNode(searchStack.front()))
    {
        WarningCannotAddToQT();
    }
}

void WebsiteSearcher::printWebsites()
{
    uint32_t nrOfWebsitesSearched = 0;
    uint32_t totalNrOfWebsites = 0;
    uint32_t nrOfEdgesCreated = 0;
    for (const auto& [key, val] : websites)
    {
        totalNrOfWebsites++;
        if (val->nodeConnections.size() > 0) {
            nrOfWebsitesSearched++;
            nrOfEdgesCreated += val->nodeConnections.size();
            std::cout << "website name: " << val->name << " nr of connections: " << val->nodeConnections.size() << std::endl;
        }
    }
    std::cout << "Nr of Websites searched : " << nrOfWebsitesSearched << std::endl;
    std::cout << "Nr of nodes created : " << totalNrOfWebsites << std::endl;
    std::cout << "Nr of links created : " << nrOfEdgesCreated << std::endl;
}

void WebsiteSearcher::search()
{
    searchWebsite(searchStack.front());
    searchStack.pop();
}
#define distTest

void WebsiteSearcher::searchWebsite(Node* wsd)
{
    curl_easy_reset(curl);
    curl_easy_setopt(curl, CURLOPT_URL, wsd->name.c_str());

    std::string responseData;
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &responseData);

    CURLcode res = curl_easy_perform(curl);
    if (res != CURLE_OK) {
        std::cerr << "curl_easy_perform() failed: " << curl_easy_strerror(res) << std::endl;
        std::cout << wsd->name << std::endl;
    }
    else {

        std::regex hrefRegex(R"(<a\s+[^>]*href\s*=\s*"/wiki/(?!.*:).*?")");
        auto it = std::sregex_iterator(responseData.begin(), responseData.end(), hrefRegex);
        auto end = std::sregex_iterator();

        static uint64_t currentMatch = 0;
        //TODO : add so we cannot add a node connection 
        for (; it != end; ++it)
        {
            std::smatch match = *it;
            if(match[0] == "<a href=\"/wiki/Main_Page\""){
                continue;
            }
            currentMatch++;
            //if we do not find it add it
            std::string link = creteWikiLink(match[0].str());
            if (websites.find(link) == websites.end())
            {
                glm::vec2 newNodePosition = getNewNodePosition(wsd, currentMatch);
               
                //TODO : add low and high angle
                Node* newwsd = new Node(this->renderer, newNodePosition, link);
                if (!QT->inseartNode(newwsd))
                {
                    WarningCannotAddToQT();
                }
                wsd->createNewConnectionEdge(newwsd);
                websites.insert(std::pair(link, newwsd));
                searchStack.push(newwsd);
                wsd->nodeConnections.push_back(newwsd);
            }
            else//if it exist just add it to the node
            {
                //dubbel check we don't have it again
                bool haveit = false;
                for (int i = 0; i < wsd->nodeConnections.size() && !haveit; i++)
                {
                    if (wsd->nodeConnections[i]->name == link)
                    {
                        haveit = true;
                    }
                }
                if (!haveit)
                {
                    wsd->createNewConnectionEdge(websites[link]);
                    wsd->nodeConnections.push_back(websites[link]);
                }

            }
        }
        wsd->searched = true;
    }
    std::cout << "done" << std::endl;
}

std::string WebsiteSearcher::creteWikiLink(std::string link)
{
    link = link.substr(9);
    link.pop_back();
    link = "https://en.wikipedia.org" + link;
    return link;
}

std::string WebsiteSearcher::createName(std::string link)
{
    return std::string();
}

glm::vec2 WebsiteSearcher::getNewNodePosition(Node* oldNode, uint64_t nrOfNodes)
{
    int squareSize = (sqrt(nrOfNodes) * 1000) + 200;
    // Calculate half-size for easier manipulation
    int halfSize = squareSize / 2.0f;

    // Generate random positions within the square
    float xpos = static_cast<float>(rand()) / RAND_MAX * squareSize - halfSize;
    float ypos = static_cast<float>(rand()) / RAND_MAX * squareSize - halfSize;

    return glm::vec2(xpos, ypos);
}

void WebsiteSearcher::WarningCannotAddToQT()
{
    std::cout << "error" << std::endl;
}

//glm::vec2 WebsiteSearcher::getNewNodePosition(Node* oldNode)
//{
//    //glm::vec2 oldPos = oldNode->nodeTransform.position * glm::vec2(screenSpaceX, screenSpaceY);
    //float angle = oldNode->highAngle - oldNode->lowAngle;
    //
    //float normalizedAngle = angle / 360.0;
    //float normalizedSize = nrOfMatches / 300.f;
    //
    //static float angleWeight = 300;
    //static float sizeWeight = 300;
    //const float lenghtTimes = 200;
    //
    //float lenght = normalizedAngle * angleWeight + normalizedSize * sizeWeight + lenghtTimes;
    //
    //angle = (angle / nrOfMatches) * (currentMatch + 1);
    //angle = angle + oldNode->lowAngle;
    //
    //angle = angle * 3.14159265359 / 180.0;
    //
    //float x = cos(angle) * lenght;
    //float y = sin(angle) * lenght;
    //
    //return oldPos + glm::vec2(x,y);
//     
//}

