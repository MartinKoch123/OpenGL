#pragma once
#include "KeyboardEvents.h"
#include "Vehicle.h"

class SingleTrackKeyboardInput{
public:
	SingleTrackKeyboardInput() : G(1) {};
	SingleTrackInput getInput(KeyboardEvents *keyboardEvents);
private:
	unsigned int G;
};

