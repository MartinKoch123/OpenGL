#pragma once
#define SCENARIO 0 //0: SingleTrack, 1: Quadcopter flight, 2: Quadcopter control
#define FULLSCREEN 0


#include <glad/glad.h>
//#define GLFW_INCLUDE_NONE
#include <GLFW\glfw3.h>
#include <glm/detail/setup.hpp>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <iostream>
#include <vector>
#include <string>
#include "Shader.h"
#include "stb_image.h"
#include "ShaderSet.h"
#include "Renderer.h"
#include "QuadcopterScenario.h"
#include "Tools.h"
#include "Mat.h"
#include "GLMcheckError.h"
#include "SingleTrackScenario.h"
#include "CopterControlScenario.h"


void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void getKeyStates(KeyStates* keyStates, GLFWwindow *window);

// settings
float lastX = SCREEN_WIDTH / 2.0f;
float lastY = SCREEN_HEIGHT / 2.0f;
glm::vec3 backgroundColor = glm::vec3(135, 206, 235)/256.0f;
bool firstMouse = true;
Scenario* scenario;

float lastFrame = 0.0f;
float deltaTime = 0.0f;


unsigned int screenWidth = SCREEN_WIDTH;
unsigned int screenHeight = SCREEN_HEIGHT;

unsigned int KEY_RESTART = GLFW_KEY_F5;
unsigned int KEY_QUIT = GLFW_KEY_ESCAPE;


int main() {

	// glfw: initialize and configure
	// ------------------------------
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	// glfw window creation
	// --------------------
	GLFWmonitor* monitor = glfwGetPrimaryMonitor();
	const GLFWvidmode* mode = glfwGetVideoMode(monitor);
	glfwWindowHint(GLFW_RED_BITS, mode->redBits);
	glfwWindowHint(GLFW_GREEN_BITS, mode->greenBits);
	glfwWindowHint(GLFW_BLUE_BITS, mode->blueBits);
	glfwWindowHint(GLFW_REFRESH_RATE, mode->refreshRate);
	GLFWwindow* window;
#if FULLSCREEN
	screenWidth = mode->width;
	screenHeight = mode->height;
		window = glfwCreateWindow(mode->width, mode->height, "My Title", monitor, NULL);
#else
	screenWidth = SCREEN_WIDTH;
	screenHeight = SCREEN_HEIGHT; 
	window = glfwCreateWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "LearnOpenGL", NULL, NULL);
#endif
	if (window == NULL) {
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
	glfwSetCursorPosCallback(window, mouse_callback);
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	// Initialize GLEW to setup the OpenGL Function pointers

	// glad: load all OpenGL function pointers
	// ---------------------------------------
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		std::cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	}
	glEnable(GL_DEPTH_TEST);

	// Text
	TextRenderer::initialize(screenWidth, screenHeight);

	// World
	Renderer renderer = Renderer(screenWidth, screenHeight);
	renderer.backgroundColor = backgroundColor;
	

	ObjectGenerator generator = ObjectGenerator();
#if SCENARIO == 0
	scenario = new SingleTrackScenario(&renderer, window, &generator);
#elif SCENARIO == 1
	scenario = new QuadcopterScenario(&renderer, window, &generator);
#else
	scenario = new CopterControlScenario(&renderer, &generator);
#endif
	KeyboardEvents keyboardEvents;
	KeyStates keyStates;

	
	deltaTime = 0;
	lastFrame = 0;
		
	while (!glfwWindowShouldClose(window)) {
		
		getKeyStates(&keyStates, window);
		keyboardEvents.update(keyStates);
		if (keyboardEvents.isPressed(KEY_QUIT))
			glfwSetWindowShouldClose(window, true);
		if (keyboardEvents.isPressed(KEY_RESTART))
			scenario->restart();
		
		renderer.processKeyboardEvents(&keyboardEvents);
		renderer.setView(scenario->getViewMatrix(), scenario->getCameraPosition());
		renderer.draw();

		scenario->onFrameChange(&keyboardEvents, deltaTime);

		glfwSwapBuffers(window);
		glfwPollEvents();

		deltaTime = (float)glfwGetTime() - lastFrame;
		lastFrame = (float)glfwGetTime();
	}

	glfwTerminate();
	return 0;
}

void getKeyStates(KeyStates * keyStates, GLFWwindow * window) {
	if (keyStates == NULL || window == NULL)
		return;
	for (unsigned int i = 0; i < NUMBER_GLFW_KEYS; i++) {
		keyStates->states[i] = glfwGetKey(window, i);
	}
}

void mouse_callback(GLFWwindow* window, double xpos, double ypos) {
	
	if (firstMouse) {
		lastX = (float)xpos;
		lastY = (float)ypos;
		firstMouse = false;
	}
	float xoffset = (float)xpos - lastX;
	float yoffset = lastY - (float)ypos;
	lastX = (float)xpos;
	lastY = (float)ypos;

	scenario->mouseCallback((float)xoffset, (float)yoffset);
}

// glfw: whenever the window size changed (by OS or user resize) this callback function executes
// ---------------------------------------------------------------------------------------------
void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
	// make sure the viewport matches the new window dimensions; note that width and 
	// height will be significantly larger than specified on retina displays.
	glViewport(0, 0, width, height);
}




