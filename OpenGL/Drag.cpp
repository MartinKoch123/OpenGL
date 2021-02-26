#include "Drag.h"

Drag::Drag(float fluidDensity, Vec3 referenceAreas, Vec3 dragCoefficients) {
	factor = 0.5f * fluidDensity * elementMult(referenceAreas, dragCoefficients);
}

Vec3 Drag::getForces(Vec3 velocity) {
	return -1.0f * elementMult(signs(velocity), elementMult(factor, elementPow(velocity, 2.0f)));
}