#pragma once
#include "MultiBodyObject.h"
#include "Object.h"
#include "Vehicle.h"

template <typename physicalModelType, typename inputType>
class PhysicalVisualModel {
public:
	MultiBodyObject* visualModel;
	physicalModelType* physicalModel;
	PhysicalVisualModel(physicalModelType* physicalModel, MultiBodyObject* visualModel) {
		this->physicalModel = physicalModel;
		this->visualModel = visualModel;
	};
	PhysicalVisualModel() : PhysicalVisualModel(NULL, NULL) {};
	void update(inputType input, float deltaTime);
	void setPose(Vec3 position, Vec4 orientation);
	
};

template <typename physicalModelType, typename inputType>
void PhysicalVisualModel<physicalModelType, inputType>::update(inputType input, float deltaTime) {
	if (physicalModel == NULL)
		return;
	physicalModel->integrate(input, deltaTime);
	if (visualModel == NULL)
		return;
	visualModel->position = physicalModel->getPosition().toGLM();
	visualModel->orientation = physicalModel->getOrientation();
	visualModel->updateModelMatrix();
}

template<typename physicalModelType, typename inputType>
inline void PhysicalVisualModel<physicalModelType, inputType>::setPose(Vec3 position, Vec4 orientation) {
	visualModel->position = position.toGLM();
	visualModel->orientation = orientation;
	visualModel->updateModelMatrix();
	physicalModel->setPosition(position);
	physicalModel->setOrientation(orientation);
}



