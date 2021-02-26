#include "Vehicle.h"


Vehicle::Vehicle(float x, float z, float psi) {
	this->x = x;
	this->z = z;
	this->psi = psi;
	v = 0;
}

Vec3 Vehicle::getPosition() {
	return Vec3(x, 0.0f, z);
}

Vec4 Vehicle::getOrientation() {
	return quaternion(0.0f, getBeta(), 0.0f);
}

TransRotPair Vehicle::getVelocity() {
	return TransRotPair();
}

float Vehicle::getBeta() {
	return psi;
}

float Vehicle::getAbsoluteVelocity() {
	return v;
}

float Vehicle::sign(float value) {
	if (value >= 1e-4f)
		return 1.0f;
	else if (value <= -1e-4f)
		return -1.0f;
	else
		return 0.0f;
}


