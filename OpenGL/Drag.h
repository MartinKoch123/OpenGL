#pragma once
#include "Mat.h"
class Drag {
public:
	Drag(float fluidDensity, Vec3 referenceAreas, Vec3 dragCoefficients);
	Drag() : Drag(0, Vec3(), Vec3()) {};
	Vec3 getForces(Vec3 velocity);
private:
	Vec3 factor;
};

