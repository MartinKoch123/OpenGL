#pragma once
#include <glad/glad.h>
#include <GLFW\glfw3.h>
#include <glm/detail/setup.hpp>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class Screen {
public:
	Screen();
	void terminate();
	void toggleWindowMode();
	unsigned int getWidth() { return width; };
	unsigned int getHeight() { return height; };
	GLFWwindow* getWindow() { return window; };
	bool shouldClose();
	void setShouldClose();
	void swapBuffers();
private:
	unsigned int width{ 100 }, height{ 100 };
	bool isFullscreen{ false };
	GLFWmonitor* monitor{ nullptr };
	const GLFWvidmode* mode{ nullptr };
	GLFWwindow* window{ nullptr };
};


