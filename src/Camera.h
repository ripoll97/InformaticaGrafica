#pragma once
#include <glm.hpp>
#include <gtc\matrix_transform.hpp>
#include <gtc\type_ptr.hpp>

#include <GL\glew.h>
//GLFW
#include <GLFW\glfw3.h>
#include <iostream>
#include "Shader.h"
#include "src\SOIL.h"

#include <time.h>

using namespace glm;
using namespace std;

class Camera {
public:
	Camera(vec3 position, vec3 direction, GLfloat sensibility2, GLfloat fov);
	void DoMovement(GLFWwindow* window);
	void MouseMove(GLFWwindow* window, double xpos, double ypos);
	void MouseScroll(GLFWwindow* window, double xScroll, double yScroll);
	mat4 LookAt();
	GLfloat GetFOV();
	vec3 cameraPos = vec3(0.0f, 0.0f, 3.0f);

private:
	vec3 cameraFront = vec3(0.0f, 0.0f, -1.0f);
	vec3 cameraUp = vec3(0.0f, 1.0f, 0.0f);
	GLfloat dt;
	GLfloat lastFrame;
	GLfloat lastMx = 400;
	GLfloat lastMy = 300;
	GLfloat sensibility = 0.04;
	GLboolean firstMouse;
	GLfloat PITCH;
	GLfloat YAW;
	GLfloat FOV;
	GLfloat cameraVel;
	GLfloat offsetX;
	GLfloat offsetY;

};