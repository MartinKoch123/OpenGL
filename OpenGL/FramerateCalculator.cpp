#include "FramerateCalculator.h"

const float FramerateCalculator::ACTUALIZATION_PERIOD = 1.0f;
float FramerateCalculator::timeSinceActualization = 0.0f;
unsigned int FramerateCalculator::framesSinceActualization = 0;
float FramerateCalculator::rate = 0.0f;

void FramerateCalculator::newFrame(float deltaTime) {
	timeSinceActualization += deltaTime;
	framesSinceActualization++;
}

int FramerateCalculator::getRate() {
	if (timeSinceActualization > ACTUALIZATION_PERIOD) {
		rate = (float)framesSinceActualization / ACTUALIZATION_PERIOD;
		timeSinceActualization -= ACTUALIZATION_PERIOD;
		framesSinceActualization = 0;
	}
	return rate;
}

FramerateCalculator::FramerateCalculator() {
}


