//GLEW
#define GLEW_STATIC
#include <GL\glew.h>
//GLFW
#include <GLFW\glfw3.h>
#include <iostream>
#include "../Shader.h"
#include "src\SOIL.h"

#include <glm.hpp>
#include <gtc\matrix_transform.hpp>
#include <gtc\type_ptr.hpp>

#include <time.h>

using namespace std;
using namespace glm;

const GLint WIDTH = 800, HEIGHT = 600;
bool WIDEFRAME = false;
int Numbuffer = 1;
float fadeValue = 0;
int rotationValue = 0;
int rotationValueY = 0;
int automaticRotation;

vec3 cameraPosition(0.0, 0.0, 3);
vec3 cameraDirectionPoint;
float cameraVelocity = 13.0f;

float pitchVal, yawVal;

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode) {
	//cuando se pulsa una tecla escape cerramos la aplicacion
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
		glfwSetWindowShouldClose(window, GL_TRUE);
		cout << "Meelassa, campo" << endl;
	}
	if (key == GLFW_KEY_W && action == GLFW_PRESS) {
		WIDEFRAME = !WIDEFRAME;
	}
	if (key == GLFW_KEY_1) {
		if (fadeValue < 1)
			fadeValue += 0.1;
	}
	if (key == GLFW_KEY_2) {
		if (fadeValue > 0)
			fadeValue -= 0.1;
	}
	if (key == GLFW_KEY_LEFT) {
		rotationValue = (rotationValue + 3) % 360;
	}
	if (key == GLFW_KEY_RIGHT) {
		rotationValue = (rotationValue - 3) % 360;
	}
	if (key == GLFW_KEY_UP) {
		rotationValueY = (rotationValueY + 3) % 360;
	}
	if (key == GLFW_KEY_DOWN) {
		rotationValueY = (rotationValueY - 3) % 360;
	}
	/*if (key == GLFW_KEY_W) {
		cameraPosition.z -= dt * cameraVelocity;
	}
	if (key == GLFW_KEY_S) {
		cameraPosition.z += dt * cameraVelocity;
	}
	if (key == GLFW_KEY_A) {
		cameraPosition.x -= dt * cameraVelocity;
	}
	if (key == GLFW_KEY_D) {
		cameraPosition.x += dt * cameraVelocity;
	}*/
}

void DoMovement(GLFWwindow* window, float dt) {
	
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
		cameraPosition.z -= dt * cameraVelocity;
		cameraDirectionPoint.z -= dt * cameraVelocity;
	}
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
		cameraPosition.z += dt * cameraVelocity;
		cameraDirectionPoint.z += dt * cameraVelocity;
	}
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
		cameraPosition.x -= dt * cameraVelocity;
		cameraDirectionPoint.x -= dt * cameraVelocity;

	}
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
		cameraPosition.x += dt * cameraVelocity;
		cameraDirectionPoint.x += dt * cameraVelocity;

	}

}

void glfWSetInputMode(GLFWwindow* window, int mode, int value) {

}

void CursorPosition(GLFWwindow* window, double xpos, double ypos) {
	pitchVal = ypos / 1000;
	yawVal = xpos / 1000;
}

void ScrollValues(GLFWwindow* window, double xoffset, double yoffset) {
	cout << yoffset << endl;
}

mat4 createLookAt(vec3 cameraPos, vec3 directionPoint, vec3 upWorldVector) {
	vec3 directionVec, upVec, rightVec;
	vec3 upWorld = upWorldVector;
	
	directionVec = normalize(directionPoint - cameraPos);

	directionVec.x = cos(yawVal * sin(pitchVal));
	directionVec.y = sin(pitchVal);
	directionVec.z = sin(yawVal * cos(pitchVal));
	
		rightVec = normalize(cross(directionVec, upWorld));
	upVec = cross(directionVec, rightVec);
	
	mat4 lookAtMat(
		rightVec.x, upVec.x, -directionVec.x, 0,
		rightVec.y, upVec.y, -directionVec.y, 0,
		rightVec.z, upVec.z, -directionVec.z, 0,
		0, 0, 0, 1
	);

	mat4 positionMat(
		1, 0, 0, 0,
		0, 1, 0, 0,
		0, 0, 1, 0,
		-(cameraPos.x), -(cameraPos.y), -(cameraPos.z), 1
	);

	return lookAtMat * positionMat;
}

/*mat4 createLookAt2() {
	vec3 directionVec, upVec, rightVec;
	vec3 upWorld = { 0,1,0 };
	mat4 lookAtMat;
	directionVec = {0.0, 1.0, 0.0};
	rightVec = { 8.0, 1.0, 2.0 };
	upVec = {4.5, 0.7, 0.0};
	return lookAtMat = {
		rightVec.x, rightVec.y, rightVec.z, 0,
		upVec.x, upVec.y, upVec.z, 0,
		directionVec.x, directionVec.y, directionVec.z, 0,
		0, 0, 0, 1
	};
}*/

int main() {
	//initGLFW

	// Time Variables //
	float oldTime = glfwGetTime();
	float time = glfwGetTime();
	float dt = time - oldTime;
	//TODO
	GLFWwindow* window;
	if (!glfwInit())
		exit(EXIT_FAILURE);
	//set GLFW
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_RESIZABLE, GL_TRUE);

	//create a window
	//TODO
	window = glfwCreateWindow(WIDTH, HEIGHT, "Finestra del projecte", nullptr, nullptr);

	if (!window) {
		cout << "Error al crear la ventana" << endl;
		glfwTerminate();
		exit(EXIT_FAILURE);
	}
	glfwMakeContextCurrent(window);
	//set GLEW and inicializate
	//TODO
	glewExperimental = GL_TRUE;
	if (GLEW_OK != glewInit()) {
		cout << "Error al iniciar glew" << endl;
		glfwTerminate();
		return NULL;
	}
	//set function when callback
	//TODO
	//glfwSetKeyCallback(window, DoMovement);
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);
	glfwSetCursorPosCallback(window, CursorPosition);
	glfwSetScrollCallback(window, ScrollValues);
	//set windows and viewport
	//TODO
	int screenWithd, screenHeight;
	glfwGetFramebufferSize(window, &screenWithd, &screenHeight);
	//fondo
	glClear(GL_COLOR_BUFFER_BIT);
	glClearColor(0.6, 0.0, 0.0, 1.0);
	//TODO



	//cargamos los shader
	//Shader shdr("./src/textureVertexShader.vertexshader", "./src/TextureFragment.fragmentshader");
	Shader shdr("./src/CubeVertexShader.vertexshader", "./src/CubeFragmentShader.fragmentshader");

	// Definir el buffer de vertices

	GLfloat VertexBufferObject[] = {
		// Positions          // Colors           // Texture Coords
		0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 0.0f, // Top Right
		0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 1.0f, // Bottom Right
		-0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 1.0f, // Bottom Left
		-0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 0.0f  // Top Left 
	};

	GLfloat VertexBufferCube[] = {
		-0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
		0.5f , -0.5f, -0.5f,  1.0f, 0.0f,
		0.5f ,  0.5f, -0.5f,  1.0f, 1.0f,
		0.5f ,  0.5f, -0.5f,  1.0f, 1.0f,
		-0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, 0.0f,

		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
		0.5f , -0.5f,  0.5f,  1.0f, 0.0f,
		0.5f ,  0.5f,  0.5f,  1.0f, 1.0f,
		0.5f ,  0.5f,  0.5f,  1.0f, 1.0f,
		-0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,

		-0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
		-0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
		-0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

		0.5f ,  0.5f,  0.5f,  1.0f, 0.0f,
		0.5f ,  0.5f, -0.5f,  1.0f, 1.0f,
		0.5f , -0.5f, -0.5f,  0.0f, 1.0f,
		0.5f , -0.5f, -0.5f,  0.0f, 1.0f,
		0.5f , -0.5f,  0.5f,  0.0f, 0.0f,
		0.5f ,  0.5f,  0.5f,  1.0f, 0.0f,

		-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
		0.5f , -0.5f, -0.5f,  1.0f, 1.0f,
		0.5f , -0.5f,  0.5f,  1.0f, 0.0f,
		0.5f , -0.5f,  0.5f,  1.0f, 0.0f,
		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,

		-0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
		0.5f ,  0.5f, -0.5f,  1.0f, 1.0f,
		0.5f ,  0.5f,  0.5f,  1.0f, 0.0f,
		0.5f ,  0.5f,  0.5f,  1.0f, 0.0f,
		-0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
		-0.5f,  0.5f, -0.5f,  0.0f, 1.0f
	};
	// Definir el EBO

	GLuint IndexBufferObject[]{
		0, 1, 3,
		3, 1, 2
	};

	vec3 CubesPositionBuffer[] = {
		vec3(0.0f ,  0.0f,  0.0f),
		vec3(2.0f ,  3.0f,  0.5f),
		vec3(-1.5f, -2.2f,  0.5f),
		vec3(-3.8f, -2.0f, -1.3f),
		vec3(2.4f , -0.4f, -3.5f),
		vec3(-1.7f,  3.0f, -7.5f),
		vec3(1.3f , -2.0f, -2.5f),
		vec3(1.5f ,  2.0f, -2.5f),
		vec3(1.5f ,  0.2f, -1.5f),
		vec3(-1.3f,  1.0f, -1.5f)
	};

	// Crear los VBO, VAO y EBO
	GLuint VBO, VAO, EBO;

	//reservar memoria para el VAO, VBO y EBO
	glGenVertexArrays(Numbuffer, &VAO);
	glGenBuffers(Numbuffer, &VBO);
	glGenBuffers(Numbuffer, &EBO);

	//Establecer el objeto
	//Declarar el VBO y el EBO



	//Enlazar el buffer con openGL
	glBindVertexArray(VAO);
	
	/*glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(VertexBufferObject), VertexBufferObject, GL_STATIC_DRAW);*/
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(IndexBufferObject), IndexBufferObject, GL_STATIC_DRAW);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(VertexBufferCube), VertexBufferCube, GL_STATIC_DRAW);

	//glBindTexture(GL_TEXTURE_2D, 0);
	//Establecer las propiedades de los vertices

	/*glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GL_FLOAT), (GLvoid*)0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GL_FLOAT), (GLvoid*)(3 * sizeof(GL_FLOAT)));
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(GL_FLOAT), (GLvoid*)(6 * sizeof(GL_FLOAT)));
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glEnableVertexAttribArray(2);*/

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(GL_FLOAT), (GLvoid*)0);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(GL_FLOAT), (GLvoid*)(3 * sizeof(GL_FLOAT)));
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(2);



	glEnable(GL_DEPTH_TEST);

	// Texture 1

	GLuint texture;
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	int width, height;
	unsigned char* image = SOIL_load_image("./src/texture.png", &width, &height, 0, SOIL_LOAD_RGB);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
	SOIL_free_image_data(image);

	// Texture 2

	GLuint texture2;
	glGenTextures(1, &texture2);
	glBindTexture(GL_TEXTURE_2D, texture2);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	image = SOIL_load_image("./src/InBread.png", &width, &height, 0, SOIL_LOAD_RGB);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
	SOIL_free_image_data(image);


	//liberar el buffer
	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindTexture(GL_TEXTURE_2D, 0);
	//glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	//liberar el buffer de vertices

	GLint variableShader = glGetUniformLocation(shdr.Program, "shaderVariable");
	GLfloat variableFade = glGetUniformLocation(shdr.Program, "fade");
	//GLint uniModel = glGetUniformLocation(shdr.Program, "model");
	GLint uniView = glGetUniformLocation(shdr.Program, "view");
	GLint uniProj = glGetUniformLocation(shdr.Program, "proj");

	//bucle de dibujado
	while (!glfwWindowShouldClose(window))
	{

		time = glfwGetTime();
		dt = time - oldTime;

		DoMovement(window, dt);

		mat4 transformationMatrix, escalationMatrix, translationMatrix2, view, proj;
		

		//cout << time  << "		" << oldTime << "		" << dt << endl;

		// Definir las matrices de transformacion
		//escalationMatrix = scale(escalationMatrix, vec3(0.5f, 0.5f, 0.0f));
		/*translationMatrix1 = translate(translationMatrix1, vec3(0.0f, -0.5f, 0.0f));
		
		rotationMatrix = rotate(rotationMatrix, radians(float(rotationValue)), vec3(1.0f, 0.0f, 0.0f));
		rotationMatrix = rotate(rotationMatrix, radians(float(rotationValueY)), vec3(0.0f, 1.0f, 0.0f));
		
		model = translationMatrix1 * rotationMatrix * model;

		translationMatrix2 = translate(translationMatrix2, vec3(0.0, 0.0f, -0.3f));*/
		// No funciona
		//view = translationMatrix2 * view;

		// lookAt sacado de Open.gl
		/*view = lookAt(
			vec3(8.0f, 1.0f, 2.0f),
			vec3(4.5f, 0.7f, 0.0f),
			vec3(0.0f, 1.0f, 0.0f)
		);*/
		view = createLookAt(cameraPosition, cameraDirectionPoint, vec3(0.0, 1, 0.0));
		proj = perspective(radians(60.0f), 800.0f / 600.0f, 0.1f, 100.f);

		// Check if any events have been activiated (key pressed, mouse moved etc.) and call corresponding response functions
		glfwSetKeyCallback(window, key_callback);
		//Establecer el color de fondo
		glClear(GL_COLOR_BUFFER_BIT);
		glClearColor(1.0, 1.0, 0.0, 1.0);

		//establecer el shader
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, texture);
		glUniform1i(glGetUniformLocation(shdr.Program, "Texture1"), 0);
		glActiveTexture(GL_TEXTURE1);

		glBindTexture(GL_TEXTURE_2D, texture2);
		glUniform1i(glGetUniformLocation(shdr.Program, "Texture2"), 1);
		shdr.USE();
		//glUniform1f(variableShader, 0.4 * abs(sin(glfwGetTime())));
		glUniform1f(variableFade, fadeValue);
		//pitar el VAO
		glBindVertexArray(VAO); 
		automaticRotation = glfwGetTime() * 50;
			for (int i = 0; i < 10; i++) {
				mat4 translationMatrix1, rotationMatrix;
				if (i == 0) {
					rotationMatrix = rotate(rotationMatrix, radians(float(rotationValue)), vec3(1.0f, 0.0f, 0.0f));
					rotationMatrix = rotate(rotationMatrix, radians(float(rotationValueY)), vec3(0.0f, 1.0f, 0.0f));

				}

				else {
					rotationMatrix = rotate(rotationMatrix, radians(float(automaticRotation)), vec3(1.0f, 0.0f, 0.0f));
					rotationMatrix = rotate(rotationMatrix, radians(float(automaticRotation * 0.5)), vec3(0.0f, 1.0f, 0.0f));
				}

				translationMatrix1 = translate(translationMatrix1, CubesPositionBuffer[i]);
				mat4 model = translationMatrix1 * rotationMatrix;

				glUniformMatrix4fv(glGetUniformLocation(shdr.Program, "model"), 1, GL_FALSE, value_ptr(model));
				glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
				glDrawArrays(GL_TRIANGLES, 0, 36);
			}
		
		//pintar con lineas
		/*if (WIDEFRAME) {
			glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
			glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
		}
		//pintar con triangulos
		if (!WIDEFRAME) {
			glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
			glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

			glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
			glDrawArrays(GL_TRIANGLES, 0, 36);
		}*/

		//glUniformMatrix4fv(uniModel, 1, GL_FALSE, value_ptr(model));
		glUniformMatrix4fv(uniView, 1, GL_FALSE, value_ptr(view));
		glUniformMatrix4fv(uniProj, 1, GL_FALSE, value_ptr(proj));

		glBindVertexArray(0);
		// Swap the screen buffers
		glfwSwapBuffers(window);
		glfwPollEvents();
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		oldTime = time;

	}
	// liberar la memoria de los VAO, EBO y VBO
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteBuffers(1, &EBO);
	glDeleteTextures(1, &texture);
	// Terminate GLFW, clearing any resources allocated by GLFW.
	exit(EXIT_SUCCESS);
}
/*
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode) {
//TODO, comprobar que la tecla pulsada es escape para cerrar la aplicación y la tecla w para cambiar a modo widwframe
}*/
