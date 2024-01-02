#include "WikiGraphScene.h"

WikiGraphScene::WikiGraphScene():
    QT(8, glm::vec2(2000,2000), glm::vec2(-1000, -1000))
{
    srand(time(NULL));
    updateSearch = 0;
    searching = false;
}

WikiGraphScene::~WikiGraphScene()
{
    delete renderer;
    delete webSearcher;
}

void WikiGraphScene::init()
{
    cam2D.cameraOffset = glm::vec4(0,0,1,0);
    renderer = new Renderer(this->shaderHandler);
    rm->createShaderProgram("Quad", rm->getShader("WikiNodeVertexShader.vert"), rm->getShader("WikiNodePixelShader.frag"));
    webSearcher = new WebsiteSearcher("https://en.wikipedia.org/wiki/VTuber", renderer);
    webSearcher->setQuadTree(&QT);
}

SceneHandlerCalls WikiGraphScene::update(float dt)
{

    cam2D.cameraOffset.z = mouse->getScroll();
    shaderHandler->setCurrentshader("Quad");
    shaderHandler->updateUniformBuffer("Camera2D",cam2D);

    if (keyboard->getKeyJustDown('F'))
    {
        searching = true;
    }
    if (keyboard->getKeyJustDown('Q')) 
    {
        searching = false;
    }
    if (searching)
    {
        updateSearch -= dt;
        if (updateSearch < 0) {
            webSearcher->search();
            updateSearch += 0.3f;
        }
    }

    if (keyboard->getKeyJustDown('G'))
    {
        webSearcher->printWebsites();
    }
    if(keyboard->getKeyDown('D'))
    {
        cam2D.cameraOffset.x -= dt;
    }
    else if(keyboard->getKeyDown('A')){
        cam2D.cameraOffset.x += dt;
    }
    if(keyboard->getKeyDown('W')){
        cam2D.cameraOffset.y -= dt;
    }
    else if(keyboard->getKeyDown('S')){
        cam2D.cameraOffset.y += dt;
    }

    if(mouse->isClicked(RIGHT)){
        glm::vec2 posClickPositionToWorldPos(
            (((mouse->getMousePosition().x - screenSpaceX / 2) / screenSpaceX * 2) - cam2D.cameraOffset.x) * (1 / cam2D.cameraOffset.z),
            -(((mouse->getMousePosition().y - screenSpaceY / 2) / screenSpaceY * 2) + cam2D.cameraOffset.y) * (1 / cam2D.cameraOffset.z)
        );
        std::vector<Node*> nodes = QT.getNodesFromQuadTree(posClickPositionToWorldPos);
        std::cout << nodes.size() << std::endl;
        Node* theNode = getNodeCollision(posClickPositionToWorldPos, nodes);
        if (theNode != nullptr)
        {
            imGuiManager->setNodeInfo(theNode);
        }
        else {
            std::cout << "we didn't get anything" << std::endl;
        }
    }

    return SceneHandlerCalls::NOTHING;
}

void WikiGraphScene::render()
{
    renderer->render();
}

Node* WikiGraphScene::getNodeCollision(glm::vec2& position, std::vector<Node*>& nodes)
{   
    for (uint32_t i = 0; i < nodes.size(); i++)
    {
        if (position.x < nodes[i]->nodeTransform.position.x + nodes[i]->nodeTransform.scale.x &&
            position.x > nodes[i]->nodeTransform.position.x - nodes[i]->nodeTransform.scale.x &&
            position.y < nodes[i]->nodeTransform.position.y + nodes[i]->nodeTransform.scale.y &&
            position.y > nodes[i]->nodeTransform.position.y - nodes[i]->nodeTransform.scale.y
            ) 
        {
            return nodes[i];
        }
    }
    return nullptr;
}
