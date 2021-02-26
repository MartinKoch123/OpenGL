#include "ShaderSet.h"



ShaderSet::ShaderSet(char* defaultVertexPath, char* defaultFragmentPath, char* textureVertexPath, char* textureFragmentPath, 
		char* lightSourceVertexPath, char* lightSourceFragmentPath, char* materialMeshVertexPath, char* materialMeshFragmentPath,
		char* particleVertexPath, char* particleFragmentPath, char* defaultShadowMappingVertexPath, char* defaultShadowMappingFragmentPath, 
		char* depthMapVertexPath, char* depthMapFragmentPath, char* instancingShadowMappingVertexPath) {
	defaultShader = new Shader(defaultVertexPath, defaultFragmentPath);
	lightSourceShader = new Shader(lightSourceVertexPath, lightSourceFragmentPath);
	textureShader = new Shader(textureVertexPath, textureFragmentPath);
	materialMeshShader = new Shader(materialMeshVertexPath, materialMeshFragmentPath);
	particleShader = new Shader(particleVertexPath, particleFragmentPath);
	defaultShadowMappingShader = new Shader(defaultShadowMappingVertexPath, defaultShadowMappingFragmentPath);
	instancingShadowMappingShader = new Shader(instancingShadowMappingVertexPath, defaultShadowMappingFragmentPath);
	depthMapShader = new Shader(depthMapVertexPath, depthMapFragmentPath);
	allShaders = std::vector<Shader*>();
	lightingShaders = std::vector<Shader*>();
	shadowMappingShaders = std::vector<Shader*>();
	allShaders.push_back(defaultShader);
	allShaders.push_back(lightSourceShader);
	allShaders.push_back(textureShader);
	allShaders.push_back(materialMeshShader);
	allShaders.push_back(particleShader);
	lightingShaders.push_back(defaultShader);
	lightingShaders.push_back(textureShader);
	lightingShaders.push_back(materialMeshShader);
	lightingShaders.push_back(particleShader);
	shadowMappingShaders.push_back(defaultShadowMappingShader);
	shadowMappingShaders.push_back(instancingShadowMappingShader);
	setLight(DirectionalLight());
	lightSpaceProjection = glm::mat4(1.0f);
	lightSpaceView = glm::lookAt(-50.0f * glm::normalize(glm::vec3(-1.0f)), glm::vec3(0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
	lightSourceDirection = glm::vec3(1.0f);
}

void ShaderSet::setViewMatrix(glm::mat4 matrix) {
	for (unsigned int i = 0; i < allShaders.size(); i++) {
		allShaders[i]->use();
		allShaders[i]->setMat4("view", matrix);
	}
}

void ShaderSet::setProjectionMatrix(glm::mat4 matrix) {
	for (unsigned int i = 0; i < allShaders.size(); i++) {
		allShaders[i]->use();
		allShaders[i]->setMat4("projection", matrix);
	}
}

void ShaderSet::setLight(PointLight* light, glm::mat4 bodyMatrix, unsigned int lightIndex) {
	for (unsigned int i = 0; i < lightingShaders.size(); i++) {
		lightingShaders[i]->use();
		lightingShaders[i]->setVec3("pointLights[" + std::to_string(lightIndex) + "].position", glm::vec3(bodyMatrix * glm::vec4(light->position, 1.0f)));
		lightingShaders[i]->setVec3("pointLights[" + std::to_string(lightIndex) + "].lightColors.ambient", light->lightColors.ambient);
		lightingShaders[i]->setVec3("pointLights[" + std::to_string(lightIndex) + "].lightColors.diffuse", light->lightColors.diffuse);
		lightingShaders[i]->setVec3("pointLights[" + std::to_string(lightIndex) + "].lightColors.specular", light->lightColors.specular);
		lightingShaders[i]->setVec3("pointLights[" + std::to_string(lightIndex) + "].attenuation", light->attenuation);
	}
}

void ShaderSet::setLight(DirectionalLight light) {

	// Depth rendering
	lightSpaceProjection = glm::ortho(-SHADOW_MAP_SIZE/2.0f, SHADOW_MAP_SIZE/2.0f, -SHADOW_MAP_SIZE/2.0f, SHADOW_MAP_SIZE/2.0f, SHADOW_MAPPING_NEAR_PLANE, SHADOW_MAPPING_FAR_PLANE);
	lightSourceDirection = -50.0f * glm::normalize(light.direction);

	//lightSpaceView = glm::lookAt(-50.0f * light.direction, glm::vec3(0.0f), glm::vec3(0.0f, 1.0f, 0.0f));

	for (unsigned int i = 0; i < shadowMappingShaders.size(); i++) {
		shadowMappingShaders[i]->use();
		shadowMappingShaders[i]->setMat4("lightSpaceMatrix", lightSpaceProjection * lightSpaceView);
	}

	for (unsigned int i = 0; i < lightingShaders.size(); i++) {
		lightingShaders[i]->use();
		lightingShaders[i]->setVec3("directionalLight.direction", light.direction);
		lightingShaders[i]->setVec3("directionalLight.lightColors.ambient", light.lightColors.ambient);
		lightingShaders[i]->setVec3("directionalLight.lightColors.diffuse", light.lightColors.diffuse);
		lightingShaders[i]->setVec3("directionalLight.lightColors.specular", light.lightColors.specular);
		lightingShaders[i]->setMat4("lightSpaceMatrix", lightSpaceProjection * lightSpaceView);
	}
}

void ShaderSet::setViewPosition(glm::vec3 position) {

	glm::vec3 positionInPlane = position;
	positionInPlane.y = 0.0f;
	lightSpaceView = glm::lookAt(lightSourceDirection + positionInPlane, positionInPlane, glm::vec3(0.0f, 1.0f, 0.0f));

	for (unsigned int i = 0; i < lightingShaders.size(); i++) {
		lightingShaders[i]->use();
		lightingShaders[i]->setVec3("viewPosition", position);
		lightingShaders[i]->setMat4("lightSpaceMatrix", lightSpaceProjection * lightSpaceView);
	}

	for (unsigned int i = 0; i < shadowMappingShaders.size(); i++) {
		shadowMappingShaders[i]->use();
		shadowMappingShaders[i]->setMat4("lightSpaceMatrix", lightSpaceProjection * lightSpaceView);
	}
}

void ShaderSet::setNumberPointLights(int numberPointLights) {
	for (unsigned int i = 0; i < lightingShaders.size(); i++) {
		lightingShaders[i]->use();
		lightingShaders[i]->setInt("numberPointLights", numberPointLights);
	}
}

