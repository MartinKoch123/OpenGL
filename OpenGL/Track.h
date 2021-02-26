#pragma once
#include "Renderer.h"
#include "Object.h"
#include "MeshDataGenerator.h"
#include <vector>

class Track{
public:
	Track(Mesh<Vertex>* trackPartMesh, glm::vec2 startPoint);
	Track();
	void addPosition(glm::vec3 position);
	MultiBodyObject* getTrackObject();
private:
	unsigned int MAX_NUMBER_PARTS = 400;
	Mesh<Vertex>* trackPartMesh;
	MultiBodyObject trackObject;
	
	unsigned int nextPart;
	ParticlesObject* particles;
};

