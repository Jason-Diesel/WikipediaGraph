#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>

#ifndef Dist
    #define ASSERT(x) if(!(x)) __debugbreak();
    #define GLTest(x) GLClearError();\
       x;\
       ASSERT(GLCheckError(#x, __FILE__, __LINE__))
    
    static void GLClearError(){
    	while(glGetError() != GL_NO_ERROR);
    }
    
    static bool GLCheckError(const char* function, const char* file, int line){
    	while(GLenum error = glGetError())
    	{
    		std::cout << "Error: " << error << ", Function: " << function
    			<< ", File: " << file << ", line: " << line << std::endl;
    		return false;
    	}
    	return true;
    }
#else
   #define GLTest(x) x
   #define ASSERT(x) x
#endif
