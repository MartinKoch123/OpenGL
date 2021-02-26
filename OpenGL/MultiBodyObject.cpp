#include "MultiBodyObject.h"

MultiBodyObject::MultiBodyObject(std::vector<SingleObject*> bodies, glm::vec3 position, glm::vec3 orientation, glm::vec3 scaling) :
	MultiBodyObject(position, orientation, scaling) {
	objects = bodies;
}

MultiBodyObject::MultiBodyObject(glm::vec3 position, glm::vec3 orientation, glm::vec3 scaling) :
	Object(position, orientation, scaling) {
	objects = std::vector<SingleObject*>();
	pointLights = std::vector<PointLight*>();
}

MultiBodyObject::MultiBodyObject(SingleObject * singleBody, glm::vec3 position, glm::vec3 orientation, glm::vec3 scaling) :
	MultiBodyObject(position, orientation, scaling) {
	objects = std::vector<SingleObject*>();
	objects.push_back(singleBody);
}

MultiBodyObject::MultiBodyObject(LightSourceObject * lightSourceBody, PointLight * pointLight, glm::vec3 position, glm::vec3 orientation, glm::vec3 scaling) :
	MultiBodyObject(position, orientation, scaling) {
	objects.push_back(lightSourceBody);
	pointLights.push_back(pointLight);
}

unsigned int MultiBodyObject::getNumberBodies() {
	return objects.size();
}

unsigned int MultiBodyObject::getNumberPointLights() {
	return pointLights.size();
}

SingleObject * MultiBodyObject::getBody(unsigned int index) {
	if (index >= objects.size())
		return nullptr;
	return objects[index];
}

PointLight * MultiBodyObject::getPointLight(unsigned int index) {
	if (index >= this->pointLights.size())
		return nullptr;
	return this->pointLights[index];
}

void MultiBodyObject::addBody(SingleObject * body) {
	if (body != NULL)
		objects.push_back(body);
}

void MultiBodyObject::removeBody(unsigned int index) {
	if (index < objects.size())
		objects.erase(objects.begin() + index);
}

void MultiBodyObject::draw(ShaderSet * shaders) {
	for (unsigned int i = 0; i < objects.size(); i++) {
		objects[i]->draw(shaders, modelMatrix);
	}
}

void MultiBodyObject::renderDepthMap(ShaderSet * shaders) {
	for (unsigned int i = 0; i < objects.size(); i++) {
		objects[i]->renderDepthMap(shaders, modelMatrix);
	}
}
