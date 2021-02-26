#pragma once
#include "Object.h"
#include "ShaderSet.h"

class MultiBodyObject : public Object {
public:
	MultiBodyObject(glm::vec3 position, glm::vec3 orientation, glm::vec3 scaling);
	MultiBodyObject(SingleObject* singleBody, glm::vec3 position, glm::vec3 orientation, glm::vec3 scaling);
	MultiBodyObject(LightSourceObject* lightSourceBody, PointLight* pointLight, glm::vec3 position, glm::vec3 orientation, glm::vec3 scaling);
	MultiBodyObject(std::vector<SingleObject*> bodies, glm::vec3 position, glm::vec3 orientation, glm::vec3 scaling);
	MultiBodyObject() : MultiBodyObject(glm::vec3(0.0f), glm::vec3(0.0f), glm::vec3(1.0f)) {};
	unsigned int getNumberBodies();
	unsigned int getNumberPointLights();
	SingleObject* getBody(unsigned int index);
	PointLight* getPointLight(unsigned int index);
	void addBody(SingleObject* body);
	void removeBody(unsigned int index);
	void draw(ShaderSet* shaders);
	void renderDepthMap(ShaderSet* shaders);
private:
	std::vector<SingleObject*> objects;
	std::vector<PointLight*> pointLights;
};
