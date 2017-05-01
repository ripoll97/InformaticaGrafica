#pragma once
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <vector>
#include "shader.hpp"
#include <GL\glew.h>
#include <gtc\matrix_transform.hpp>
#include <glm.hpp>
#include <include\assimp\types.h>

using namespace glm;
using namespace std;

struct Vertex {
	vec3 Position;
	vec3 Normal;
	vec3 TexCoords;
};

struct Texture {
	GLuint id;
	string type;
};

class Mesh {
public:
	vector<Vertex> vertices;
	vector<GLuint> indices;
	vector<Texture> textures;

	Mesh(vector<Vertex> vertices, vector<GLuint> indices, vector<Texture> textures);
	void Draw(Shader MeshShader, GLint DrawMode);
private:
	GLuint VAO, VBO, EBO;
	void setupMesh();
};
