#pragma once
#include <glm\glm.hpp>
#include "Mat.h"
#include "PhysicalSystem.h"

struct SingleTrackInput {
	SingleTrackInput() {
		phiVar = 0.0f;
		Fb = 0.0f;
		delta = 0.0f;
		xi = 0.5f;
		G = 1;
	};
	float phiVar;
	float Fb;
	float delta;
	float xi;
	unsigned int G;
};




class Vehicle : public PhysicalSystem {
public:
	Vehicle(float x, float y, float phi);
	Vehicle() : x(0), z(0), psi(0) {};
	virtual float getBeta();
	virtual Vec3 getPosition();
	virtual Vec4 getOrientation();
	virtual TransRotPair getVelocity();
	float getAbsoluteVelocity();
	float x;
	float z;
protected:
	float v;
	float psi;
	const float m = 500;
	float sign(float value);
};



