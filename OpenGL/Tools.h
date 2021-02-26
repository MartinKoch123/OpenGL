#pragma once
#include <glm\glm.hpp>
#include <string>
#include <iostream>
#include <sstream>
#include <iomanip>
#include <glad/glad.h>
#include <random>


const unsigned int NUMBER_GLFW_KEYS = 348;
const float PI = 3.14159265359f;
const unsigned int SCREEN_WIDTH = 1700;
const unsigned int SCREEN_HEIGHT = 900;
const unsigned int SHADOW_MAP_RESOLUTION = 4096;
const float SHADOW_MAP_SIZE = 200.0f;
const float RENDER_DISTANCE = 200.0f;
const float SHADOW_MAPPING_NEAR_PLANE = 0.0f;
const float SHADOW_MAPPING_FAR_PLANE = 70.0f;
const float GRAVITY = 9.81f;
const float DENSITY_AIR = 1.20f;
const std::string FILE_FONT_VERTEX_SHADER = "shaders/fontVS.txt";
const std::string FILE_FONT_FRAGMENT_SHADER = "shaders/fontFS.txt";



int randomInt(int min, int max);

int randomInt(int max);

int randomInt();

float randomFloat();

float randomFloat11();

float randomFloatNonZero11();

float randomGauﬂ(float mean, float deviation);

glm::vec3 normalOfTriangle(glm::vec3 vertex1, glm::vec3 vertex2, glm::vec3 vertex3);

float limit(float value, float lowerBound, float upperBound);

template <typename physicalModelType>
std::string to_string_with_precision(const physicalModelType a_value, const int n = 6) {
	std::ostringstream out;
	out << std::setprecision(n) << a_value;
	return out.str();
}

float sign(float value);
