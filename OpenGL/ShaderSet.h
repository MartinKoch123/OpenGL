#pragma once
#include "Shader.h"
#include "PointLight.h"
#include <glm\glm.hpp>
#include <vector>
#include "Tools.h"

class ShaderSet {
public:
	ShaderSet(char* defaultVertexPath, char* defaultFragmentPath, char* textureVertexPath, char* textureFragmentPath, 
		char* lightSourceVertexPath, char* lightSourceFragmentPath, char* materialMeshVertexPath, char* materialMeshFragmentPath, 
		char* particleVertexPath, char* particleFragmentPath, char* defaultShadowMappingVertexPath, char* defaultShadowMappingFragmentPath, 
		char* depthMapVertexPath, char* depthMapFragmentPath, char* instancingShadowMappingVertexPath);
	ShaderSet() {};
	void setViewMatrix(glm::mat4 matrix);
	void setProjectionMatrix(glm::mat4 matrix);
	void setLight(PointLight * light, glm::mat4 bodyMatrix, unsigned int lightIndex);
	void setLight(DirectionalLight light);
	void setViewPosition(glm::vec3 position);
	void setNumberPointLights(int numberPointLights);
	Shader* defaultShader;
	Shader* textureShader;
	Shader* lightSourceShader;
	Shader* materialMeshShader;
	Shader* particleShader;
	Shader* defaultShadowMappingShader;
	Shader* instancingShadowMappingShader;
	Shader* depthMapShader;
private:
	std::vector<Shader*> allShaders;
	std::vector<Shader*> lightingShaders;
	std::vector<Shader*> shadowMappingShaders;
	glm::mat4 lightSpaceProjection;
	glm::mat4 lightSpaceView;
	glm::vec3 lightSourceDirection;
};

