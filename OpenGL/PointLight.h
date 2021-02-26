#pragma once
#include <glm\glm.hpp>



struct ThreeComponentColor {
	ThreeComponentColor(glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular) {
		this->ambient = ambient;
		this->diffuse = diffuse;
		this->specular = specular;
	}
	ThreeComponentColor(glm::vec3 componentWhiteFactors) : 
		ThreeComponentColor(glm::vec3(componentWhiteFactors.x), glm::vec3(componentWhiteFactors.y), glm::vec3(componentWhiteFactors.z)){
	}
	ThreeComponentColor(float whiteFactor) : 
		ThreeComponentColor(glm::vec3(whiteFactor)){
	}
	ThreeComponentColor() {};
	glm::vec3 ambient;
	glm::vec3 diffuse;
	glm::vec3 specular;

};

struct PointLight {
	PointLight(glm::vec3 position, ThreeComponentColor lightColors, glm::vec3 attenuation) {
		this->position = position;
		this->lightColors = lightColors;
		this->attenuation = attenuation;
	}
	PointLight(glm::vec3 position, ThreeComponentColor lightColors, unsigned int brightnessLevel) : 
		PointLight(position, lightColors, getAttenuation(brightnessLevel)){
	}
	ThreeComponentColor lightColors;
	glm::vec3 position;
	glm::vec3 attenuation;
	static glm::vec3 getAttenuation(unsigned int brightnessLevel);
	static float attenuationCoefficients[];
};

struct DirectionalLight {
	DirectionalLight(glm::vec3 direction, ThreeComponentColor light) {
		this->lightColors = light;
		this->direction = direction;
	}
	DirectionalLight() {};
	ThreeComponentColor lightColors;
	glm::vec3 direction;
};