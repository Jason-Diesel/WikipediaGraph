#pragma once

#include "DirectionalLight.h"
#include "SpotLight.h"
#include "PointLight.h"

#include "LightBuffer.h"
#include "GameObject.h"
#include "ShaderHandler.h"
#include "ResourceManager.h"
#include <vector>

class ShadowMap{
public:
	//Holds mutliple ShadowMaps one for each light
	ShadowMap(std::vector<Light*> lights, ShaderHandler* shaderHandler);
	ShadowMap(ShaderHandler* shaderHandler);
	virtual ~ShadowMap();
	void addShaderProgram(uint32_t ShadowShaderProgram);

	//Cleans the shadowMap handler and ready for new Scene
	//Just like delete
	void clean();
	
	void setLights(std::vector<Light*> lights);
	void addLight(Light* light);
	void addGameObject(GameObject* gameObject);
	void renderShadow();
	void updateLightMatrices();
	uint32_t getDepthBuffer(int index);
private:
	std::vector<GameObject*> gameObjectsWithShadow;
	std::vector<Light*> lights;

	std::vector<uint32_t> DepthBufferFBO;
	uint32_t DepthBufferArray;

	ShaderHandler* shaderHandler;
	
	LightBuffer lightBuffer;
	//UniformBuffer lightCB;

	ShadowMapBuffer shadowMapConstantBuffer;
	//UniformBuffer shadowMapCB;

	std::vector<uint32_t> ShadowShaderProgram;
};