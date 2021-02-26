#include "QuadcopterController.h"


QuadcopterController::QuadcopterController() {
	hoverForce = GRAVITY * Quadrocopter::MASS;
}

void QuadcopterController::reset() {
}


QCC_Height_PD::QCC_Height_PD() {

	// Poles -2, -2
	K.entries[0][0] = -4 * Quadrocopter::MASS;
	K.entries[0][1] = -4 * Quadrocopter::MASS;
}

QuadrocopterInput QCC_Height_PD::getInput(Vec3 position, Vec4 orientation, TransRotPair velocity, float deltaTime) {

	
	Vec2 deltaXi;
	
	float error = position.y() - 5.0f;

	deltaXi = Vec2(error, velocity.trans.y());

	float uniForce = (K*deltaXi).entries[0][0] + hoverForce;


	QuadrocopterInput input;
	input.thrustLeftFront = uniForce / 4.0f;
	input.thrustLeftRear = uniForce / 4.0f;
	input.thrustRightFront = uniForce / 4.0f;
	input.thrustRightRear = uniForce / 4.0f;
	return input;
}

QCC_Height_PID::QCC_Height_PID() {

	// Poles -2, -2, -2
	K.entries[0][0] = -8 * Quadrocopter::MASS;
	K.entries[0][1] = -12 * Quadrocopter::MASS;
	K.entries[0][2] = -6 * Quadrocopter::MASS;
	reset();
}

QuadrocopterInput QCC_Height_PID::getInput(Vec3 position, Vec4 orientation, TransRotPair velocity, float deltaTime) {

	float error = position.y() - 5.0f;

	integratedError += deltaTime * error;

	Vec3 deltaXi = Vec3(integratedError, error, velocity.trans.y());

	float uniForce = (K*deltaXi).entries[0][0] + hoverForce;

	QuadrocopterInput input;
	input.thrustLeftFront = uniForce / 4.0f;
	input.thrustLeftRear = uniForce / 4.0f;
	input.thrustRightFront = uniForce / 4.0f;
	input.thrustRightRear = uniForce / 4.0f;
	return input;
}

void QCC_Height_PID::reset() {
	integratedError = 0.0f;
}
