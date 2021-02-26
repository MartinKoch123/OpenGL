#include "KeyboardEvents.h"

KeyStates::KeyStates() {
	for (unsigned int i = 0; i < NUMBER_GLFW_KEYS; i++) {
		states[i] = GLFW_RELEASE;
	}
}

bool KeyboardEvents::isPressed(unsigned int key) {
	return states.states[key] == PRESSED;
}

bool KeyboardEvents::wasTapped(unsigned int key) {
	return lastStates.states[key] == RELEASED && states.states[key] == PRESSED;
}

void KeyboardEvents::update(KeyStates newStates) {
	lastStates = states;
	states = newStates;
}
