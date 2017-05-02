#pragma once
#include <GL\glew.h>
#include<glm.hpp>
#include <gtc\matrix_transform.hpp>
using namespace glm;
#include "Shader.h"

enum FigureType {
	cube = 0,
};

class Object {

public:

	Object(vec3 scale, vec3 rotation, vec3 position, FigureType typef);
	~Object();

	void Start();
	void Draw();
	void Move(vec3 translation);
	void Rotate(vec3 rota);
	void Scale(vec3 scal);
	void Delete();
	mat4 GetModelMatrix();
	vec3 GetPosition();

private:
	GLuint VBO, VAO, EBO;
	vec3 position;
	vec3 scalation;
	vec3 rotation;
};
