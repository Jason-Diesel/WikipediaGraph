#pragma once
#include "ResourceManager.h"
#include "ErrorHelper.h"

class ShaderHandler{
public:
	ShaderHandler();
	virtual ~ShaderHandler();
	void setResourceManager(ResourceManager* rm);

	void setCurrentshader(uint32_t shader);
	void setCurrentshader(const std::string &shader);
	uint32_t getCurrentShader() const;

	void AddBuffer(const std::string& buffername, const Buffer buffer);
	void AddBuffer(const std::string& buffername, const UniformBuffer buffer);
	void AddBuffer(const std::string& buffername, const SSBOBuffer buffer);

	template <typename T>
	void updateBuffers(const std::string& buffer, const T& data){
		if(buffers.find(buffer) != buffers.end()){
			buffers[buffer].UpdateData(data);
		}
	}

	void updateUniformBuffer(const std::string& buffer, const void* data, size_t size){
		if(UBs.find(buffer) != UBs.end()){
			UBs[buffer].UpdateDataBasedOnSize(data, size);
			UBs[buffer].setUniform(currentShaderProgram);
		}
	}
	template <typename T>
	void updateUniformBuffer(const std::string& buffer, const T& data){
		if(UBs.find(buffer) != UBs.end()){
			UBs[buffer].UpdateData(data);
			UBs[buffer].setUniform(currentShaderProgram);
		}
	}
	template <typename T>
	void updateSSBOBuffer(const std::string& buffer, const T& data){
		if(SSBOs.find(buffer) != SSBOs.end()){
			SSBOs[buffer].UpdateData(data);
		}
	}
private:
	void setUpBuffers();
private:
	std::map<std::string, Buffer> buffers;
	std::map<std::string, UniformBuffer> UBs;
	std::map<std::string, SSBOBuffer> SSBOs;

	ResourceManager* rm;
	uint32_t currentShaderProgram;
};