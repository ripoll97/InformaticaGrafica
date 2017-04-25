#include "Camera.h"

Camera::Camera(vec3 position, vec3 direction, GLfloat sensibility2, GLfloat fov) {
	cameraPos = position;
	cameraFront = normalize(direction - position);
	sensibility = sensibility2;
	FOV = fov;
	cameraVel = 13.0;
	firstMouse = true;
};

mat4 Camera::LookAt() {
		cout << FOV << endl;

	return lookAt(cameraPos, cameraPos + cameraFront, cameraUp);
}

/*mat4 Camera::LookAt() {
	vec3 directionVec, upVec, rightVec;
	vec3 upWorld(0.0, 1.0, 0.0);
	
	//directionVec = normalize(cameraFront - cameraPos);
	directionVec = normalize(cameraFront - cameraPos);
	rightVec = normalize(cross(directionVec, upWorld));
	upVec = cross(directionVec, rightVec);

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
	);

	mat4 positionMat(
		1, 0, 0, 0,
		0, 1, 0, 0,
		0, 0, 1, 0,
		-(cameraPos.x), -(cameraPos.y), -(cameraPos.z), 1
	);
	
	return lookAtMat * positionMat;
	//return lookAt(cameraPos, cameraPos + cameraFront, cameraUp);
}*/

void Camera::DoMovement(GLFWwindow* window) {

	dt = glfwGetTime() - lastFrame;

	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
		cameraPos += dt * cameraVel * cameraFront;
		//cameraFront.z -= dt * cameraVel;
	}
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
		cameraPos -= dt * cameraVel * cameraFront;
		//cameraFront.z += dt * cameraVel;
	}
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
		cameraPos -= normalize(cross(cameraFront, cameraUp)) * cameraVel * dt;
	//cameraFront.x -= dt * cameraVel;

	}
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
		cameraPos += normalize(cross(cameraFront, cameraUp)) * cameraVel * dt;
		//cameraFront.x += dt * cameraVel;
	}
	lastFrame = glfwGetTime();
}

void Camera::MouseMove(GLFWwindow* window, double xpos, double ypos) {
	if (firstMouse) {
		lastMx = xpos;
		lastMy = ypos;
		firstMouse = false;
	}
	
	GLfloat xOffset = xpos - lastMx;
	GLfloat yOffset = lastMy - ypos;
	lastMx = xpos;
	lastMy = ypos;

	xOffset *= sensibility;
	yOffset *= sensibility;

	YAW += xOffset;
	PITCH += yOffset;

	PITCH = clamp(PITCH, -89.0f, 89.0f);
	YAW = mod(YAW, 360.0f);

	vec3 front;

	front.x = cos(radians(PITCH)) * cos(radians(YAW));
	front.y = sin(radians(PITCH));
	front.z = cos(radians(PITCH)) * sin(radians(YAW));

	cameraFront = normalize(front);
}

/*void Camera::MouseMove(GLFWwindow* window, double xpos, double ypos) {
	offsetX = xpos - lastMx;
	offsetY = ypos - lastMy;

	offsetX *= sensibility;
	offsetY *= sensibility;

	YAW += offsetX * 10;
	PITCH += offsetY * 10;
	
 	PITCH = clamp(PITCH, -89.f, 89.f);
	YAW = mod(YAW, 360.f);

	cout << YAW << " " << PITCH << endl;
	//cout << cameraFront.x << " | " << cameraFront.y << " | " << cameraFront.z << endl;

	vec3 dir;

	dir.x = cos(radians(PITCH)) * cos(radians(YAW));
	dir.y = sin(radians(PITCH));
	dir.z = cos(radians(PITCH)) * sin(radians(YAW));

	cameraFront = normalize(dir);
	//cout << cameraFront.x << " | " << cameraFront.y << " | " << cameraFront.z << endl;
	//cameraFront = dir;

	lastMx = xpos;
	lastMy = ypos;

}*/

void Camera::MouseScroll(GLFWwindow* window, double xScroll, double yScroll) {
	cout << yScroll << endl;
	if (FOV >= 1.0f && FOV <= 45.0f)
		FOV -= yScroll * dt;
	if (FOV <= 1.0f)
		FOV = 1.0;
	if (FOV >= 45.0f)
		FOV = 45.0f;
}

GLfloat Camera::GetFOV() {
	return FOV;
}
