#include "Track.h"


Track::Track(Mesh<Vertex>* trackPartMesh, glm::vec2 startPoint) {
	this->trackPartMesh = trackPartMesh;
	trackObject = MultiBodyObject(glm::vec3(startPoint.x, 0.01f, startPoint.y), glm::vec3(0.0f), glm::vec3(1.0f));
	
	if (trackPartMesh == NULL)
		return;

	particles = new ParticlesObject(trackPartMesh, glm::vec3(0.0f), glm::vec3(glm::radians(-90.0f), 0.0f, 0.0f), glm::vec3(0.4f), Material(Material::black_rubber), MAX_NUMBER_PARTS);
	trackObject.addBody(particles);
	nextPart = 0;
}

Track::Track() {
	
}

void Track::addPosition(glm::vec3 position) {
	if (particles->particlePositions.size() > nextPart) {
		particles->particlePositions[nextPart] = glm::vec3(position.x, 0.0f, position.z);
	}
	nextPart++;
	if (nextPart == MAX_NUMBER_PARTS)
		nextPart = 0;

}

MultiBodyObject * Track::getTrackObject() {
	return &trackObject;
}

