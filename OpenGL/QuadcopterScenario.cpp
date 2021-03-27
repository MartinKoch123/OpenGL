#include "QuadcopterScenario.h"

QuadcopterScenario::QuadcopterScenario(Renderer* renderer, ObjectGenerator* generator) :
	Scenario(renderer->getWidth(), renderer->getHeight()) {

	camera = Camera(-2.0f, 3.0f, 5.0f, 0.0f, 1.0f, 0.0f, -70.0f, 0.0f);
	freeCamera = FreeCamera(Vec3(0.0f, 1.0f, 0.0f), quaternion());
	cameraMode = 1;

	// Directional Light
	renderer->setDirectioalLight(DirectionalLight(glm::normalize(glm::vec3(-0.4f, -0.4f, -0.4f)), ThreeComponentColor(0.3f)));

	// Terrain
	float terrainSize = 400;
	HeightMap<200>* heightMap = new HeightMap<200>();
	TerrainTools::addPerlinNoise(heightMap, 2, 30.0f);
	TerrainTools::addPerlinNoise(heightMap, 8, 20.0f);
	TerrainTools::addPerlinNoise(heightMap, 16, 10.0f);
	TerrainTools::addPerlinNoise(heightMap, 64, 1.5f);
	Terrain* terrain = new Terrain(terrainSize, heightMap);
	renderer->addMultiBodyObject(generator->getTerrainObject(terrain));

	// Trees
	/*for (unsigned int i = 0; i < 10; i++) {
		renderer->addMultiBodyObject(generator->createTree(terrain, randomFloat()*10.0f, 30.0f + randomFloat()*10.0f));
	}

	renderer->addMultiBodyObject(generator->createTree(terrain, randomFloat()*10.0f, 30.0f + randomFloat()*10.0f));*/

	

	// Instancing Trees
	unsigned int numberTrees = 500;
	std::vector<ParticlesObject*> instancingTreeParts = generator->getInstancingTree(terrain, numberTrees);
	HeightMap<50>* noiseMap = new HeightMap<50>();
	TerrainTools::addPerlinNoise(noiseMap, 3, 1.0f);
	Terrain treeDensity = Terrain(terrainSize, noiseMap);

	unsigned int index = 0;
	glm::vec3 offset;

	while (index < numberTrees){
		
		float randX = randomFloat11() * terrainSize / 2.0f;
		float randY = randomFloat11() * terrainSize / 2.0f;

		//if (randomFloat() + treeDensity.getHeight(randX, randY) < 1.0f)
			//continue;

		offset.x = randX;
		offset.z = randY;
		offset.y = terrain->getHeight(offset.x, offset.z);
		for (unsigned int j = 0; j < instancingTreeParts.size(); j++) {
			instancingTreeParts[j]->particlePositions[index] = offset;
		}
		index++;
	}


	
	MultiBodyObject* treesMBO = new MultiBodyObject(glm::vec3(0.0f), glm::vec3(0.0f), glm::vec3(1.0f));
	for (unsigned int j = 0; j < instancingTreeParts.size(); j++) {
		treesMBO->addBody(instancingTreeParts[j]);
	}
	renderer->addMultiBodyObject(treesMBO);


	// Quadcopter
	Quadrocopter* quadcopterModel = new Quadrocopter();
	quadcopterModel->setPosition(Vec3(0.0f, 10.0f, -2.0f));
	quadcopterModel->setVelocity(TransRotPair(Vec3(0.0f, 5.0f, 0.0f), Vec3(0.0f, 0.0f, 0.0f)));

	MultiBodyObject* quadcopterObject = generator->getQuadrocopter();
	renderer->addMultiBodyObject(quadcopterObject);

	quadcopter = PhysicalVisualModel<Quadrocopter, QuadrocopterInput>(quadcopterModel, quadcopterObject);

	quadcopterKeyboardInput = QuadcopterKeyboardInput();
}

void QuadcopterScenario::onFrameChange(KeyboardEvents* keyboardEvents, float deltaTime) {

	Scenario::onFrameChange(keyboardEvents, deltaTime);

	quadcopterInput = quadcopterKeyboardInput.getInput(keyboardEvents, deltaTime);
	processInput(keyboardEvents, deltaTime);

	if (cameraMode == 1) {
		freeCamera.position = quadcopter.physicalModel->getPosition() - 0.0f * quadcopter.physicalModel->getHeading();
		freeCamera.setOrientation(quadcopter.physicalModel->getOrientation());
	}
}

glm::mat4 QuadcopterScenario::getViewMatrix() {
	switch (cameraMode) {
	case 0:
		return camera.GetViewMatrix();
	case 1:
		return freeCamera.GetViewMatrix();
	}
	return glm::mat4();
}

glm::vec3 QuadcopterScenario::getCameraPosition() {
	switch (cameraMode) {
	case 0:
		return camera.Position;
	case 1:
		return freeCamera.position.toGLM();
	}
	return glm::vec3();
}

void QuadcopterScenario::mouseCallback(float xOffset, float yOffset) {
	camera.ProcessMouseMovement(xOffset, yOffset);
}

void QuadcopterScenario::onSimulationIteration() {
	quadcopter.update(quadcopterInput, STEP_SIZE);
}

void QuadcopterScenario::processInput(KeyboardEvents* keyboardEvents, float deltaTime) {
	processToggleCamera(keyboardEvents);
	if (cameraMode != 0)
		return;
	processCameraMovements(keyboardEvents, deltaTime);

}

void QuadcopterScenario::processToggleCamera(KeyboardEvents* keyboardEvents) {
	if (keyboardEvents->wasTapped(GLFW_KEY_K)){
		if (cameraMode == 1)
			cameraMode = 0;
		else
			cameraMode++;
	}
}




