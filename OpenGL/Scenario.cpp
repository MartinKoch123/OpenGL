#include "Scenario.h"

Scenario::Scenario(unsigned int screenWidth, unsigned int screenHeight) {
	this->screenWidth = screenWidth;
	this->screenHeight = screenHeight;
	camera = Camera(0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f);
	hud = HUD(screenWidth, screenHeight);
	hudCameraPosition = HUDelement(0.03f, 0.9f, 0.4f, Vec3(1.0f), 3);
	hud.addElement(&hudCameraPosition);
	hudFrameRate = HUDelement(0.01f, 0.05f, 0.5f, Vec3(1.0f), 1);
	hud.addElement(&hudFrameRate);
	restart();
}

void Scenario::onFrameChange(KeyboardEvents * keyboardEvents, float deltaTime) {
	simulationLoop(deltaTime);
	hudCameraPosition.lines[0] = to_string_with_precision(camera.Position.x, 2);
	hudCameraPosition.lines[1] = to_string_with_precision(camera.Position.y, 2);
	hudCameraPosition.lines[2] = to_string_with_precision(camera.Position.z, 2);
	FramerateCalculator::newFrame(deltaTime);
	hudFrameRate.lines[0] = to_string_with_precision(FramerateCalculator::getRate(), 1);
	hud.draw();
}

void Scenario::mouseCallback(float xPos, float yPos) {
}

void Scenario::restart() {
	unsimulatedTime = 0.0f;
	iniTime = 0.0f;
}

void Scenario::simulationLoop(float deltaTime) {
	if (iniTime < T_INI) {
		iniTime += deltaTime;
		return;
	}

	unsimulatedTime += deltaTime;
	while (unsimulatedTime > STEP_SIZE){
		onSimulationIteration();
		unsimulatedTime -= STEP_SIZE;
	}
}

void Scenario::processCameraMovements(KeyboardEvents* keyboardEvents, float deltaTime) {
	if (keyboardEvents->isPressed(GLFW_KEY_W))
		camera.ProcessKeyboard(FORWARD, deltaTime);
	if (keyboardEvents->isPressed(GLFW_KEY_S))
		camera.ProcessKeyboard(BACKWARD, deltaTime);
	if (keyboardEvents->isPressed(GLFW_KEY_A))
		camera.ProcessKeyboard(LEFT, deltaTime);
	if (keyboardEvents->isPressed(GLFW_KEY_D))
		camera.ProcessKeyboard(RIGHT, deltaTime);
}


