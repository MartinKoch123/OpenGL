#pragma once
#include "Mat.h"

struct TransRotPair {
	TransRotPair(Vec3 trans, Vec3 rot) : trans(trans), rot(rot) {}
	TransRotPair() {}
	Vec3 trans;
	Vec3 rot;
};

class PhysicalSystem {
public:
	PhysicalSystem() {};
	Vec3 getHeading();
	virtual Vec3 getPosition() = 0;
	virtual Vec4 getOrientation() = 0;
	virtual TransRotPair getVelocity() = 0;
	virtual float getAbsoluteVelocity() = 0;
	virtual void setPosition(Vec3 position);
	virtual void setOrientation(Vec4 orientation);
	virtual void setVelocity(TransRotPair velocityPair);
};