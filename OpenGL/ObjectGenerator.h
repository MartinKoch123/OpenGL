#include "MultiBodyObject.h"
#include "Terrain.h"
#include "MeshDataGenerator.h"

#pragma once
class ObjectGenerator {
public:
	ObjectGenerator();
	MultiBodyObject* createCar(glm::vec3 position);
	MultiBodyObject* createTree(Terrain* terrain, float x, float z);
	std::vector<ParticlesObject*> getInstancingTree(Terrain* terrain, unsigned int numberTrees);
	MultiBodyObject * getTerrainObject(Terrain* terrain);
	MultiBodyObject * getQuadrocopter();
	Mesh<Vertex>* square;
	Mesh<Vertex>* cube;
	Mesh<Vertex>* sphere;
	Mesh<Vertex>* cylinder;
	Mesh<Vertex>* cylinder5;
	Mesh<Vertex>* pyramid4;
	Mesh<Vertex>* pyramid10;
	Mesh<Vertex>* cone;
	MaterialMesh* blackRubberSquare;
	MaterialMesh* greenRubberSquare;
	Texture* boxTexture;
	Texture* grassTexture;
	Texture* woodSteelBoxTexture;
	Texture* woodSteelBoxTexture_specular;
	Texture* defaultTexture_specular;
	static const float TREE_SIZE;
};

