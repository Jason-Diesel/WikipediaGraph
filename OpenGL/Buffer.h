#pragma once
#include "BufferCreator.h"
#include "glm.hpp"
#include <map>

#define MAXNUMBEROFLIGHTS 6
#define MAXNUMBEROFBONES 60

class Buffer{
public:
	Buffer();
	uint32_t& Get();
	//create different Buffers
	void CreateVertexArray_();
	template <typename T>
	void CreateVertexBuffer_(std::vector<T>& vertecies, GLenum type = GL_FLOAT){
		CreateVertexBuffer(vertecies, type);
	}
	template <typename T>
	void CreateAnimationVertexBuffer_(std::vector<T>& vertecies, GLenum type = GL_FLOAT){
		CreateAnimationVertexBuffer(vertecies, type);
	}
	void CreateIndeciesBuffer_(std::vector<uint32_t>& vertecies);


	template <typename T>
	void UpdateData(const T& data){
		UpdateUniformBuffer(data, this->buffer);
	}
	void UpdateDataBasedOnSize(const void* data, size_t size){
		UpdateUniformBufferBasedOnSize(data, size, this->buffer);
	}
protected:
	uint32_t buffer;
	
};

class UniformBuffer : public Buffer{
public:
	//if current program is bind no need to set the program
	template <typename T>
	UniformBuffer(T data, const std::string& uniformName, uint16_t bindngIndex, int program = -1)
	{
		init(data, uniformName, bindngIndex, program);
	}

	UniformBuffer(uint64_t DataSize, const std::string& uniformName, uint16_t bindngIndex, bool doubleTest)
	{
		this->uniformName = uniformName;
		buffer = CreateUniformBufferBasedOnSize(DataSize);
		this->bindingIndex = bindngIndex;
	}
	
	UniformBuffer();

	template <typename T>
	void init(T data, const std::string& uniformName, uint16_t bindngIndex, int program = -1)
	{
		this->uniformName = uniformName;
		buffer = CreateUniformBuffer(data);
		this->bindingIndex = bindngIndex;
	}
	template <typename T>
	void UpdateData(const T& data){
		UpdateUniformBuffer(data, this->buffer);
	}
	void setUniform(const uint32_t currentProgram);
private:
	std::string uniformName;
	GLint getBlockIndex(int program);
	uint16_t bindingIndex;
	std::map<int, GLint> blockIndex;//first = what shader Program, //second is the block index for that shaderProgram
};

class SSBOBuffer : public Buffer{
public:
	template <typename T>
	SSBOBuffer(const T& data, const uint32_t bindingIndex){
		this->buffer = CreateSSBO(data, bindingIndex);
	}
	template <typename T>
	void UpdateData(const T& data){
		UpdateSSBO(data, this->buffer);
	}
	void setSSBO(const uint32_t currentProgram);
private:
	GLint blockIndex;
};

//0
struct cameraBuffer
{
	glm::mat4 p;
	glm::mat4 v;
	glm::vec4 camPos;
};

//1
//just a glm::mat4()

//2
struct materialBuffer
{
	glm::vec4 Ka;
	glm::vec4 Kd;
	glm::vec4 Ks;
	glm::vec4 Ke;
};

//3
struct ShadowMapBuffer
{
	glm::vec4 lightPos[MAXNUMBEROFLIGHTS];//4:th element is what type of light it is
	glm::vec4 lightColors[MAXNUMBEROFLIGHTS];//4:th element is how hard the shadows should be
	glm::mat4 lightViewProjection[MAXNUMBEROFLIGHTS];
	int nrOfLight;
};

//4
struct BoneConstantBuffer
{
	glm::mat4 poses[MAXNUMBEROFBONES];
};

//5
struct LightBuffer
{
	glm::mat4 projection;
	glm::mat4 view;
};

//6
struct camera2DBuffer
{
	glm::vec4 cameraOffset;//x offset, y offset, z zoom, w padding?
};


struct NodeTransformData
{
	NodeTransformData():
		colors(1), Transform2d(1)
	{}
	glm::vec4 colors;
	glm::mat4 Transform2d;
};

struct NodeTransform{
	glm::vec2 position = glm::vec2(0,0);
	float rotation = 0;
	glm::vec2 scale = glm::vec2(1,1);
	glm::vec3 color = glm::vec3(1,1,1);
	glm::mat4 toMat4()
	{
		glm::mat4 translation(
			1,0,position.x,0,
			0,1,position.y,0,
			0,0,1,0,
			0,0,0,1
			);
		glm::mat4 rotationmat(
			cos(this->rotation), -sin(this->rotation), 0,0,
			sin(this->rotation), cos(this->rotation), 0,0,
			0,0,1,0,
			0,0,0,1
		);
		glm::mat4 scalemat(
			scale.x, 0, 0,0,
			0, scale.y, 0,0,
			0, 0, 1, 0,
			0,0,0,1
		);
		
		return scalemat * (rotationmat * translation);
	}
	NodeTransformData toConstantBuffer(){
		NodeTransformData r;
		r.Transform2d = this->toMat4();
		r.colors = glm::vec4(color.x,color.y,color.z,1);

		return r;
	}
};