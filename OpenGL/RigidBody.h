#pragma once
#include "Mat.h"
#include "Vehicle.h"
#include <glm\glm.hpp>
#include "Tools.h"





class RigidBody : public PhysicalSystem {
public:
	float mass;
	Mat3 momentOfInertia;
	TransRotPair acceleration;
	TransRotPair velocity;
	Vec3 position;
	Vec4 orientation;
	MatQ<6> MInv66;
	RigidBody(float mass, Mat3 momentOfInertia33);
	RigidBody();
	void integrate(TransRotPair forces, float deltaTime);
	Vec3 getGravitationalForces();
	Vec3 getPosition();
	Vec4 getOrientation();
	TransRotPair getVelocity();
	float getAbsoluteVelocity();
	void setPosition(Vec3 position);
	void setOrientation(Vec4 orientation);
	void setVelocity(TransRotPair velocityPair);
};




