#pragma once
#include "RigidBody.h"
#include "Mat.h"
#include "Tools.h"
#include "Drag.h"
#include <random>

struct QuadrocopterInput {
	QuadrocopterInput(float leftFront, float rightFront, float leftRear, float rightRear) {
		thrustLeftFront = leftFront;
		thrustRightFront = rightFront;
		thrustLeftRear = leftRear;
		thrustRightRear = rightRear;
	}
	QuadrocopterInput(float equalThrust) : QuadrocopterInput(equalThrust, equalThrust, equalThrust, equalThrust) {};
	QuadrocopterInput() : QuadrocopterInput(0.0f) {};
	float thrustLeftFront;
	float thrustRightFront;
	float thrustLeftRear;
	float thrustRightRear;
};

class Quadrocopter : public RigidBody{
public:
	Quadrocopter();
	void integrate(QuadrocopterInput input, float deltaTime);
	static const float MASS;
private:
	TransRotPair calculateForces(QuadrocopterInput input);
	Drag drag;
	Vec3 POSITION_ROTOR_LEFT_FRONT = Vec3(0.5f, 0.0f, -0.5f);
	Vec3 POSITION_ROTOR_RIGHT_FRONT = Vec3(0.5f, 0.0f, 0.5f);
	Vec3 POSITION_ROTOR_LEFT_REAR = Vec3(-0.5f, 0.0f, -0.5f);
	Vec3 POSITION_ROTOR_RIGHT_REAR = Vec3(-0.5f, 0.0f, 0.5f);
	const Vec3 VECTOR_THRUST_DIRECTION = Vec3(0.0f, 1.0f, 0.0f);
	const Vec3 DRAG_REFERENCE_AREAS = Vec3(0.1f, 1.0f, 0.1f);
	const Vec3 DRAG_COEFFICIENT = Vec3(0.82f, 1.15f, 0.82f);
	float const DRAG_FACTOR_XZ = 0.2f;
	float const DRAG_FACTOR_Y = 0.5f;
	float const ROTATION_DRAG_FACTOR_XZ = 0.8f;
	float const ROTATION_DRAG_FACTOR_Y = 0.2f;
	
	const Mat3 MOMENT_OF_INERTIA = eye3();
	const float a = 0;
};