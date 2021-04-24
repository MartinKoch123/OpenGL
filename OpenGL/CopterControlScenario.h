#pragma once
#include "Scenario.h"
#include "Quadrocopter.h"
#include "Renderer.h"
#include "ObjectGenerator.h"
#include "PhysicalVisualModel.h"
#include "TerrainTools.h"
#include "QuadcopterController.h"

class CopterControlScenario : public Scenario{
public:
	CopterControlScenario(Renderer* renderer, ObjectGenerator* generator);
	CopterControlScenario() {};
	void onFrameChange(KeyboardEvents* keyboardEvents, float deltaTime);
	glm::mat4 getViewMatrix();
	glm::vec3 getCameraPosition();
	void restart();
protected:
	void onSimulationIteration();
	void mouseCallback(float xOffset, float yOffset);
private:
	static constexpr float TERRAIN_SIZE = 100;
	PhysicalVisualModel<Quadrocopter, QuadrocopterInput> copter;
	QuadrocopterInput copterInput;
	QuadcopterController* controller{ nullptr };
	HUDelement hudCopterState;	
};

