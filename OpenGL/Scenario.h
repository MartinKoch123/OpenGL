#pragma once
#include "KeyboardEvents.h"
#include "Camera.h"
#include "FreeCamera.h"
#include "FramerateCalculator.h"
#include "HUD.h"

class Scenario {
public:
	Scenario() {};
	Scenario(unsigned int screenWidth, unsigned int screenHeight);

	virtual void onFrameChange(KeyboardEvents* keyboardEvents, float deltaTime);
	virtual glm::mat4 getViewMatrix() = 0;
	virtual glm::vec3 getCameraPosition() = 0;
	virtual void mouseCallback(float xPos, float yPos);
	virtual void restart();
protected:
	void simulationLoop(float deltaTime);
	virtual void onSimulationIteration() = 0;
	virtual void processCameraMovements(KeyboardEvents* keyboardEvents, float deltaTime);
	Camera camera;
	float STEP_SIZE = 0.01f;
	const float T_INI = 3.0f;
	HUD hud;
	unsigned int screenWidth, screenHeight;
private:
	float unsimulatedTime;
	float iniTime;
	HUDelement hudCameraPosition;
	HUDelement hudFrameRate;

	
};

