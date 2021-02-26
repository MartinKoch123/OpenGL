#include "SingleTrackScenario.h"

SingleTrackScenario::SingleTrackScenario(Renderer* renderer, GLFWwindow* window, ObjectGenerator* generator) : 
	Scenario(renderer->getWidth(), renderer->getHeight()){

	camera = Camera(-2.0f, 3.0f, 5.0f, 0.0f, 1.0f, 0.0f, -70.0f, 0.0f);
	cameraMode = 0;

	// Directional Light
	renderer->setDirectioalLight(DirectionalLight(glm::normalize(glm::vec3(-0.4f, -1.0f, -0.4f)), ThreeComponentColor(0.3f)));

	// Unicolor objects
	renderer->addMultiBodyObject(
		new MultiBodyObject(
			new UnicolorObject(generator->cube, glm::vec3(0.5f), glm::vec3(0.0f), glm::vec3(1.0f, 1.0f, 2.0f), Material(Material::emerald)),
			glm::vec3(-2.0f, 0.0f, 2.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(1.0f)));
	renderer->addMultiBodyObject(
		new MultiBodyObject(
			new UnicolorObject(generator->cube, glm::vec3(0.5f), glm::vec3(0.0f), glm::vec3(1.1f, 1.3f, 2.5f), Material(Material::silver)),
			glm::vec3(22.0f, 0.0f, 8.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(1.0f)));
	renderer->addMultiBodyObject(
		new MultiBodyObject(
			new UnicolorObject(generator->cube, glm::vec3(0.5f), glm::vec3(0.0f), glm::vec3(2.0f, 2.0f, 4.0f), Material(Material::silver)),
			glm::vec3(24.0f, 0.0f, 28.0f), glm::vec3(0.0f, glm::radians(90.0f), 0.0f), glm::vec3(1.0f)));
	renderer->addMultiBodyObject(
		new MultiBodyObject(
			new UnicolorObject(generator->cube, glm::vec3(0.5f), glm::vec3(0.0f), glm::vec3(1.5f), Material(Material::red_plastic)),
			glm::vec3(-2.0f, 0.0f, -1.0f), glm::vec3(-90.0f, 0.0f, 0.0f), glm::vec3(1.0f)));
	renderer->addMultiBodyObject(
		new MultiBodyObject(
			new UnicolorObject(generator->cube, glm::vec3(0.5f), glm::vec3(0.0f), glm::vec3(1.0f), Material(Material::cyan_rubber)),
			glm::vec3(1.2f, 0.0f, -2.3f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.7f)));
	renderer->addMultiBodyObject(
		new MultiBodyObject(
			new UnicolorObject(generator->cube, glm::vec3(0.0f), glm::vec3(0.0f), glm::vec3(0.05f, 2.0f, 0.05f), Material(Material::black_plastic)),
			glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(1.0f)));
	renderer->addMultiBodyObject(
		new MultiBodyObject(
			new UnicolorObject(generator->cube, glm::vec3(0.0f), glm::vec3(0.0f), glm::vec3(0.05f, 2.0f, 0.05f), Material(Material::black_plastic)),
			glm::vec3(5.0f, 0.0f, 5.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(1.0f)));


	renderer->addMultiBodyObject(
		new MultiBodyObject(
			new UnicolorObject(generator->cylinder, glm::vec3(0.0f), glm::vec3(0.0f), glm::vec3(1.0f, 5.0f, 1.0f), Material(Material::chrome)),
			glm::vec3(2.0f, 0.0f, 5.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(1.0f)));

	renderer->addMultiBodyObject(
		new MultiBodyObject(
			new UnicolorObject(generator->cylinder, glm::vec3(0.0f), glm::vec3(0.0f), glm::vec3(0.7f, 2.0f, 1.0f), Material(Material::cyan_plastic)),
			glm::vec3(-3.0f, 0.0f, 6.0f), glm::vec3(0.0f, glm::radians(70.0f), glm::radians(90.0f)), glm::vec3(1.0f)));

	renderer->addMultiBodyObject(
		new MultiBodyObject(
			new UnicolorObject(generator->cylinder, glm::vec3(0.0f), glm::vec3(0.0f), glm::vec3(2.0f, 7.2f, 1.1f), Material(Material::black_rubber)),
			glm::vec3(7.0f, 0.3f, 13.0f), glm::vec3(0.0f, 0.0f, glm::radians(90.0f)), glm::vec3(0.5f)));

	renderer->addMultiBodyObject(
		new MultiBodyObject(
			new UnicolorObject(generator->sphere, glm::vec3(0.0f), glm::vec3(0.0f), glm::vec3(1.0f), Material(Material::cyan_rubber)),
			glm::vec3(4.0f, 1.0f, 8.0f), glm::vec3(0.0f), glm::vec3(1.0f)));

	MultiBodyObject* pyramids = new MultiBodyObject(glm::vec3(13.0f, 0.0f, -20.0f), glm::vec3(0.0f), glm::vec3(2.0f, 3.0f, 2.0f));
	pyramids->addBody(new UnicolorObject(generator->pyramid4, glm::vec3(0.0f), glm::vec3(0.0f), glm::vec3(1.0f), Material(Material::jade)));
	pyramids->addBody(new UnicolorObject(generator->pyramid4, glm::vec3(-2.0f, 0.0f, 0.0f), glm::vec3(0.0f, glm::radians(20.0f), 0.0f), glm::vec3(1.0f), Material(Material::jade)));
	pyramids->addBody(new UnicolorObject(generator->pyramid4, glm::vec3(-4.0f, 0.0f, 0.0f), glm::vec3(0.0f, glm::radians(40.0f), 0.0f), glm::vec3(1.0f), Material(Material::jade)));
	pyramids->addBody(new UnicolorObject(generator->pyramid4, glm::vec3(-6.0f, 0.0f, 0.0f), glm::vec3(0.0f, glm::radians(60.0f), 0.0f), glm::vec3(1.0f), Material(Material::jade)));
	pyramids->addBody(new UnicolorObject(generator->pyramid4, glm::vec3(-8.0f, 0.0f, 0.0f), glm::vec3(0.0f, glm::radians(80.0f), 0.0f), glm::vec3(1.0f), Material(Material::jade)));
	pyramids->addBody(new UnicolorObject(generator->pyramid4, glm::vec3(-10.0f, 0.0f, 0.0f), glm::vec3(0.0f, glm::radians(100.0f), 0.0f), glm::vec3(1.0f), Material(Material::jade)));
	renderer->addMultiBodyObject(pyramids);

	renderer->addMultiBodyObject(
		new MultiBodyObject(
			new UnicolorObject(generator->pyramid4, glm::vec3(0.0f), glm::vec3(0.0f), glm::vec3(20.0f), Material(Material::white_rubber)),
			glm::vec3(-50.0f, 0.0f, -40.0f), glm::vec3(0.0f), glm::vec3(1.0f)));

	renderer->addMultiBodyObject(
		new MultiBodyObject(
			new UnicolorObject(generator->cone, glm::vec3(0.0f), glm::vec3(0.0f), glm::vec3(1.0f), Material(Material::green_rubber)),
			glm::vec3(-18.0f, 0.0f, 8.5), glm::vec3(0.0f), glm::vec3(3.0f)));

	// Light Sources
	//LightSourceObject* sunCube0 = new LightSourceObject(generator->sphere, glm::vec3(0.0f), glm::vec3(0.0f), glm::vec3(1.0f), glm::vec3(0.0f, 0.0f, 0.7f));
	//LightSourceObject* sunCube1 = new LightSourceObject(generator->sphere, glm::vec3(0.0f), glm::vec3(0.0f), glm::vec3(1.0f), glm::vec3(1.0f));

	//MultiBodyObject* sun0 = new MultiBodyObject(
	//	sunCube0,
	//	new PointLight(sunCube0->position, ThreeComponentColor(glm::vec3(0.0f, 0.0f, 0.2f), glm::vec3(0.0f, 0.0f, 0.6f), glm::vec3(0.0f, 0.0f, 1.0f)), 1),
	//	glm::vec3(1.3f, 1.5f, -1.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.1f));
	//MultiBodyObject* sun1 = new MultiBodyObject(
	//	sunCube1,
	//	new PointLight(sunCube1->position, ThreeComponentColor(glm::vec3(0.2f), glm::vec3(0.6f), glm::vec3(1.0f)), 7),
	//	glm::vec3(-2.0f, 7.0f, 1.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.2f));
	//MultiBodyObject* sun2 = new MultiBodyObject(
	//	sunCube1,
	//	new PointLight(sunCube1->position, ThreeComponentColor(glm::vec3(0.2f), glm::vec3(0.6f), glm::vec3(1.0f)), 7),
	//	glm::vec3(20.0f, 7.0f, 30.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.2f));


	//renderer->addMultiBodyObject(sun0);
	//renderer->addMultiBodyObject(sun1);
	//renderer->addMultiBodyObject(sun2);

	//// Texture objects
	//TextureMesh* boxMesh = new TextureMesh(MeshDataGenerator::textureCube(), generator->boxTexture, generator->defaultTexture_specular);
	//renderer->addMultiBodyObject(
	//	new MultiBodyObject(
	//		new TextureObject(boxMesh, glm::vec3(0.5f), glm::vec3(0.0f), glm::vec3(1.0f), 0.1f),
	//		glm::vec3(2.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(1.0f)));

	//TextureMesh* woodSteelBoxMesh = new TextureMesh(MeshDataGenerator::textureCube(), generator->woodSteelBoxTexture, generator->woodSteelBoxTexture_specular);
	//renderer->addMultiBodyObject(
	//	new MultiBodyObject(
	//		new TextureObject(woodSteelBoxMesh, glm::vec3(0.5f), glm::vec3(0.0f), glm::vec3(1.0f), 0.2f),
	//		glm::vec3(0.0f, 0.0f, -1.7f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.8f)));


	//// Ground
	//renderer->addMultiBodyObject(
	//	new MultiBodyObject(
	//		new MaterialMeshObject(generator->greenRubberSquare, glm::vec3(0.0f), glm::vec3(0.0f), glm::vec3(1.0f)),
	//		glm::vec3(0.0f), glm::vec3(glm::radians(-90.0f), 0.0f, 0.0f), glm::vec3(1000.0f)));

	renderer->addMultiBodyObject(
		new MultiBodyObject(
			new UnicolorObject(generator->square, glm::vec3(0.0f), glm::vec3(0.0f), glm::vec3(1.0f), Material(Material::green_rubber)),
			glm::vec3(0.0f), glm::vec3(glm::radians(-90.0f), 0.0f, 0.0f), glm::vec3(1000.0f)));



	// Singletrack
	MultiBodyObject* carModel = generator->createCar(glm::vec3(0.0f));
	renderer->addMultiBodyObject(carModel);
	SingleTrack* car = new SingleTrack(0, 0, 0);
	singleTrack = PhysicalVisualModel<SingleTrack, SingleTrackInput>(car, carModel);

	singleTrackKeyboardInput = SingleTrackKeyboardInput();

	trackRear = Track(generator->square, glm::vec2(0.0f));
	renderer->addMultiBodyObject(trackRear.getTrackObject());
	trackFront = Track(generator->square, glm::vec2(0.0f));
	renderer->addMultiBodyObject(trackFront.getTrackObject());

	// Hud
	hudSingleTrackState = HUDelement(0.4f, 0.9f, 0.4f, Vec3(1.0f), 2);
	hud.addElement(&hudSingleTrackState);
}

void SingleTrackScenario::onFrameChange(KeyboardEvents* keyboardEvents, float deltaTime) {

	Scenario::onFrameChange(keyboardEvents, deltaTime);

	singleTrackInput = singleTrackKeyboardInput.getInput(keyboardEvents);
	processInput(keyboardEvents, deltaTime);

	if (cameraMode == 1) {
		camera.Position = glm::vec3(singleTrack.physicalModel->x, 2.5f, -singleTrack.physicalModel->z) - 7.0f * singleTrack.physicalModel->getHeading().toGLM();
		camera.setAngles(glm::radians(-15.0f), -singleTrack.physicalModel->getBeta());
	}

	trackRear.addPosition(singleTrack.physicalModel->rearWheel.getPosition().toGLM());
	trackFront.addPosition(singleTrack.physicalModel->frontWheel.getPosition().toGLM());

	hudSingleTrackState.lines[0] = "Speed: " + to_string_with_precision(singleTrack.physicalModel->getAbsoluteVelocity(), 2);
	hudSingleTrackState.lines[1] = "Gear: " + to_string_with_precision(singleTrack.physicalModel->getGear(), 0);
}

glm::mat4 SingleTrackScenario::getViewMatrix() {
	return camera.GetViewMatrix();
}

glm::vec3 SingleTrackScenario::getCameraPosition() {
	return camera.Position;
}

void SingleTrackScenario::mouseCallback(float xOffset, float yOffset) {
	camera.ProcessMouseMovement(xOffset, yOffset);
}

void SingleTrackScenario::onSimulationIteration() {
	singleTrack.update(singleTrackInput, STEP_SIZE);
	singleTrack.visualModel->getBody(1)->orientation = quaternion(glm::radians(90.0f), singleTrackInput.delta, 0.0f);
	singleTrack.visualModel->getBody(1)->updateModelMatrix();
}

void SingleTrackScenario::processInput(KeyboardEvents* keyboardEvents, float deltaTime) {
	processToggleCamera(keyboardEvents);
	if (cameraMode != 0)
		return;
	processCameraMovements(keyboardEvents, deltaTime);
}

void SingleTrackScenario::processToggleCamera(KeyboardEvents* keyboardEvents) {
	if (keyboardEvents->wasTapped(GLFW_KEY_K)) {
		if (cameraMode == 1)
			cameraMode = 0;
		else
			cameraMode++;
	}
}





