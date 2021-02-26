#include "SingleTrackKeyboardInput.h"

SingleTrackInput SingleTrackKeyboardInput::getInput(KeyboardEvents *keyboardEvents) {
	SingleTrackInput input = SingleTrackInput();
	if (keyboardEvents->isPressed(GLFW_KEY_UP))
		input.phiVar = 1.0f;
	if (keyboardEvents->isPressed(GLFW_KEY_DOWN))
		input.Fb = 15000.0f;
	if (keyboardEvents->isPressed(GLFW_KEY_SPACE)) {
		input.Fb = 15000.0f;
		input.xi = 1.0f;
	}
	if (keyboardEvents->isPressed(GLFW_KEY_LEFT)) {
		input.delta += 0.53f;
	}
	if (keyboardEvents->isPressed(GLFW_KEY_RIGHT)) {
		input.delta -= 0.53f;
	}
	
	if (keyboardEvents->wasTapped(GLFW_KEY_LEFT_SHIFT) && G < 5)
		G++;
	if (keyboardEvents->wasTapped(GLFW_KEY_LEFT_CONTROL) && G > 1)
		G--;
	input.G = G;
	
	return input;
}



