#include "ImGuiManager.h"

ImGuiManager::ImGuiManager()
{
	Image = 0;
	this->node = nullptr;
}

void ImGuiManager::init()
{

}

void ImGuiManager::render()
{
	ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();
	
	renderNodeInfo();

	ImGui::Render();
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

void ImGuiManager::setNodeInfo(Node* node)
{
	this->node = node;
}

void ImGuiManager::renderNodeInfo()
{
	static const char* current_item = NULL;
	static int sItem = -1;
	if (node != nullptr)
	{
		ImGui::Begin(node->name.c_str());
		ImGui::SetWindowSize(ImVec2(500, 200));
		std::string searchedString = node->searched ? "Searched : true" : "Searched : false";
		std::string nodeConnections = "Nr Of node Connections : " + std::to_string((int)node->nodeConnections.size());

		ImGui::Text(searchedString.c_str());
		ImGui::Text(nodeConnections.c_str());
		if (ImGui::BeginCombo("ConnectedNodes", current_item)) {
			for (int i = 0; i < node->nodeConnections.size(); i++)
			{
				//bool is_selcted = (current_item == node[i].name.c_str());
				if (ImGui::Selectable(node->nodeConnections[i]->name.c_str(), false)) {
					//we do not care
				}
			}
			ImGui::EndCombo();
		}
		ImGui::End();
	}
	
}
/*
void ImGuiManager::renderGameObject()
{
	static const char* current_item = NULL;
	static int sItem = -1;
	static bool lightsSelected = false;

	if(ImGui::BeginCombo("GameObjects", current_item)){
		for(int i = 0; i < gameObjects.size(); i++){
			bool is_selcted = (current_item == gameObjects[i].second.c_str());
			if(ImGui::Selectable(gameObjects[i].second.c_str(), is_selcted)){
				lightsSelected = false;
				current_item = gameObjects[i].second.c_str();
				sItem = i;
			}
			if(is_selcted){
				lightsSelected = false;
				sItem = i;
			}
		}
		for(int i = 0; i < lights.size(); i++){
			bool is_selcted = (current_item == lights[i].second.c_str());
			if(ImGui::Selectable(lights[i].second.c_str(), is_selcted)){
				lightsSelected = true;
				current_item = lights[i].second.c_str();
				sItem = i;
			}
			if(is_selcted){
				lightsSelected = true;
				sItem = i;
			}
		}

	ImGui::EndCombo();
	}

	if(sItem > -1){
		if(!lightsSelected){
			Transform* transform = gameObjects[sItem].first->getComponent<Transform>("Transform");
			ImGui::Text("Position");
			ImGui::SliderFloat("x##Position", &transform->position.x, -400, 400);
			ImGui::SliderFloat("y##Position", &transform->position.y, -400, 400);
			ImGui::SliderFloat("z##Position", &transform->position.z, -400, 400);
			ImGui::Text("Rotation");
			ImGui::SliderFloat("x##Rotation", &transform->rotation.x, -10, 10);
			ImGui::SliderFloat("y##Rotation", &transform->rotation.y, -10, 10);
			ImGui::SliderFloat("z##Rotation", &transform->rotation.z, -10, 10);
			ImGui::Text("Scale");
			ImGui::SliderFloat("x##Scale", &transform->scale.x, 0, 100);
			ImGui::SliderFloat("y##Scale", &transform->scale.y, 0, 100);
			ImGui::SliderFloat("z##Scale", &transform->scale.z, 0, 100);
		}
		else{
			Light* l = lights[sItem].first;
			ImGui::Text("Position");
			ImGui::SliderFloat("x##Position", &l->position.x, -400, 400);
			ImGui::SliderFloat("y##Position", &l->position.y, -400, 400);
			ImGui::SliderFloat("z##Position", &l->position.z, -400, 400);
			DirectionalLight* dl = dynamic_cast<DirectionalLight*>(l);
			SpotLight* sl = dynamic_cast<SpotLight*>(l);
			if(dl){
				ImGui::Text("Rotation");
				ImGui::SliderFloat("x##Rotation", &dl->rotation.x, -10, 10);
				ImGui::SliderFloat("y##Rotation", &dl->rotation.y, -10, 10);
				ImGui::SliderFloat("z##Rotation", &dl->rotation.z, -10, 10);
			}
			else if(sl){
				ImGui::Text("Rotation");
				ImGui::SliderFloat("x##Rotation", &sl->rotation.x, -10, 10);
				ImGui::SliderFloat("y##Rotation", &sl->rotation.y, -10, 10);
				ImGui::SliderFloat("z##Rotation", &sl->rotation.z, -10, 10);
			}
			float* colors[3] = {&l->color.r, &l->color.g, &l->color.b};
			ImGui::ColorEdit3("Color", *colors);
		}
		
	}
}
*/

