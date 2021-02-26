#include "Quadrocopter.h"

const float Quadrocopter::MASS = 5.0f;

Quadrocopter::Quadrocopter()  {
	mass = MASS;
	momentOfInertia = MOMENT_OF_INERTIA;
	drag = Drag(DENSITY_AIR, DRAG_REFERENCE_AREAS, DRAG_COEFFICIENT);
}

void Quadrocopter::integrate(QuadrocopterInput input, float deltaTime) {

	//float windSpeed = 5.0f;
	float windSpeed = 0.0f;

	std::default_random_engine generator;
	std::normal_distribution<double> distribution(-1.0f, 0.1f);

	double number = distribution(generator);

	Vec3 windDir = Vec3();
	//windDir.entries[0][0] = randomGauﬂ(-1.0f, 0.1f);
	windDir.entries[1][0] = randomGauﬂ(1.0f, 2.0f);
	//windDir.entries[2][0] = randomGauﬂ(-0.f, 0.1f);

	windDir = windDir.normalize();

	TransRotPair forces = calculateForces(input);
	forces.trans += getGravitationalForces();
	forces.trans += drag.getForces(velocity.trans + windDir * windSpeed);

	RigidBody::integrate(forces, deltaTime);
}

TransRotPair Quadrocopter::calculateForces(QuadrocopterInput input) {
	TransRotPair forces = TransRotPair();

	/*float thrustLeftFront = randomGauﬂ(input.thrustLeftFront, 0.1f);
	float thrustRightFront = randomGauﬂ(input.thrustRightFront, 0.1f);
	float thrustLeftRear = randomGauﬂ(input.thrustLeftRear, 0.1f);
	float thrustRightRear = randomGauﬂ(input.thrustRightRear, 0.1f);*/

	float thrustLeftFront = input.thrustLeftFront;
	float thrustRightFront = input.thrustRightFront;
	float thrustLeftRear = input.thrustLeftRear;
	float thrustRightRear = input.thrustRightRear;

	forces.trans += VECTOR_THRUST_DIRECTION * (thrustLeftFront + thrustRightFront + thrustLeftRear + thrustRightRear);

	forces.rot += thrustLeftFront * cross(POSITION_ROTOR_LEFT_FRONT, VECTOR_THRUST_DIRECTION);
	forces.rot += thrustRightFront * cross(POSITION_ROTOR_RIGHT_FRONT, VECTOR_THRUST_DIRECTION);
	forces.rot += thrustLeftRear * cross(POSITION_ROTOR_LEFT_REAR, VECTOR_THRUST_DIRECTION);
	forces.rot += thrustRightRear * cross(POSITION_ROTOR_RIGHT_REAR, VECTOR_THRUST_DIRECTION);

	forces.rot += 0.5f*(thrustLeftFront + thrustRightRear - thrustRightFront - thrustRightRear)*VECTOR_THRUST_DIRECTION;

	float dragX = -sign(velocity.trans.x()) * DRAG_FACTOR_XZ * pow(velocity.trans.x(), 2);
	float dragZ = -sign(velocity.trans.z()) * DRAG_FACTOR_XZ * pow(velocity.trans.z(), 2);
	float dragY = -sign(velocity.trans.y()) * DRAG_FACTOR_Y * pow(velocity.trans.y(), 2);

	float dragXaxis = -sign(velocity.rot.x()) * ROTATION_DRAG_FACTOR_XZ * pow(velocity.rot.x(), 2);
	float dragZaxis = -sign(velocity.rot.z()) * ROTATION_DRAG_FACTOR_XZ * pow(velocity.rot.z(), 2);
	float dragYaxis = -sign(velocity.rot.y()) * ROTATION_DRAG_FACTOR_Y * pow(velocity.rot.y(), 2);

	//forces.trans += Vec3(dragX, dragY, dragZ);
	forces.rot += Vec3(dragXaxis, dragYaxis, dragZaxis);

	return forces;
}

