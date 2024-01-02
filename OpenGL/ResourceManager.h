#pragma once
#include "ImageReader.h"
#include "Buffer.h"
#include "LoadShaders.h"
#include "Vertex.h"
#include "Animation.h"
#include "Material.h"
#include "AnimatorModel.h"
#include <map>
#include <string>
#include <iostream>

class ResourceManager{
public:
	ResourceManager();
	virtual ~ResourceManager();
	Model* getModel(const std::string& FileName);

	uint32_t getShader(const std::string& ShaderFile);
	uint32_t getShaderProgram(const std::string& ShaderProgram);
	uint32_t getTexture(const std::string& FileName);

	//create more here later if we need hull, displacement and more
	uint32_t createShaderProgram(const std::string& ShaderProgramName, uint32_t vertex, uint32_t pixel);
	uint32_t createShaderProgram(const std::string& ShaderProgramName, uint32_t vertex, uint32_t control, uint32_t evaluation, uint32_t pixel);

private:
	std::map<std::string, Model*> Models; 
	std::map<std::string, uint32_t> Shaders; 
	std::map<std::string, uint32_t> ShaderProgram; 
	std::map<std::string, uint32_t> Textures;
	void loadDef();
};
