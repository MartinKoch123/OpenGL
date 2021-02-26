#pragma once
#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#include "Tools.h"

enum KEY_STATE {RELEASED, PRESSED};

class KeyStates {
public:
	KeyStates();
	unsigned int operator [](unsigned int i) const {
		if (i >= NUMBER_GLFW_KEYS)
			return 0;
		return states[i]; 
	}
	unsigned int states[NUMBER_GLFW_KEYS];
};

class KeyboardEvents {
public:
	bool isPressed(unsigned int key);
	bool wasTapped(unsigned int key);
	void update(KeyStates newStates);
private:
	KeyStates lastStates;
	KeyStates states;
};


