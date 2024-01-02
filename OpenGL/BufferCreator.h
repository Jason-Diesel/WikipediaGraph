#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <vector>
#include "ErrorHelper.h"
#include "../glm/glm.hpp"

template <typename T>
uint32_t CreateVertexBuffer(std::vector<T>& vertecies, GLenum type = GL_FLOAT){
	uint32_t buffer = 0;
    GLTest(glGenBuffers(1, &buffer));
    GLTest(glBindBuffer(GL_ARRAY_BUFFER, buffer));
    GLTest(glBufferData(GL_ARRAY_BUFFER, sizeof(T) * vertecies.size(), vertecies.data(), GL_STATIC_DRAW));
    
    GLTest(glEnableVertexAttribArray(0));
    GLTest(glVertexAttribPointer(0, 3, type, GL_FALSE, sizeof(T), 0));
    GLTest(glEnableVertexAttribArray(1));
    GLTest(glVertexAttribPointer(1, 2, type, GL_FALSE, sizeof(T), (void*)offsetof(T, m_texChoords)));
    GLTest(glEnableVertexAttribArray(2));
    GLTest(glVertexAttribPointer(2, 3, type, GL_FALSE, sizeof(T), (void*)offsetof(T, m_normals)));
    GLTest(glEnableVertexAttribArray(3));
    GLTest(glVertexAttribPointer(3, 3, type, GL_FALSE, sizeof(T), (void*)offsetof(T, m_tangent)));
    GLTest(glEnableVertexAttribArray(4));
    GLTest(glVertexAttribPointer(4, 3, type, GL_FALSE, sizeof(T), (void*)offsetof(T, m_bitangent)));

    GLTest(glBindBuffer(GL_ARRAY_BUFFER, 0));

    return buffer;
}

template <typename T>
uint32_t CreateVertexBuffer2D(std::vector<T>& vertecies, GLenum type = GL_FLOAT){
	uint32_t buffer = 0;
    GLTest(glGenBuffers(1, &buffer));
    GLTest(glBindBuffer(GL_ARRAY_BUFFER, buffer));
    GLTest(glBufferData(GL_ARRAY_BUFFER, sizeof(T) * vertecies.size(), vertecies.data(), GL_STATIC_DRAW));
    
    GLTest(glEnableVertexAttribArray(0));
    GLTest(glVertexAttribPointer(0, 2, type, GL_FALSE, sizeof(T), 0));

    GLTest(glBindBuffer(GL_ARRAY_BUFFER, 0));

    return buffer;
}

template <typename T>
uint32_t CreateAnimationVertexBuffer(std::vector<T>& vertecies, GLenum type = GL_FLOAT){
	uint32_t buffer = 0;
    GLTest(glGenBuffers(1, &buffer));
    GLTest(glBindBuffer(GL_ARRAY_BUFFER, buffer));
    GLTest(glBufferData(GL_ARRAY_BUFFER, sizeof(T) * vertecies.size(), vertecies.data(), GL_STATIC_DRAW));
    
    
    GLTest(glEnableVertexAttribArray(0));
    GLTest(glVertexAttribPointer(0, 3, type, GL_FALSE, sizeof(T), 0));
    GLTest(glEnableVertexAttribArray(1));
    GLTest(glVertexAttribPointer(1, 2, type, GL_FALSE, sizeof(T), (void*)offsetof(T, m_texChoords)));
    GLTest(glEnableVertexAttribArray(2));
    GLTest(glVertexAttribPointer(2, 3, type, GL_FALSE, sizeof(T), (void*)offsetof(T, m_normals)));
    GLTest(glEnableVertexAttribArray(3));
    GLTest(glVertexAttribPointer(3, 3, type, GL_FALSE, sizeof(T), (void*)offsetof(T, m_tangent)));
    GLTest(glEnableVertexAttribArray(4));
    GLTest(glVertexAttribPointer(4, 3, type, GL_FALSE, sizeof(T), (void*)offsetof(T, m_bitangent)));
    GLTest(glEnableVertexAttribArray(5));
    GLTest(glVertexAttribPointer(5, 4, type, GL_FALSE, sizeof(T), (void*)offsetof(T, m_boneIDs)));
    GLTest(glEnableVertexAttribArray(6));
    GLTest(glVertexAttribPointer(6, 4, type, GL_FALSE, sizeof(T), (void*)offsetof(T, m_boneWeights)));

    GLTest(glBindBuffer(GL_ARRAY_BUFFER, 0));

    return buffer;
}

uint32_t CreateVertexArray();

uint32_t CreateIndeciesBuffer(std::vector<uint32_t>& vertecies);

template <typename T>
uint32_t CreateInstanceBuffer(std::vector<T>& instances) 
{
    uint32_t buff = 0;
    
    glGenBuffers(1, &buff);
    glBindBuffer(GL_ARRAY_BUFFER, buff);
    glBufferData(GL_ARRAY_BUFFER, instances.size() * sizeof(T), instances.data(), GL_DYNAMIC_DRAW);

    //color
    GLTest(glEnableVertexAttribArray(1));
    GLTest(glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(T), (void*)(0 * sizeof(glm::vec4))));
    //transform
    GLTest(glEnableVertexAttribArray(2));
    GLTest(glVertexAttribPointer(2, 4, GL_FLOAT, GL_FALSE, sizeof(T), (void*)(1 * sizeof(glm::vec4))));
    GLTest(glEnableVertexAttribArray(3));
    GLTest(glVertexAttribPointer(3, 4, GL_FLOAT, GL_FALSE, sizeof(T), (void*)(2 * sizeof(glm::vec4))));
    GLTest(glEnableVertexAttribArray(4));
    GLTest(glVertexAttribPointer(4, 4, GL_FLOAT, GL_FALSE, sizeof(T), (void*)(3 * sizeof(glm::vec4))));
    GLTest(glEnableVertexAttribArray(5));
    GLTest(glVertexAttribPointer(5, 4, GL_FLOAT, GL_FALSE, sizeof(T), (void*)(4 * sizeof(glm::vec4))));
    
    GLTest(glVertexAttribDivisor(1, 1));
    GLTest(glVertexAttribDivisor(2, 1));
    GLTest(glVertexAttribDivisor(3, 1));
    GLTest(glVertexAttribDivisor(4, 1));
    GLTest(glVertexAttribDivisor(5, 1));
    
    GLTest(glBindBuffer(GL_ARRAY_BUFFER, 0));
    GLTest(glBindVertexArray(0));
    
    return buff;
    
    /*
    uint32_t buff = 0;

    glGenBuffers(1, &buff);
    glBindBuffer(GL_ARRAY_BUFFER, buff);
    glBufferData(GL_ARRAY_BUFFER, instances.size() * sizeof(T), instances.data(), GL_DYNAMIC_DRAW);

    std::size_t vec4Size = sizeof(glm::vec4);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, vec4Size, (void*)0);
    glEnableVertexAttribArray(3);
    glVertexAttribPointer(3, 4, GL_FLOAT, GL_FALSE, 4 * vec4Size, (void*)0);
    glEnableVertexAttribArray(4);
    glVertexAttribPointer(4, 4, GL_FLOAT, GL_FALSE, 4 * vec4Size, (void*)(1 * vec4Size));
    glEnableVertexAttribArray(5);
    glVertexAttribPointer(5, 4, GL_FLOAT, GL_FALSE, 4 * vec4Size, (void*)(2 * vec4Size));
    glEnableVertexAttribArray(6);
    glVertexAttribPointer(6, 4, GL_FLOAT, GL_FALSE, 4 * vec4Size, (void*)(3 * vec4Size));

    glVertexAttribDivisor(3, 1);
    glVertexAttribDivisor(4, 1);
    glVertexAttribDivisor(5, 1);
    glVertexAttribDivisor(6, 1);

    GLTest(glBindBuffer(GL_ARRAY_BUFFER, 0));
    GLTest(glBindVertexArray(0));

    return buff;
    */
}

template <typename T>
void UpdateInstanceBuffer(uint32_t buffer, std::vector<T>& instances)
{
    glBindBuffer(GL_ARRAY_BUFFER, buffer);

    GLsizei bufferSize;
    glGetBufferParameteriv(GL_ARRAY_BUFFER, GL_BUFFER_SIZE, &bufferSize);

    if (static_cast<size_t>(bufferSize) < instances.size() * sizeof(T)) {
        glBufferData(GL_ARRAY_BUFFER, instances.size() * sizeof(T), instances.data(), GL_DYNAMIC_DRAW);
    }
    else {
        glBufferSubData(GL_ARRAY_BUFFER, 0, instances.size() * sizeof(T), instances.data());
    }

    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

template <typename T>
uint32_t CreateUniformBuffer(T data){
    uint32_t UB;
    GLTest(glGenBuffers(1, &UB));
    GLTest(glBindBuffer(GL_UNIFORM_BUFFER, UB));
    GLTest(glBufferData(GL_UNIFORM_BUFFER, sizeof(T), NULL, GL_DYNAMIC_DRAW));
    return UB;
}

uint32_t CreateUniformBufferBasedOnSize(uint64_t dataSize);

template <typename T>
void UpdateUniformBuffer(const T data, uint32_t buff){
    GLTest(glBindBuffer(GL_UNIFORM_BUFFER, buff));
    void* ptr = glMapBuffer(GL_UNIFORM_BUFFER, GL_WRITE_ONLY);
    if(ptr){
        memcpy(ptr, &data, sizeof(data));
        GLTest(glUnmapBuffer(GL_UNIFORM_BUFFER));
    }
    glBindBuffer(GL_UNIFORM_BUFFER, 0);
}

void UpdateUniformBufferBasedOnSize(const void* data, size_t size, uint32_t buff);

template <typename T>
uint32_t CreateSSBO(T data, const GLuint index)
{
    uint32_t ssbo;
    glGenBuffers(1, &ssbo);
    glBindBuffer(GL_SHADER_STORAGE_BUFFER, ssbo);
    glBufferData(GL_SHADER_STORAGE_BUFFER, sizeof(data), NULL, GL_DYNAMIC_COPY);
    glBindBufferBase(GL_SHADER_STORAGE_BUFFER, index, ssbo);
    glBindBuffer(GL_SHADER_STORAGE_BUFFER, 0); // unbind
    return ssbo;
}

template <typename T>
void UpdateSSBO(const T &data, const uint32_t buff)
{
    glBindBuffer(GL_SHADER_STORAGE_BUFFER, buff);
    glBufferSubData(GL_SHADER_STORAGE_BUFFER, 0, sizeof(T), data);
}

void setUniform(std::string uniformName, const uint32_t uniformBuffer, GLuint bindingIndex = 0);

void createDepthStencil(uint32_t Width, uint32_t Height, uint32_t &depthBufferFBO, uint32_t &depthBuffer);