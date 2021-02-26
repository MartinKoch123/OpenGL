#include "CopterControlScenario.h"



CopterControlScenario::CopterControlScenario(Renderer * renderer, ObjectGenerator * generator) : 
	Scenario(renderer->getWidth(), renderer->getHeight()) {

	renderer->setDirectioalLight(DirectionalLight(glm::vec3(-1.0f), ThreeComponentColor(0.5f)));

	camera = Camera(0.0f, 1.0f, 3.0f, 0.0f, 1.0f, 0.0f, glm::radians(-90.0f), 0.0f);
	
	// Terrain
	float terrainSize = 100;
	HeightMap<200>* heightMap = new HeightMap<200>();
	TerrainTools::addPerlinNoise(heightMap, 32, 0.5f);
	Terrain* terrain = new Terrain(terrainSize, heightMap);
	renderer->addMultiBodyObject(generator->getTerrainObject(terrain));


	// Copter
	MultiBodyObject* copterObject = generator->getQuadrocopter();
	Quadrocopter* copterModel = new Quadrocopter();
	copterModel->setPosition(Vec3(0.0f, 1.0f, 0.0f));
	copterObject->position = copterModel->getPosition().toGLM();
	renderer->addMultiBodyObject(copterObject);

	copter = PhysicalVisualModel<Quadrocopter, QuadrocopterInput>(copterModel, copterObject);

	controller = new QCC_Height_PD();

	// Hud
	hudCopterState = HUDelement(0.4f, 0.9f, 0.4f, Vec3(1.0f), 3);
	hud.addElement(&hudCopterState);

	restart();
}

void CopterControlScenario::restart() {
	Scenario::restart();
	copter.setPose(Vec3(0.0f, 1.0f, 0.0f), quaternion());
	copter.physicalModel->setVelocity(TransRotPair(Vec3(0.0f), Vec3(0.0f)));
}

void CopterControlScenario::onFrameChange(KeyboardEvents * keyboardEvents, float deltaTime) {

	processCameraMovements(keyboardEvents, deltaTime);

	hudCopterState.lines[0] = to_string_with_precision(copter.physicalModel->getPosition().x(), 3);
	hudCopterState.lines[1] = to_string_with_precision(copter.physicalModel->getPosition().y(), 3);
	hudCopterState.lines[2] = to_string_with_precision(copter.physicalModel->getPosition().z(), 3);

	if (keyboardEvents->wasTapped(GLFW_KEY_1))
		controller = new QCC_Height_PD();
	else if (keyboardEvents->wasTapped(GLFW_KEY_2))
		controller = new QCC_Height_PID();
	
	Scenario::onFrameChange(keyboardEvents, deltaTime);
}

glm::mat4 CopterControlScenario::getViewMatrix() {
	return camera.GetViewMatrix();
}

glm::vec3 CopterControlScenario::getCameraPosition() {
	return camera.Position;
}



void CopterControlScenario::onSimulationIteration() {
	QuadrocopterInput input = controller->getInput(copter.physicalModel->getPosition(), Vec4(), copter.physicalModel->getVelocity(), STEP_SIZE);
	copter.update(input, STEP_SIZE);
}

void CopterControlScenario::mouseCallback(float xOffset, float yOffset) {
	camera.ProcessMouseMovement(xOffset, yOffset);
}
