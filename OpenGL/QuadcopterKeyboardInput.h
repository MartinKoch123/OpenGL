#pragma once
#include "Tools.h"
#include "KeyboardEvents.h"
#include "Quadrocopter.h"


class QuadcopterKeyboardInput {
public:
	QuadcopterKeyboardInput() {};
	QuadrocopterInput getInput(KeyboardEvents* keyboardEvents,  float deltaTime);
private:
	
	float MAX_PITCH_ROLL_THRUST = 1.0f;
	float MAX_MAIN_THRUST = 15.0f;
	float MAX_YAW_THRUST = 2.2f;
	float T_FULL_THRUST = 0.1f;
	float T_ZERO_THRUST = 1.0f;
	float lastMainThrust = 0.0f;
};
