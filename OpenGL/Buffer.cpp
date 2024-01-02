#include "Buffer.h"

Buffer::Buffer():
    buffer(0)
{
}

uint32_t& Buffer::Get()
{
    return this->buffer;
}

void Buffer::CreateVertexArray_()
{
    this->buffer = CreateVertexArray();
}

void Buffer::CreateIndeciesBuffer_(std::vector<uint32_t>& vertecies)
{
    this->buffer = CreateIndeciesBuffer(vertecies);
}

UniformBuffer::UniformBuffer()
{
}

void UniformBuffer::setUniform(const uint32_t currentProgram)
{
    GLTest(glBindBufferBase(GL_UNIFORM_BUFFER, bindingIndex, this->buffer));
	GLTest(glUniformBlockBinding(currentProgram, getBlockIndex(currentProgram), bindingIndex));
}

GLint UniformBuffer::getBlockIndex(int program)
{
    if(blockIndex.find(program) == blockIndex.end())
    {
        blockIndex.insert(std::pair(program, glGetUniformBlockIndex(program, this->uniformName.c_str())));
    }
    return blockIndex[program];
}

void SSBOBuffer::setSSBO(const uint32_t currentProgram)
{
    uint32_t block_index = 0;
    block_index = glGetProgramResourceIndex(currentProgram, GL_SHADER_STORAGE_BLOCK, "shader_data");
}
