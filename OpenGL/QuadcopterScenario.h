#pragma once
#include "Texture.h"
#include "Object.h"
#include "Renderer.h"
#include "MeshDataGenerator.h"
#include "Mesh.h"
#include "PointLight.h"
#include "MultiBodyObject.h"
#include "Terrain.h"
#include "TerrainTools.h"
#include "ObjectGenerator.h"
#include <random>
#include "PhysicalVisualModel.h"
#include "Quadrocopter.h"
#include <GLFW\glfw3.h>
#include "QuadcopterKeyboardInput.h"
#include "Track.h"
#include "Camera.h"
#include "FreeCamera.h"
#include "FramerateCalculator.h"
#include "HUD.h"
#include "Scenario.h"
#include "TerrainTools.h"
#include "Terrain.h"

class QuadcopterScenario : public Scenario {
public:
	QuadcopterScenario(Renderer* renderer, ObjectGenerator* generator);
	QuadcopterScenario() {};
	void onFrameChange(KeyboardEvents* keyboardEvents, float deltaTime);
	glm::mat4 getViewMatrix();
	glm::vec3 getCameraPosition();
	void mouseCallback(float xPos, float yPos);
protected:
	void onSimulationIteration();
private:
	static constexpr float TERRAIN_SIZE = 400;
	static constexpr unsigned int NUMBER_TREES = 500;
	void processInput(KeyboardEvents* keyboardEvents, float deltaTime);
	void processToggleCamera(KeyboardEvents* keyboardEvents);
	PhysicalVisualModel<Quadrocopter, QuadrocopterInput> quadcopter;
	QuadcopterKeyboardInput quadcopterKeyboardInput;
	QuadrocopterInput quadcopterInput;
	FreeCamera freeCamera;
	enum class CameraMode { Free, Copter};
	CameraMode cameraMode = CameraMode::Copter;
};

