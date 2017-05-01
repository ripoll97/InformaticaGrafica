#pragma once

#define GLEW_STATIC
#include <GL\glew.h>

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>


class Shader
{
public:

	GLuint Program;
	Shader(const GLchar* vertexPath, const GLchar* fragmentPath);
	void Shader::USE();
	~Shader();
};

