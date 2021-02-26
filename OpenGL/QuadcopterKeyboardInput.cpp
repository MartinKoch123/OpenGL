#include "QuadcopterKeyboardInput.h"

QuadrocopterInput QuadcopterKeyboardInput::getInput(KeyboardEvents* keyboardEvents, float deltaTime) {

	QuadrocopterInput input = QuadrocopterInput(0.0f, 0.0f, 0.0f, 0.0f);
	if (keyboardEvents->isPressed(GLFW_KEY_W))
		lastMainThrust = MAX_MAIN_THRUST;
	//lastMainThrust = limit(lastMainThrust + MAX_MAIN_THRUST / T_FULL_THRUST*deltaTime, 0.0f, MAX_MAIN_THRUST);
	else
		lastMainThrust = 0.5f * MAX_MAIN_THRUST;
		//lastMainThrust = limit(lastMainThrust - MAX_MAIN_THRUST / T_ZERO_THRUST*deltaTime, 0.0f, MAX_MAIN_THRUST);

	input.thrustLeftFront = lastMainThrust;
	input.thrustRightFront = lastMainThrust;
	input.thrustLeftRear = lastMainThrust;
	input.thrustRightRear = lastMainThrust;

	if (keyboardEvents->isPressed(GLFW_KEY_KP_4)) {
		input.thrustRightFront += MAX_PITCH_ROLL_THRUST;
		input.thrustRightRear += MAX_PITCH_ROLL_THRUST;
	}
	if (keyboardEvents->isPressed(GLFW_KEY_KP_6)) {
		input.thrustLeftFront += MAX_PITCH_ROLL_THRUST;
		input.thrustLeftRear += MAX_PITCH_ROLL_THRUST;
	}
	if (keyboardEvents->isPressed(GLFW_KEY_KP_8)) {
		input.thrustRightRear += MAX_PITCH_ROLL_THRUST;
		input.thrustLeftRear += MAX_PITCH_ROLL_THRUST;
	}
	if (keyboardEvents->isPressed(GLFW_KEY_KP_5)) {
		input.thrustRightFront += MAX_PITCH_ROLL_THRUST;
		input.thrustLeftFront += MAX_PITCH_ROLL_THRUST;
	}
	if (keyboardEvents->isPressed(GLFW_KEY_A)) {
		input.thrustLeftFront += MAX_YAW_THRUST;
		input.thrustRightRear += MAX_YAW_THRUST;
	}
	if (keyboardEvents->isPressed(GLFW_KEY_D)) {
		input.thrustRightFront += MAX_YAW_THRUST;
		input.thrustLeftRear += MAX_YAW_THRUST;
	}
	return input;
}


