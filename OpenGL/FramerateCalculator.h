#pragma once
class FramerateCalculator {
public:
	static void newFrame(float deltaTime);
	static int getRate();
private:
	static const float ACTUALIZATION_PERIOD;
	static float timeSinceActualization;
	static unsigned int framesSinceActualization;
	static float rate;
	FramerateCalculator();
};

