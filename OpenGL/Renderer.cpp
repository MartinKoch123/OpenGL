#include "Renderer.h"

Renderer::Renderer(unsigned int width, unsigned int height) {

	this->objects = std::vector<MultiBodyObject*>();
	numberPointLights = 0;

	shaders = ShaderSet("shaders/defaultVS.txt", "shaders/defaultFS.txt", "shaders/textureVS.txt", "shaders/textureFS.txt",
		"shaders/lightSourceVS.txt.", "shaders/lightSourceFS.txt", "shaders/materialMeshVS.txt", "shaders/materialMeshFS.txt",
		"shaders/particleVS.txt", "shaders/particleFS.txt", "shaders/defaultShadowMappingVS.txt", "shaders/defaultShadowMappingFS.txt", 
		"shaders/depthMapVS.txt", "shaders/depthMapFS.txt", "shaders/instancingShadowMappingVS.txt");
	setSize(width, height);

	//glEnable(GL_CULL_FACE);

	// Shadow mapping
	glGenFramebuffers(1, &depthMapFBO);
	glGenTextures(1, &depthMap);
	glBindTexture(GL_TEXTURE_2D, depthMap);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT,
		SHADOW_MAP_RESOLUTION, SHADOW_MAP_RESOLUTION, 0, GL_DEPTH_COMPONENT, GL_FLOAT, NULL);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);
	float borderColor[] = { 1.0f, 1.0f, 1.0f, 1.0f };
	glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, borderColor);

	glBindFramebuffer(GL_FRAMEBUFFER, depthMapFBO);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, depthMap, 0);
	glDrawBuffer(GL_NONE);
	glReadBuffer(GL_NONE);
	glBindFramebuffer(GL_FRAMEBUFFER, 0);

	shaders.defaultShader->setInt("shadowMap", 0);

	// depth debug
	float depthQuadVertices[] = {
		// positions        // texture Coords
		-1.0f,  1.0f, 0.0f, 0.0f, 1.0f,
		-1.0f, -1.0f, 0.0f, 0.0f, 0.0f,
		1.0f,  1.0f, 0.0f, 1.0f, 1.0f,
		1.0f, -1.0f, 0.0f, 1.0f, 0.0f,
	};
	// setup plane VAO
	glGenVertexArrays(1, &depthQuadVAO);
	glGenBuffers(1, &depthQuadVAO);
	glBindVertexArray(depthQuadVAO);
	glBindBuffer(GL_ARRAY_BUFFER, depthQuadVAO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(depthQuadVertices), &depthQuadVertices, GL_STATIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));

	shaders.depthMapShader->use();
	shaders.depthMapShader->setInt("depthMap", 0);

}

void Renderer::draw() {

	// Shadow mapping
	glViewport(0, 0, SHADOW_MAP_RESOLUTION, SHADOW_MAP_RESOLUTION);
	glBindFramebuffer(GL_FRAMEBUFFER, depthMapFBO);
	glClear(GL_DEPTH_BUFFER_BIT);
	
	for (unsigned int iMBO = 0; iMBO < objects.size(); iMBO++) {
		MBO = objects[iMBO];
		if (MBO == NULL)
			continue;
		MBO->renderDepthMap(&shaders);
	}
	glBindFramebuffer(GL_FRAMEBUFFER, 0);

	// Draw Frame
	glViewport(0, 0, width, height);
	glClearColor(backgroundColor.x, backgroundColor.y, backgroundColor.z, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, depthMap);

	// Normal rendering
	if (!renderDepthMap) {
		for (unsigned int iMBO = 0; iMBO < objects.size(); iMBO++) {
			MBO = objects[iMBO];
			if (MBO == NULL)
				continue;
			MBO->draw(&shaders);
		}
	}

	// Depth map
	else {
		shaders.depthMapShader->use();
		shaders.depthMapShader->setFloat("near_plane", 0.1f);
		shaders.depthMapShader->setFloat("far_plane", RENDER_DISTANCE);
		glBindVertexArray(depthQuadVAO);
		glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
		glBindVertexArray(0);
	}
}

void Renderer::addMultiBodyObject(MultiBodyObject * object) {
	this->objects.push_back(object);
	for (unsigned int i = 0; i < object->getNumberPointLights(); i++) {
		shaders.setLight(object->getPointLight(i), object->getModelMatrix(), numberPointLights);
		numberPointLights++;
	}
	if (numberPointLights > 0)
		shaders.setNumberPointLights(numberPointLights);
}

void Renderer::setDirectioalLight(DirectionalLight light) {
	shaders.setLight(light);
}

void Renderer::setView(glm::mat4 viewMatrix, glm::vec3 viewPosition) {
	shaders.setViewMatrix(viewMatrix);
	shaders.setViewPosition(viewPosition);
}

void Renderer::setSize(unsigned int width, unsigned int height) {
	this->width = width;
	this->height = height;
	glm::mat4 projection = glm::perspective(glm::radians(45.0f), (float)width / (float)height, 0.1f, RENDER_DISTANCE);
	shaders.setProjectionMatrix(projection);
}







