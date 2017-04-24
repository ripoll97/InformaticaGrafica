#include "Camera.h"

Camera::Camera(vec3 position, vec3 direction, GLfloat sensibility2, GLfloat fov) {
	cameraPos = position;
	cameraFront = direction;
	sensibility = sensibility2;
	FOV = fov;
	cameraVel = 13.0;
};

mat4 Camera::LookAt() {
	vec3 directionVec, upVec, rightVec;
	vec3 upWorld(0.0, 1.0, 0.0);

	directionVec = normalize(cameraFront - cameraPos);
	
	/*
	directionVec.x = cos(YAW * sin(PITCH));
	directionVec.y = sin(PITCH);
	directionVec.z = sin(YAW * cos(PITCH));
	*/

	rightVec = normalize(cross(directionVec, upWorld));
	upVec = normalize(cross(directionVec, rightVec));

	mat4 lookAtMat(
		rightVec.x, upVec.x, -directionVec.x, 0,
		rightVec.y, upVec.y, -directionVec.y, 0,
		rightVec.z, upVec.z, -directionVec.z, 0,
		0, 0, 0, 1
	);

	/*mat4 lookAtMat(
	rightVec.x, rightVec.y, rightVec.z, 0,
	upVec.x, upVec.y, upVec.z, 0,
	-directionVec.x, -directionVec.y, -directionVec.z, 0,
	0, 0, 0, 1
	);*/

	mat4 positionMat(
		1, 0, 0, 0,
		0, 1, 0, 0,
		0, 0, 1, 0,
		-(cameraPos.x), -(cameraPos.y), -(cameraPos.z), 1
	);

	return lookAtMat * positionMat;
}

void Camera::DoMovement(GLFWwindow* window) {

	dt = glfwGetTime() - lastFrame;

	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
		cameraPos.z -= dt * cameraVel;
		//cameraFront.z -= dt * cameraVel;
	}
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
		cameraPos.z += dt * cameraVel;
		//cameraFront.z += dt * cameraVel;
	}
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
		cameraPos.x -= dt * cameraVel;
		//cameraFront.x -= dt * cameraVel;

	}
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
		cameraPos.x += dt * cameraVel;
		//cameraFront.x += dt * cameraVel;
	}
	lastFrame = glfwGetTime();
}

void Camera::MouseMove(GLFWwindow* window, double xpos, double ypos) {
	offsetX = xpos - lastMx;
	offsetY = ypos - lastMy;

	lastMx = xpos;
	lastMy = ypos;
	
	offsetX *= sensibility;
	offsetY *= sensibility;

	YAW += offsetX;
	PITCH += offsetY;
	
 	PITCH = clamp(PITCH, -89.f, 89.f);
	YAW = mod(YAW, 360.f);

	cout << "Despres		Yaw: " << YAW << " Pitch: " << PITCH << endl;

	vec3 dir;
	
	dir.x = cos(radians(YAW)) * sin(radians(YAW));
	dir.y = sin(radians(PITCH));
	dir.z = sin(radians(YAW)) * cos(radians(PITCH));

	cameraFront = normalize(dir);
	//cameraFront = dir;
}

void Camera::MouseScroll(GLFWwindow* window, double xScroll, double yScroll) {

}

GLfloat Camera::GetFOV() {
	return FOV;
}
