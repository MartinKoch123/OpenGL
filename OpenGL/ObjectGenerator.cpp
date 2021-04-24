#include "ObjectGenerator.h"

using glm::vec3, std::vector;

ObjectGenerator::ObjectGenerator() {
	boxTexture = new Texture("container.jpg");
	grassTexture = new Texture("grass.jpg");
	woodSteelBoxTexture = new Texture("woodSteelContainer.png");
	woodSteelBoxTexture_specular = new Texture("woodSteelContainer_specular.png");
	defaultTexture_specular = new Texture("default_specular.png");
	square = new Mesh<Vertex>(MeshDataGenerator::square());
	cube = new Mesh<Vertex>(MeshDataGenerator::cube());
	sphere = new Mesh<Vertex>(MeshDataGenerator::sphere(50));
	cylinder = new Mesh<Vertex>(MeshDataGenerator::cylinder(1.0f, 100));
	cylinder5 = new Mesh<Vertex>(MeshDataGenerator::cylinder(1.0f, 5));
	pyramid4 = new Mesh<Vertex>(MeshDataGenerator::pyramid(4));
	pyramid10 = new Mesh<Vertex>(MeshDataGenerator::pyramid(10));
	cone = new Mesh<Vertex>(MeshDataGenerator::pyramid(200));
	blackRubberSquare = new MaterialMesh(MeshDataGenerator::toMaterialVertex(MeshDataGenerator::square(), Material::black_rubber));
	greenRubberSquare = new MaterialMesh(MeshDataGenerator::toMaterialVertex(MeshDataGenerator::square(), Material::green_rubber));
}


MultiBodyObject * ObjectGenerator::createCar(vec3 position) {
	UnicolorObject* mainBody = new UnicolorObject(cube, vec3(0.0f, 0.3f, 0.0f), vec3(0.0f), vec3(2.56f, 0.2f, 0.2f), Material(Material::black_plastic));
	UnicolorObject* frontWheel = new UnicolorObject(cylinder, vec3(1.19f, 0.3f, 0.0f), vec3(glm::radians(90.0f), 0.0f, 0.0f), vec3(0.3f, 0.6f, 0.3f), Material(Material::ruby));
	UnicolorObject* backWheel = new UnicolorObject(cylinder, vec3(-1.37f, 0.3f, 0.0f), vec3(glm::radians(90.0f), 0.0f, 0.0f), vec3(0.3f, 0.6f, 0.3f), Material(Material::ruby));

	MultiBodyObject* car = new MultiBodyObject(position, vec3(0.0f), vec3(1.0f));
	car->addBody(mainBody);
	car->addBody(frontWheel);
	car->addBody(backWheel);

	return car;
}

MultiBodyObject * ObjectGenerator::createTree(Terrain* terrain, float x, float z) {

	vec3 brown = vec3(0.54f, 0.27f, 0.07f);
	Material leaves = Material(Material::pine_tree);
	leaves.specular = vec3(0.0f);
	vec3 position = vec3(x, terrain->height(x, z) - 0.1f, z);

	float trunkHeight = 0.8f + (randomFloat() - 0.5f)*0.4f;
	float trunkRadius = 0.2f + (randomFloat() - 0.5f)*0.04f;
	float branchesHeightBot = 0.8f + (randomFloat() - 0.5f)*0.2f;
	float branchesHeightMid = 0.7f + (randomFloat() - 0.5f)*0.2f;
	float branchesScaling = 1.0f + (randomFloat() - 0.5f)*0.2f;

	MultiBodyObject* tree = new MultiBodyObject(position, vec3(0.0f), vec3(1.0f));
	tree->addBody(new UnicolorObject(cylinder, vec3(0.0f, trunkHeight / 2, 0.0f), vec3(0.0f), TREE_SIZE * vec3(trunkRadius, trunkHeight, trunkRadius), Material(0.2f*brown, 0.7f*brown, 0.1f*brown, 0.05f)));
	tree->addBody(new UnicolorObject(pyramid10, vec3(0.0f, trunkHeight, 0.0f), vec3(0.0f), TREE_SIZE* branchesScaling*vec3(1.0f, 2.0f, 1.0f), leaves));
	tree->addBody(new UnicolorObject(pyramid10, vec3(0.0f, trunkHeight + branchesHeightBot, 0.0f), vec3(0.0f), TREE_SIZE * branchesScaling*vec3(0.8f, 1.6f, 0.8f), leaves));
	tree->addBody(new UnicolorObject(pyramid10, vec3(0.0f, trunkHeight + branchesHeightBot + branchesHeightMid, 0.0f), vec3(0.0f), TREE_SIZE * branchesScaling*vec3(0.6f, 1.2f, 0.6f), leaves));
	return tree;
}

std::vector<ParticlesObject*> ObjectGenerator::getInstancingTree(Terrain* terrain, unsigned int numberTrees) {
	vec3 brown = vec3(0.54f, 0.27f, 0.07f);
	Material leaves = Material(Material::pine_tree);
	leaves.specular = vec3(0.0f);

	float trunkHeight = 0.8f;
	float trunkRadius = 0.2f;
	float branchesHeightBot = 0.8f;
	float branchesHeightMid = 0.7f;
	float branchesScaling = 1.0f;

	std::vector<ParticlesObject*> treeParts;
	treeParts.push_back(new ParticlesObject(cylinder, vec3(0.0f, trunkHeight / 2, 0.0f), vec3(0.0f), TREE_SIZE * vec3(trunkRadius, trunkHeight, trunkRadius), Material(0.2f*brown, 0.7f*brown, 0.1f*brown, 0.05f), numberTrees));
	treeParts.push_back(new ParticlesObject(cone, vec3(0.0f, trunkHeight, 0.0f), vec3(0.0f), TREE_SIZE * branchesScaling*vec3(1.0f, 2.0f, 1.0f), leaves, numberTrees));
	treeParts.push_back(new ParticlesObject(cone, vec3(0.0f, trunkHeight + branchesHeightBot, 0.0f), vec3(0.0f), TREE_SIZE * branchesScaling*vec3(0.8f, 1.6f, 0.8f), leaves, numberTrees));
	treeParts.push_back(new ParticlesObject(cone, vec3(0.0f, trunkHeight + branchesHeightBot + branchesHeightMid, 0.0f), TREE_SIZE * vec3(0.0f), branchesScaling*vec3(0.6f, 1.2f, 0.6f), leaves, numberTrees));
	return treeParts;
}

MultiBodyObject* ObjectGenerator::getTerrainObject(Terrain& terrain) {
	MultiBodyObject* MBO = new MultiBodyObject();

	vector<Vertex> vertexData;
	vector<vector<vec3>> points;

	unsigned int mapSize = terrain.heightMap()->size();
	for (unsigned int iX = 0; iX < mapSize; iX++) {
		points.push_back(vector<vec3>());
		for (unsigned int iZ = 0; iZ < mapSize; iZ++) {
			points[iX].push_back(vec3((float)iX / (mapSize - 1) - 0.5f, terrain.heightMap()->get(iX, iZ), (float)iZ / (mapSize - 1) - 0.5f));
		}
	}

	for (unsigned int iX = 1; iX < mapSize; iX++) {
		for (unsigned int iZ = 1; iZ < mapSize; iZ++) {
			MeshDataGenerator::addTriangle(&vertexData, points[iX][iZ], points[iX - 1][iZ - 1], points[iX - 1][iZ]);
			MeshDataGenerator::addTriangle(&vertexData, points[iX][iZ], points[iX][iZ - 1], points[iX - 1][iZ - 1]);
		}
	}

	Mesh<Vertex>* mesh = new Mesh<Vertex>(vertexData);
	Material material = Material(Material::dark_grass);
	material.specular = vec3(0.0f);
	MBO->addBody(new UnicolorObject(mesh, vec3(0.0), vec3(0.0f), vec3(terrain.width(), 1.0f, terrain.width()), material));

	return MBO;
}

MultiBodyObject* ObjectGenerator::getQuadrocopter() {
	MultiBodyObject* quadcopterObject = new MultiBodyObject();
	quadcopterObject->addBody(new UnicolorObject(cylinder, vec3(0.5f, 0.0f, -0.5f), vec3(0.0f), vec3(0.2f, 0.05f, 0.2f), Material(Material::jade)));
	quadcopterObject->addBody(new UnicolorObject(cylinder, vec3(0.5f, 0.0f, 0.5f), vec3(0.0f), vec3(0.2f, 0.05f, 0.2f), Material(Material::jade)));
	quadcopterObject->addBody(new UnicolorObject(cylinder, vec3(-0.5f, 0.0f, -0.5f), vec3(0.0f), vec3(0.2f, 0.05f, 0.2f), Material(Material::jade)));
	quadcopterObject->addBody(new UnicolorObject(cylinder, vec3(-0.5f, 0.0f, 0.5f), vec3(0.0f), vec3(0.2f, 0.05f, 0.2f), Material(Material::jade)));
	return quadcopterObject;
}