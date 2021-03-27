#include "Screen.h"
#include "Tools.h"
#include <exception>

Screen::Screen() {
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	monitor = glfwGetPrimaryMonitor();
	mode = glfwGetVideoMode(monitor);
	glfwWindowHint(GLFW_RED_BITS, mode->redBits);
	glfwWindowHint(GLFW_GREEN_BITS, mode->greenBits);
	glfwWindowHint(GLFW_BLUE_BITS, mode->blueBits);
	glfwWindowHint(GLFW_REFRESH_RATE, mode->refreshRate);
	window = glfwCreateWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "OpenGL", nullptr, nullptr);
	if (!window) {
		glfwTerminate();
		throw std::runtime_error("Failed to create GLFW window.");		
	}
	glfwMakeContextCurrent(window);
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) 
		throw std::runtime_error("Failed to initialized GLAD.");
	glEnable(GL_DEPTH_TEST);
}

void Screen::toggleWindowMode() {
	GLFWmonitor* monitor;
	if (!isFullscreen) {
		width = mode->width; height = mode->height;
		monitor = glfwGetPrimaryMonitor();
	}
	else {
		width = SCREEN_WIDTH; height = SCREEN_HEIGHT;
		monitor = nullptr;
	}
	glfwSetWindowMonitor(window, monitor, 100, 100, width, height, GLFW_DONT_CARE);
	isFullscreen = !isFullscreen;
}

bool Screen::shouldClose() {
	return glfwWindowShouldClose(window);
}

void Screen::setShouldClose() {
	glfwSetWindowShouldClose(window, true);
}

void Screen::terminate() {
	glfwTerminate();
}


