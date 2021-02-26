#include "PointLight.h"

float PointLight::attenuationCoefficients[] = {
	1.0f, 0.7f, 1.8f,
	1.0f, 0.35f, 0.44f,
	1.0f, 0.22f, 0.20f,
	1.0f, 0.14f, 0.07f,
	1.0f, 0.09f, 0.032f,
	1.0f, 0.07f, 0.017f,
	1.0f, 0.045f, 0.0075f,
	1.0f, 0.027f, 0.0028f,
	1.0f, 0.022f, 0.0019f,
	1.0f, 0.014f, 0.0007f,
	1.0f, 0.007f, 0.0002f,
	1.0f, 0.0014f, 0.000007f
};

glm::vec3 PointLight::getAttenuation(unsigned int brightnessLevel) {
	if (brightnessLevel >= 12)
		return glm::vec3(0.0f);
	return glm::vec3(attenuationCoefficients[brightnessLevel * 3], attenuationCoefficients[brightnessLevel * 3 + 1], attenuationCoefficients[brightnessLevel * 3 + 2]);
}


