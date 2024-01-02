#include "LoadShaders.h"
#include "ErrorHelper.h"

#include <iostream>
#include <windows.h>

void tester()
{
	std::cout << "test" << std::endl;
}

bool readShader(const std::string& name, std::string& shaderData)
{
	std::ifstream reader;
	reader.open(ShaderPath + name, std::ios::binary | std::ios::ate);

	if (!reader.is_open())
	{
		
		std::string failedPath = ShaderPath + name;
		printf("cannot open vertex file %s\n", failedPath.c_str());
		Sleep(50000);
		return false;
	}

	reader.seekg(0, std::ios::end);
	shaderData.reserve(static_cast<uint32_t>(reader.tellg()));
	reader.seekg(0, std::ios::beg);

	shaderData.assign((std::istreambuf_iterator<char>(reader)), std::istreambuf_iterator<char>());
	reader.close();

	return true;
}

void readShaderError(uint32_t shader, uint32_t type)
{
	int lenght;
    glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &lenght);
    char* message = (char*)alloca(lenght * sizeof(char));
    glGetShaderInfoLog(shader, lenght, &lenght, message);
    
    std::cout << "ERROR: " << (type == GL_VERTEX_SHADER ? "vertex" : "fragment") << message << std::endl;

    glDeleteShader(shader);

}

bool loadVShader(const std::string& name, uint32_t& vertexShader)
{
	std::string shaderData;
	if(!readShader(name, shaderData)){
		return false;
	}
	
	vertexShader = glCreateShader(GL_VERTEX_SHADER);
	const char* src = shaderData.c_str();
	glShaderSource(vertexShader, 1, &src, nullptr);
	glCompileShader(vertexShader);
	int res;
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &res);
    if(res == GL_FALSE){
		readShaderError(vertexShader, GL_VERTEX_SHADER);
		return false;
	}
	return true; 
}

bool loadHShader(const std::string& name, uint32_t& hullShader)
{
	std::string shaderData;
	if(!readShader(name, shaderData)){
		return false;
	}
	
	hullShader = glCreateShader(GL_TESS_CONTROL_SHADER);
	const char* src = shaderData.c_str();
	glShaderSource(hullShader, 1, &src, nullptr);
	glCompileShader(hullShader);
	int res;
    glGetShaderiv(hullShader, GL_COMPILE_STATUS, &res);
    if(res == GL_FALSE){
		readShaderError(hullShader, GL_TESS_CONTROL_SHADER);
		return false;
	}
	return true; 
}

bool loadDShader(const std::string& name, uint32_t& domainShader)
{
	std::string shaderData;
	if(!readShader(name, shaderData)){
		return false;
	}
	domainShader = glCreateShader(GL_TESS_EVALUATION_SHADER);
	const char* src = shaderData.c_str();
	glShaderSource(domainShader, 1, &src, nullptr);
	glCompileShader(domainShader);
	int res;
    glGetShaderiv(domainShader, GL_COMPILE_STATUS, &res);
    if(res == GL_FALSE){
		readShaderError(domainShader, GL_TESS_EVALUATION_SHADER);
		return false;
	}
	return true;
}

bool loadGShader(const std::string& name, uint32_t& geometryShader)
{
	std::string shaderData;
	if(!readShader(name, shaderData)){
		return false;
	}
	geometryShader = glCreateShader(GL_GEOMETRY_SHADER);
	const char* src = shaderData.c_str();
	glShaderSource(geometryShader, 1, &src, nullptr);
	glCompileShader(geometryShader);
	int res;
    glGetShaderiv(geometryShader, GL_COMPILE_STATUS, &res);
    if(res == GL_FALSE){
		readShaderError(geometryShader, GL_GEOMETRY_SHADER);
		return false;
	}
	return true;
}

bool loadPShader(const std::string& name, uint32_t& pixelShader)
{
	std::string shaderData;
	if(!readShader(name, shaderData)){
		return false;
	}
	pixelShader = glCreateShader(GL_FRAGMENT_SHADER);
	const char* src = shaderData.c_str();
	glShaderSource(pixelShader, 1, &src, nullptr);
	glCompileShader(pixelShader);
	int res;
    glGetShaderiv(pixelShader, GL_COMPILE_STATUS, &res);
    if(res == GL_FALSE){
		readShaderError(pixelShader, GL_FRAGMENT_SHADER);
		return false;
	}
	return true;

}

uint32_t attachShaders(uint32_t vertexShader, uint32_t pixelShader)
{
	uint32_t p = glCreateProgram();
	glAttachShader(p, vertexShader);
    glAttachShader(p, pixelShader);
    glLinkProgram(p);
    glValidateProgram(p);

	return p;
}

uint32_t attachShaders(uint32_t vertex, uint32_t control, uint32_t evaluation, uint32_t pixel)
{
	uint32_t p = glCreateProgram();
	GLTest(glAttachShader(p, vertex));
	GLTest(glAttachShader(p, pixel));
	GLTest(glAttachShader(p, control));
	GLTest(glAttachShader(p, evaluation));
    GLTest(glLinkProgram(p));
    GLTest(glValidateProgram(p));

	//should probably not do this here later
    //glDeleteShader(vertexShader);
    //glDeleteShader(pixelShader);

	return p;
}
