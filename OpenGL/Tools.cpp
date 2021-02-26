#include "Tools.h"

std::default_random_engine generator;

int randomInt(int min, int max) {
	return rand() % (max - min) + min;
}

int randomInt(int max) {
	return randomInt(0, max);
}

int randomInt() {
	return randomInt(0, 100);
}

float randomFloat() {
	return (float)randomInt(0, RAND_MAX) / RAND_MAX;
}

float randomFloat11() {
	return 2.0f * (randomFloat() - 0.5f);
}

float randomFloatNonZero11() {
	float x = randomFloat11();
	if (x == 0)
		x = 0.0000001f;
	return x;
}

float randomGauﬂ(float mean, float deviation) {
	std::normal_distribution<float> distribution(mean, deviation);
	return distribution(generator);
}

glm::vec3 normalOfTriangle(glm::vec3 vertex1, glm::vec3 vertex2, glm::vec3 vertex3) {
	return glm::normalize(glm::cross(vertex2 - vertex1, vertex3 - vertex2));
}

float limit(float value, float lowerBound, float upperBound) {
	if (value < lowerBound)
		return lowerBound;
	if (value > upperBound)
		return upperBound;
	return value;
}

float sign(float value) {
	if (value == 0.0f)
		return 0.0f;
	return value > 0 ? 1.0f : -1.0f;
}
