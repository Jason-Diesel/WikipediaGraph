#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <fstream>
//kinda fucked up here butt idk
#ifdef _DEBUG
#define ShaderPath "Shaders/"
#else
#define ShaderPath "Shaders/"
#endif

//Just return the data
bool readShader(const std::string& name, std::string &shaderData);

void readShaderError(uint32_t shader, uint32_t type);

bool loadVShader(const std::string& name, uint32_t &vertexShader);

//TESSControlShader
bool loadHShader(const std::string& name, uint32_t &hullShader);

//TESSEvaluationShader
bool loadDShader(const std::string& name, uint32_t &domainShader);

bool loadGShader(const std::string& name, uint32_t &geometryShader);

bool loadPShader(const std::string& name, uint32_t &pixelShader);

uint32_t attachShaders(uint32_t vertexShader, uint32_t pixelShader);

uint32_t attachShaders( uint32_t vertex, uint32_t control, uint32_t evaluation, uint32_t pixel);
