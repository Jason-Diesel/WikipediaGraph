#include "ShaderHandler.h"

ShaderHandler::ShaderHandler()
{
}

ShaderHandler::~ShaderHandler()
{
}

void ShaderHandler::setResourceManager(ResourceManager* rm)
{
	this->rm = rm;
	setUpBuffers();
}

void ShaderHandler::setCurrentshader(uint32_t shader)
{
	if(currentShaderProgram != shader){
		currentShaderProgram = shader;
		GLTest(glUseProgram(shader));
	}
}

void ShaderHandler::setCurrentshader(const std::string& shader)
{
	if(currentShaderProgram != rm->getShaderProgram(shader)){
		currentShaderProgram = rm->getShaderProgram(shader);
		GLTest(glUseProgram(currentShaderProgram));
	}
}

uint32_t ShaderHandler::getCurrentShader() const{
	return this->currentShaderProgram;
}

void ShaderHandler::AddBuffer(const std::string& buffername, const Buffer buffer)
{
	buffers.insert(std::pair(buffername, buffer));
}

void ShaderHandler::AddBuffer(const std::string& buffername, const UniformBuffer buffer)
{
	UBs.insert(std::pair(buffername, buffer));
}

void ShaderHandler::AddBuffer(const std::string& buffername, const SSBOBuffer buffer)
{
	SSBOs.insert(std::pair(buffername, buffer));
}

void ShaderHandler::setUpBuffers()
{
	//skeletal transform 0
	//cameraBuffer zeroDataCamera;
	//UniformBuffer UBCamera(zeroDataCamera, "Matrices", 0, rm->getShaderProgram("defShaderProgram"));
	//AddBuffer("SkeletalPose", UBCamera);

	//normal transform 1
	glm::mat4 zeroDataTransform(1);
	UniformBuffer UBTransform(zeroDataTransform, "Transform", 1);
	AddBuffer("Transform", UBTransform);

	//material 2
	UniformBuffer UBMaterial(materialBuffer(), "Material", 2);
	AddBuffer("Material", UBMaterial);

	//3
	UniformBuffer UBShadow(ShadowMapBuffer(), "ShadowData", 3);
	AddBuffer("ShadowMap", UBShadow);

	//4
	UniformBuffer UBBones(BoneConstantBuffer(), "Skeleton", 4);
	AddBuffer("Skeleton", UBBones);

	//5
	UniformBuffer UBLights(LightBuffer(), "LightData", 5);
	AddBuffer("LightData", UBLights);

	//6
	UniformBuffer UB2DCamera(camera2DBuffer(), "Camera2D", 6);
	AddBuffer("Camera2D", UB2DCamera);
}
