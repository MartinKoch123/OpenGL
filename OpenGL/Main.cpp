#pragma once
#include <glad/glad.h>
#include <GLFW\glfw3.h>
#include <glm/detail/setup.hpp>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <iostream>
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
#include "Screen.h"

enum class ScenarioType { SingleTrack, QuadcopterFlight, QuadcopterControl };

using std::unique_ptr;

//constexpr ScenarioType SCENARIO_TYPE = ScenarioType::SingleTrack;
constexpr ScenarioType SCENARIO_TYPE = ScenarioType::QuadcopterFlight;

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void getKeyStates(KeyStates &keyStates, GLFWwindow *window);

glm::vec3 BACKGROUND_COLOR = glm::vec3(135, 206, 235)/256.0f;
constexpr unsigned int HOTKEY_RESTART = GLFW_KEY_F5;
constexpr unsigned int HOTKEY_QUIT = GLFW_KEY_ESCAPE;
constexpr unsigned int HOTKEY_TOGGLE_WINDOW_MODE = GLFW_KEY_F10;
constexpr unsigned int HOTKEY_TOGGLE_DEPTH_MAP_MODE = GLFW_KEY_F9;

float lastX = 0, lastY = 0;
float lastFrame = 0.0f, deltaTime = 0.0f;
bool isFirstMouseMovement = false;
unique_ptr<Scenario> scenario;
unique_ptr<Screen> screen;
KeyboardEvents keyboardEvents;
KeyStates keyStates;
Renderer renderer;

int main() {

	try {
		screen = unique_ptr<Screen>(new Screen()); }
	catch (std::runtime_error& e) {
		std::cout  << e.what() << std::endl; return 1; }
	glfwSetFramebufferSizeCallback(screen->getWindow(), framebuffer_size_callback);
	glfwSetCursorPosCallback(screen->getWindow(), mouse_callback);

	TextRenderer::initialize(SCREEN_WIDTH, SCREEN_HEIGHT);

	renderer = Renderer(SCREEN_WIDTH, SCREEN_HEIGHT);
	renderer.backgroundColor = BACKGROUND_COLOR;

	ObjectGenerator generator = ObjectGenerator();
	if (SCENARIO_TYPE == ScenarioType::SingleTrack)
		scenario = unique_ptr<Scenario>(new SingleTrackScenario(&renderer, &generator));
	else if (SCENARIO_TYPE == ScenarioType::QuadcopterFlight)
		scenario = unique_ptr<Scenario>(new QuadcopterScenario(&renderer, &generator));
	else
		scenario = unique_ptr<Scenario>(new CopterControlScenario(&renderer, &generator));
		
	while (!screen->shouldClose()) {
		
		glfwPollEvents();
		getKeyStates(keyStates, screen->getWindow());
		keyboardEvents.update(keyStates);
		if (keyboardEvents.isPressed(HOTKEY_QUIT))
			screen->setShouldClose();
		if (keyboardEvents.isPressed(HOTKEY_RESTART))
			scenario->restart();
		if (keyboardEvents.wasTapped(HOTKEY_TOGGLE_WINDOW_MODE)) 
			screen->toggleWindowMode();
		if (keyboardEvents.wasTapped(HOTKEY_TOGGLE_DEPTH_MAP_MODE))
			renderer.toggleDepthMapMode();
	
		renderer.setView(scenario->getViewMatrix(), scenario->getCameraPosition());
		renderer.draw();

		scenario->onFrameChange(&keyboardEvents, deltaTime);

		screen->swapBuffers();

		deltaTime = glfwGetTime() - lastFrame;
		lastFrame = glfwGetTime();
	}

	screen->terminate();
	return 0;
}

void getKeyStates(KeyStates &keyStates, GLFWwindow * window) {
	if (!window)
		return;
	for (unsigned int i = 0; i < NUMBER_GLFW_KEYS; i++) 
		keyStates.states[i] = glfwGetKey(window, i);
}

void mouse_callback(GLFWwindow* window, double xpos, double ypos) {
	if (isFirstMouseMovement) {
 		lastX = xpos; lastY = ypos;
		isFirstMouseMovement = false;
	}
	float xoffset = xpos - lastX;
	float yoffset = lastY - ypos;
	lastX = xpos; lastY = ypos;
	scenario->mouseCallback(xoffset, yoffset);
}

// GLFW: whenever the window size changed (by OS or user resize) this callback function executes
void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
	// make sure the viewport matches the new window dimensions; note that width and 
	// height will be significantly larger than specified on retina displays.
	renderer.setSize(width, height);
	TextRenderer::initialize(width, height);
	glViewport(0, 0, width, height);
}




