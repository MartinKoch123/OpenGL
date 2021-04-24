#include "QuadcopterScenario.h"

using glm::vec3, std::unique_ptr, std::vector;

QuadcopterScenario::QuadcopterScenario(Renderer* renderer, ObjectGenerator* generator) :
		Scenario(renderer->getWidth(), renderer->getHeight()) {

	camera = Camera(-2.0f, 3.0f, 5.0f, 0.0f, 1.0f, 0.0f, -70.0f, 0.0f);
	freeCamera = FreeCamera(Vec3(0.0f, 1.0f, 0.0f), quaternion());

	// Light
	renderer->setDirectioalLight(DirectionalLight(glm::normalize(vec3(-0.4f, -0.4f, -0.4f)), ThreeComponentColor(0.3f)));

	// Terrain
	unique_ptr<HeightMap> heightMap = unique_ptr<HeightMap>(new HeightMap(200));
	TerrainTools::addPerlinNoise(heightMap.get(), 2, 30.0f);
	TerrainTools::addPerlinNoise(heightMap.get(), 8, 20.0f);
	TerrainTools::addPerlinNoise(heightMap.get(), 16, 10.0f);
	TerrainTools::addPerlinNoise(heightMap.get(), 64, 1.5f);
	Terrain terrain = Terrain(TERRAIN_SIZE, heightMap.get());
	renderer->addMultiBodyObject(generator->getTerrainObject(terrain));

	// Instancing Trees
	vector<ParticlesObject*> instancingTreeParts = generator->getInstancingTree(&terrain, NUMBER_TREES);
	vec3 offset = vec3();
	int index = 0;
	while (index < NUMBER_TREES){
		offset.x = randomFloat11() * TERRAIN_SIZE / 2.0f;
		offset.z = randomFloat11() * TERRAIN_SIZE / 2.0f;
		offset.y = terrain.height(offset.x, offset.z);
		for (auto particlesObject : instancingTreeParts)
			particlesObject->particlePositions[index] = offset;
		index++;
	}
	
	MultiBodyObject* treesMBO = new MultiBodyObject(vec3(0.0f), vec3(0.0f), vec3(1.0f));
	for (unsigned int j = 0; j < instancingTreeParts.size(); j++) 
		treesMBO->addBody(instancingTreeParts[j]);
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
	if (cameraMode == CameraMode::Copter) {
		freeCamera.position = quadcopter.physicalModel->getPosition() - 0.0f * quadcopter.physicalModel->getHeading();
		freeCamera.setOrientation(quadcopter.physicalModel->getOrientation());
	}
}

glm::mat4 QuadcopterScenario::getViewMatrix() {
	switch (cameraMode) {
	case CameraMode::Free:
		return camera.GetViewMatrix();
	case CameraMode::Copter:
		return freeCamera.GetViewMatrix(); }
	return glm::mat4();
}

vec3 QuadcopterScenario::getCameraPosition() {
	switch (cameraMode) {
	case CameraMode::Free:
		return camera.Position;
	case CameraMode::Copter:
		return freeCamera.position.toGLM(); }
	return vec3();
}

void QuadcopterScenario::mouseCallback(float xOffset, float yOffset) {
	camera.ProcessMouseMovement(xOffset, yOffset); }

void QuadcopterScenario::onSimulationIteration() {
	quadcopter.update(quadcopterInput, STEP_SIZE); }

void QuadcopterScenario::processInput(KeyboardEvents* keyboardEvents, float deltaTime) {
	processToggleCamera(keyboardEvents);
	if (cameraMode == CameraMode::Free)
		processCameraMovements(keyboardEvents, deltaTime);
}

void QuadcopterScenario::processToggleCamera(KeyboardEvents* keyboardEvents) {
	if (keyboardEvents->wasTapped(GLFW_KEY_K))
		cameraMode = cameraMode == CameraMode::Free ? CameraMode::Copter : CameraMode::Free;
}




