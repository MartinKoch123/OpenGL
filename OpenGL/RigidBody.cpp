#include "RigidBody.h"

RigidBody::RigidBody() : RigidBody(1.0, eye3()){ }

void RigidBody::integrate(TransRotPair forces, float deltaTime) {
	//Vec<6> C = vertcat(Vec3(), cross(Vec3(velocityBody6.entries[3][0], velocityBody6.entries[4][0], velocityBody6.entries[5][0]), momentOfInertia * Vec3(velocityBody6.entries[3][0], velocityBody6.entries[4][0], velocityBody6.entries[5][0])));
	//Vec<6> accelerationBody6 = MInv66 * (forces6 - C);

	acceleration.trans = eye3() / mass * forces.trans;
	acceleration.rot = momentOfInertia.inv() * (forces.rot - cross(velocity.rot, momentOfInertia * velocity.rot));

	velocity.trans += deltaTime * acceleration.trans;
	velocity.rot += deltaTime * acceleration.rot;
	Mat3 rotation = rotation3(orientation);
	position += deltaTime * rotation * velocity.trans;
	orientation += deltaTime * concatRotations(0.5f * Vec4(vertcat(Scal(0.0f), velocity.rot)), orientation);
	orientation = orientation / orientation.norm();
	velocity.trans = rotation3(orientation).trans() * rotation * velocity.trans;

}

Vec3 RigidBody::getGravitationalForces() {
	return rotation3(orientation).trans() * Vec3(0.0f, -GRAVITY, 0.0f) * mass;
}

Vec3 RigidBody::getPosition() {
	return position;
}

Vec4 RigidBody::getOrientation() {
	return orientation;
}

TransRotPair RigidBody::getVelocity() {
	return velocity;
}

float RigidBody::getAbsoluteVelocity() {
	return velocity.trans.norm();
}

void RigidBody::setPosition(Vec3 position) {
	this->position = position;
}

void RigidBody::setOrientation(Vec4 orientation) {
	this->orientation = orientation;
}

void RigidBody::setVelocity(TransRotPair velocityPair) {
	this->velocity = velocityPair;
}


RigidBody::RigidBody(float mass, Mat3 momentOfInertia33) 
	: mass(mass), momentOfInertia(momentOfInertia33), position(Vec3()), orientation(quaternion()) , velocity(TransRotPair()), acceleration(TransRotPair()) {
}

