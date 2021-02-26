#include "PhysicalSystem.h"

Vec3 PhysicalSystem::getHeading() {
	return rotation3(getOrientation()) * Vec3(1.0f, 0.0f, 0.0f);
}

void PhysicalSystem::setPosition(Vec3 position) {
	
}

void PhysicalSystem::setOrientation(Vec4 orientation) {
}

void PhysicalSystem::setVelocity(TransRotPair velocityPair) {
}
