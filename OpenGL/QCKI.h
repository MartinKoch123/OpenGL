#pragma once
#include "Tools.h"
#include "KeyboardInput.h"
#include "RigidBody.h"
#include "Quadrocopter.h"


class QuadcopterKeyboardInput2 : public KeyboardInput {
public:
	QuadcopterKeyboardInput2(GLFWwindow* window) : KeyboardInput(window) {};
	QuadcopterKeyboardInput2() {};
	QuadrocopterInput getInput(float deltaTime);
private:
	float MAX_PITCH_ROLL_THRUST = 1.0f;
	float MAX_MAIN_THRUST = 15.0f;
	float MAX_YAW_THRUST = 2.2f;
	float T_FULL_THRUST = 0.1f;
	float T_ZERO_THRUST = 1.0f;
	float lastMainThrust = 0.0f;
};

