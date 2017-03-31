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


using namespace std;
using namespace glm;

const GLint WIDTH = 800, HEIGHT = 600;
bool WIDEFRAME = false;
int Numbuffer = 1;
float fadeValue = 0;
int rotationValue = 50;

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode) {
	//cuando se pulsa una tecla escape cerramos la aplicacion
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
		glfwSetWindowShouldClose(window, GL_TRUE);
		cout << "Meelassa, campo" << endl;
	}
	if (key == GLFW_KEY_W && action == GLFW_PRESS) {
		WIDEFRAME = !WIDEFRAME;
	}
	if (key == GLFW_KEY_UP) {
		if (fadeValue < 1)
			fadeValue += 0.1;
	}
	if (key == GLFW_KEY_DOWN) {
		if (fadeValue > 0)
			fadeValue -= 0.1;
	}
	if (key == GLFW_KEY_LEFT) {
		rotationValue = (rotationValue + 3) % 360;
		cout << rotationValue << endl;
	}
	if (key == GLFW_KEY_RIGHT) {
		rotationValue = (rotationValue - 3) % 360;
		cout << rotationValue << endl;
	}
}


int main() {
	//initGLFW
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
	glfwSetKeyCallback(window, key_callback);
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
		vec3(2.0f ,  5.0f, -15.0f),
		vec3(-1.5f, -2.2f, -2.5f),
		vec3(-3.8f, -2.0f, -12.3f),
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
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(VertexBufferObject), VertexBufferObject, GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(IndexBufferObject), IndexBufferObject, GL_STATIC_DRAW);

	glBindTexture(GL_TEXTURE_2D, 0);
	//Establecer las propiedades de los vertices

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GL_FLOAT), (GLvoid*)0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GL_FLOAT), (GLvoid*)(3 * sizeof(GL_FLOAT)));
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(GL_FLOAT), (GLvoid*)(6 * sizeof(GL_FLOAT)));
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
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
	glGenTextures(2, &texture2);
	glBindTexture(GL_TEXTURE_2D, texture2);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	int width2, height2;
	unsigned char* image2 = SOIL_load_image("./src/InBread.png", &width2, &height2, 0, SOIL_LOAD_RGB);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width2, height2, 0, GL_RGB, GL_UNSIGNED_BYTE, image2);
	SOIL_free_image_data(image2);


	//liberar el buffer
	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindTexture(GL_TEXTURE_2D, 0);
	//glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	//liberar el buffer de vertices

	GLint variableShader = glGetUniformLocation(shdr.Program, "shaderVariable");
	GLfloat variableFade = glGetUniformLocation(shdr.Program, "fade");
	GLint uniModel = glGetUniformLocation(shdr.Program, "model");
	GLint uniView = glGetUniformLocation(shdr.Program, "view");
	GLint uniProj = glGetUniformLocation(shdr.Program, "proj");

	//bucle de dibujado
	while (!glfwWindowShouldClose(window))
	{

		mat4 transformationMatrix, escalationMatrix, translationMatrix1, translationMatrix2, rotationMatrix, model, view, proj;

		// Definir las matrices de transformacion
		//escalationMatrix = scale(escalationMatrix, vec3(0.5f, 0.5f, 0.0f));
		translationMatrix1 = translate(translationMatrix1, vec3(0.0f, -0.5f, 0.0f));
		rotationMatrix = rotate(rotationMatrix, radians(float(rotationValue)), vec3(1.0f, 0.0f, 0.0f));

		model = translationMatrix1 * rotationMatrix * model;

		translationMatrix2 = translate(translationMatrix2, vec3(0.0, 0.0f, -0.3f));
		// No funciona
		//view = translationMatrix2 * view;

		// lookAt sacado de Open.gl
		view = lookAt(
			vec3(1.2f, 1.2f, 1.2f),
			vec3(0.0f, 0.0f, 0.0f),
			vec3(0.0f, 0.0f, 1.0f)
		);

		proj = perspective(radians(60.0f), 800.0f / 600.0f, 1.0f, -10.0f);

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
		//pintar con lineas
		if (WIDEFRAME) {
			glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
			glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
		}
		//pintar con triangulos
		if (!WIDEFRAME) {
			glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
			glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
		}

		glUniformMatrix4fv(uniModel, 1, GL_FALSE, value_ptr(model));
		glUniformMatrix4fv(uniView, 1, GL_FALSE, value_ptr(view));
		glUniformMatrix4fv(uniProj, 1, GL_FALSE, value_ptr(proj));

		glBindVertexArray(0);
		// Swap the screen buffers
		glfwSwapBuffers(window);
		glfwPollEvents();
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
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
