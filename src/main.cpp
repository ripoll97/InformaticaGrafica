//GLEW
#define GLEW_STATIC
#include <GL\glew.h>
//GLFW
#include <GLFW\glfw3.h>
#include <iostream>
#include "Shader.h"
#include "src\SOIL.h"

#include <glm.hpp>
#include <gtc\matrix_transform.hpp>
#include <gtc\type_ptr.hpp>

#include <time.h>

#include "Camera.h"
#include "Model.h"
#include "Mesh.h"
#include "Object.h"

using namespace std;
using namespace glm;

const GLint WIDTH = 800, HEIGHT = 600;
bool WIDEFRAME = false;
int Numbuffer = 1;
float fadeValue = 0;
int rotationValue = 0;
int rotationValueY = 0;
int automaticRotation;

vec3 cameraPosition(0.0, 0.0, 5);
vec3 cameraDirectionPoint;
float cameraVelocity = 13.0f;
GLfloat cameraSensibility = 0'02;

float offsetX = 0;
float offsetY = 0;
float pitchVal, yawVal;
float lastPosX = WIDTH / 2;
float lastPosY = HEIGHT / 2;
double posX = WIDTH / 2;
double posY = HEIGHT / 2;

// Ilumination variables
vec3 lightPos(3.0f, 0.0, 0.0f);
vec3 objectColor(1.0f, 0.5f, 0.31f);
vec3 lightColor(1.0f, 1.0f, 1.0f);


Camera camara(cameraPosition, cameraDirectionPoint, cameraSensibility, 45.0f);
Object cubeObj(vec3(1.0f, 1.0f, 1.0f), vec3(1.0f, 0.0f, 0.0f), vec3(0.0f, 0.0f, 0.5f), cube);
Object lightCube(vec3(0.2f, 0.2f, 0.2f), vec3(1.0f, 1.0f, 1.0f), vec3(3.0f, 0.0, 0.0f), cube);
vec3 cubePosition(cubeObj.GetPosition());
vec3 cubeRotation(0.0f);

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode) {
	//cuando se pulsa una tecla escape cerramos la aplicacion
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
		glfwSetWindowShouldClose(window, GL_TRUE);
	}

	if (key == GLFW_KEY_LEFT) {
	}
	if (key == GLFW_KEY_RIGHT) {
	
	}
	if (key == GLFW_KEY_UP) {
	
	}
	if (key == GLFW_KEY_DOWN) {
	
	}

	// Cube moves

	if (key == GLFW_KEY_I) {
		cubePosition.z += 0.1;
	}

	if (key == GLFW_KEY_K) {
		cubePosition.z -= 0.1;
	}

	if (key == GLFW_KEY_L) {
		cubePosition.x += 0.1;
	}

	if (key == GLFW_KEY_J) {
		cubePosition.x -= 0.1;
	}

	if (key == GLFW_KEY_O) {
		cubePosition.y -= 0.1;
	}

	if (key == GLFW_KEY_U) {
		cubePosition.y += 0.1;
	}
	if (key == GLFW_KEY_KP_6) {
		cubeRotation.y -= 0.11;
	}	
	if (key == GLFW_KEY_KP_4) {
		cubeRotation.y += 0.1;
	}
	if (key == GLFW_KEY_KP_8) {
		cubeRotation.x += 0.1;
	}
	if (key == GLFW_KEY_KP_2) {
		cubeRotation.x -= 0.1;
	}
	cubeObj.Move(cubePosition);
	cubeObj.Rotate(cubeRotation);	

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

static void cursor_position_callback(GLFWwindow* window, double xpos, double ypos) {
	camara.MouseMove(window, xpos, ypos);
}

void DoRotation() {
	cameraDirectionPoint.x = cos(radians(yawVal)) * cos(radians(pitchVal));
	cameraDirectionPoint.y = sin(radians(pitchVal));
	cameraDirectionPoint.z = sin(radians(yawVal)) * cos(radians(pitchVal));

}

void ScrollValues(GLFWwindow* window, double xoffset, double yoffset) {
	camara.MouseScroll(window, xoffset, yoffset);
}

mat4 createLookAt(vec3 cameraPos, vec3 directionPoint, vec3 upWorldVector) {
	vec3 directionVec, upVec, rightVec;
	vec3 upWorld = upWorldVector;
	
	directionVec = normalize(directionPoint - cameraPos);

	/*directionVec.x = cos(yawVal * sin(pitchVal));
	directionVec.y = sin(pitchVal);
	directionVec.z = sin(yawVal * cos(pitchVal));
	*/
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

int main() {
	camara = Camera(cameraPosition, cameraDirectionPoint, cameraSensibility, 45);

	GLFWwindow* window;
	if (!glfwInit())
		exit(EXIT_FAILURE);
	//set GLFW
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_RESIZABLE, GL_TRUE);

	//create a window
	window = glfwCreateWindow(WIDTH, HEIGHT, "Finestra del projecte", nullptr, nullptr);

	if (!window) {
		cout << "Error al crear la ventana" << endl;
		glfwTerminate();
		exit(EXIT_FAILURE);
	}
	glfwMakeContextCurrent(window);

	//set GLEW and inicializate
	glewExperimental = GL_TRUE;
	if (GLEW_OK != glewInit()) {
		cout << "Error al iniciar glew" << endl;
		glfwTerminate();
		return NULL;
	}

	// Set OpenGl depth for 3D
	glEnable(GL_DEPTH_TEST);

	cubeObj.Start();
	lightCube.Start();
	cubeObj.Rotate(cubeRotation);
	lightCube.Rotate(cubeRotation);
	// Set inputs and callback
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	glfwSetCursorPosCallback(window, cursor_position_callback);
	glfwSetScrollCallback(window, ScrollValues);
	// If we want to move the camera with DoMovement
	//glfwSetKeyCallback(window, camera.DoMovement);


	//cargamos los shader
	//Shader shdr("./src/textureVertexShader.vertexshader", "./src/TextureFragment.fragmentshader");
	//Shader shdrObj("./src/CubeVertexShader.vertexshader", "./src/CubeFragmentShader.fragmentshader");
	Shader shdrObj("./src/Light1.vertexshader", "./src/Light1.fragmentshader");
	Shader lightObj("./src/Light2.vertexshader", "./src/Light2.fragmentshader");

	// Directional Shader
	Shader directionalShader("./src/Light_Directional.vertexshader", "./src/Light_Directional.fragmentshader");

	// Load the model
	//Model ourModel("./Models/spider/spider.obj");

	//set windows and viewport
	int screenWithd, screenHeight;
	glfwGetFramebufferSize(window, &screenWithd, &screenHeight);
	//fondo
	glClear(GL_COLOR_BUFFER_BIT);
	glClearColor(1.0, 1.0, 1.0, 1.0);

#if(false)

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

	//Enlazar el buffer con openGL
	glBindVertexArray(VAO);
	
	//glBindBuffer(GL_ARRAY_BUFFER, VBO);
	//glBufferData(GL_ARRAY_BUFFER, sizeof(VertexBufferObject), VertexBufferObject, GL_STATIC_DRAW);
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

#endif

#if(false)
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
#endif

	//liberar el buffer
	//glBindVertexArray(0);
	//glBindBuffer(GL_ARRAY_BUFFER, 0);
	//glBindTexture(GL_TEXTURE_2D, 0);
	//glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	/* Variables to the shaders
	//GLint variableShader = glGetUniformLocation(shdr.Program, "shaderVariable");
	//GLfloat variableFade = glGetUniformLocation(shdr.Program, "fade");
	//GLint uniModel = glGetUniformLocation(shdr.Program, "model");
	//GLint uniView = glGetUniformLocation(shdr.Program, "view");
	//GLint uniProj = glGetUniformLocation(shdr.Program, "proj");*/

	

	while (!glfwWindowShouldClose(window))
	{
		mat4 transformationMatrix, escalationMatrix, translationMatrix2, view, proj;

		/*// Definir las matrices de transformacion
		//escalationMatrix = scale(escalationMatrix, vec3(0.5f, 0.5f, 0.0f));
		/*translationMatrix1 = translate(translationMatrix1, vec3(0.0f, -0.5f, 0.0f));
		
		rotationMatrix = rotate(rotationMatrix, radians(float(rotationValue)), vec3(1.0f, 0.0f, 0.0f));
		rotationMatrix = rotate(rotationMatrix, radians(float(rotationValueY)), vec3(0.0f, 1.0f, 0.0f));
		
		model = translationMatrix1 * rotationMatrix * model;

		translationMatrix2 = translate(translationMatrix2, vec3(0.0, 0.0f, -0.3f));

		// PROVA --------------------------
		/*	time = glfwGetTime();
		DoMovement(window, dt);
		dt = time - oldTime;
		glfwGetCursorPos(window, &posX, &posY);

		offsetX = posX - lastPosX;
		offsetY = posY - lastPosY;
		

		yawVal += offsetX;
		pitchVal += offsetY;

		yawVal = mod(yawVal, 360.f);
		pitchVal = clamp(pitchVal, -89.f, 89.f);

		DoRotation();
		cout << "Yaw: " << yawVal << "	Pitch: " << pitchVal << endl;
		view = createLookAt(cameraPosition, cameraDirectionPoint, vec3(0.0, 1.0, .0));
		proj = perspective(radians(60.0f), 800.0f / 600.0f, 0.1f, 100.f);

		lastPosX = posX;
		lastPosY = posY;*/



		// Check if any events have been activiated (key pressed, mouse moved etc.) and call corresponding response functions
		glfwSetKeyCallback(window, key_callback);
		camara.DoMovement(window);

		//Establecer el color de fondo
		glClear(GL_COLOR_BUFFER_BIT);
		glClearColor(0.0, 0.0, 0.0, 1.0);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		//establecer el shader
		/*glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, texture);
		glUniform1i(glGetUniformLocation(shdr.Program, "Texture1"), 0);
		glActiveTexture(GL_TEXTURE1);

		glBindTexture(GL_TEXTURE_2D, texture2);
		glUniform1i(glGetUniformLocation(shdr.Program, "Texture2"), 1);
		shdr.USE();
		//glUniform1f(variableShader, 0.4 * abs(sin(glfwGetTime())));
		glUniform1f(variableFade, fadeValue);
		//pitar el VAO
		glBindVertexArray(VAO); */
		
		/*// Automatic rotation
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
			}*/
		
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

		// BIG CUBE
		cubeObj.Draw();
		//shdrObj.USE();
		directionalShader.USE();

		view = camara.LookAt();
		proj = perspective(camara.GetFOV(), 800.0f / 600.0f, 0.1f, 100.f);
		/*glUniformMatrix4fv(glGetUniformLocation(shdrObj.Program, "view"), 1, GL_FALSE, value_ptr(view));
		glUniformMatrix4fv(glGetUniformLocation(shdrObj.Program, "proj"), 1, GL_FALSE, value_ptr(proj));
		glUniformMatrix4fv(glGetUniformLocation(shdrObj.Program, "model"), 1, GL_FALSE, value_ptr(cubeObj.GetModelMatrix()));
		glUniform3f(glGetUniformLocation(shdrObj.Program, "objectColor"), objectColor.x, objectColor.y, objectColor.z);
		glUniform3f(glGetUniformLocation(shdrObj.Program, "lightColor"), lightColor.x, lightColor.y, lightColor.z);
		glUniform3f(glGetUniformLocation(shdrObj.Program, "lightPos"), lightPos.x, lightPos.y, lightPos.z);
		glUniform3f(glGetUniformLocation(shdrObj.Program, "viewPos"), camara.cameraPos.x, camara.cameraPos.y, camara.cameraPos.z);*/

		glUniformMatrix4fv(glGetUniformLocation(directionalShader.Program, "view"), 1, GL_FALSE, value_ptr(view));
		glUniformMatrix4fv(glGetUniformLocation(directionalShader.Program, "proj"), 1, GL_FALSE, value_ptr(proj));
		glUniformMatrix4fv(glGetUniformLocation(directionalShader.Program, "model"), 1, GL_FALSE, value_ptr(cubeObj.GetModelMatrix()));
		glUniform3f(glGetUniformLocation(directionalShader.Program, "objectColor"), objectColor.x, objectColor.y, objectColor.z);
		glUniform3f(glGetUniformLocation(directionalShader.Program, "lightColor"), lightColor.x, lightColor.y, lightColor.z);
		glUniform3f(glGetUniformLocation(directionalShader.Program, "lightPos"), lightPos.x, lightPos.y, lightPos.z);
		glUniform3f(glGetUniformLocation(directionalShader.Program, "viewPos"), camara.cameraPos.x, camara.cameraPos.y, camara.cameraPos.z);

		// LIGHT CUBE
		lightCube.Draw();
		lightObj.USE();
		//view = camara.LookAt();
		//proj = perspective(camara.GetFOV(), 800.0f / 600.0f, 0.1f, 100.f);
		glUniformMatrix4fv(glGetUniformLocation(lightObj.Program, "view"), 1, GL_FALSE, value_ptr(view));
		glUniformMatrix4fv(glGetUniformLocation(lightObj.Program, "proj"), 1, GL_FALSE, value_ptr(proj));
		glUniformMatrix4fv(glGetUniformLocation(lightObj.Program, "model2"), 1, GL_FALSE, value_ptr(lightCube.GetModelMatrix()));

		/*// Model and draw
		mat4 model;
		model = translate(model, vec3(-5.0f, -1.75f, 0.0f));
		model = scale(model, vec3(0.2f));
		glUniformMatrix4fv(glGetUniformLocation(shdrObj.Program, "model"), 1, GL_FALSE, value_ptr(model));
		ourModel.Draw(shdrObj, GL_TRIANGLES);*/

		//glBindVertexArray(0);

		// Swap the screen buffers
		glfwSwapBuffers(window);
		glfwPollEvents();

		//oldTime = time;
	}
	// liberar la memoria de los VAO, EBO y VBO
	//glDeleteVertexArrays(1, &VAO);
	//glDeleteBuffers(1, &VBO);
	//glDeleteBuffers(1, &EBO);
	//glDeleteTextures(1, &texture);
	// Terminate GLFW, clearing any resources allocated by GLFW.
	cubeObj.Delete();
	lightCube.Delete();
	exit(EXIT_SUCCESS);
}
/*
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode) {
//TODO, comprobar que la tecla pulsada es escape para cerrar la aplicación y la tecla w para cambiar a modo widwframe
}*/
