#pragma once
#include "Scenario.h"
#include "Renderer.h"
#include "Track.h"
#include "SingleTrackKeyboardInput.h"
#include "SingleTrack.h"
#include "PhysicalVisualModel.h"
#include "ObjectGenerator.h"

class SingleTrackScenario : public Scenario{
public:
	SingleTrackScenario(Renderer* renderer, GLFWwindow* window, ObjectGenerator* generator);
	SingleTrackScenario() {};
	void onFrameChange(KeyboardEvents* keyboardEvents, float deltaTime);
	glm::mat4 getViewMatrix();
	glm::vec3 getCameraPosition();
	void mouseCallback(float xPos, float yPos);
protected:
	void onSimulationIteration();
private:
	void processInput(KeyboardEvents* keyboardEvents, float deltaTime);
	void processToggleCamera(KeyboardEvents* keyboardEvents);
	PhysicalVisualModel<SingleTrack, SingleTrackInput> singleTrack;
	SingleTrackKeyboardInput singleTrackKeyboardInput;
	SingleTrackInput singleTrackInput;
	Track trackRear;
	Track trackFront;
	HUDelement hudSingleTrackState;
	unsigned int cameraMode;
};

