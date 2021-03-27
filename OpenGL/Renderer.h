#pragma once
#include "Object.h"
#include "PointLight.h"
#include <vector>
#include "ShaderSet.h"
#include "Material.h"
#include <glm\glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "Tools.h"
#include "MultiBodyObject.h"
#include "KeyboardEvents.h"

class Renderer {
public:
	Renderer() {};
	Renderer(unsigned int with, unsigned int height);
	void draw();
	void addMultiBodyObject(MultiBodyObject* object);
	void setDirectioalLight(DirectionalLight light);
	void setView(glm::mat4 viewMatrix, glm::vec3 viewPosition);
	void processKeyboardEvents(KeyboardEvents* events);
	glm::vec3 backgroundColor;
	unsigned int getWidth() { return width; }
	unsigned int getHeight() { return height; }
	void setSize(unsigned int width, unsigned int height);
private:
	unsigned int width;
	unsigned int height;
	unsigned int depthMap;
	unsigned int depthMapFBO;
	unsigned int depthQuadVAO;
	glm::mat4 projection;
	std::vector<MultiBodyObject*> objects;
	ShaderSet shaders;
	unsigned int numberPointLights;
	MultiBodyObject* MBO;
	bool renderDepthMap = false;
};


