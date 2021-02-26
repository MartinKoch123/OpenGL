#pragma once
#include "Vehicle.h"
#include "Tools.h"
#include <glm\glm.hpp>
#include <glad\glad.h>
#include <glm/gtc/matrix_transform.hpp>


class Body {
public:
	Body(Vehicle* system, Vec3 relativePosition, Vec4 relativeOrientation);
	Body();
	Vec3 relativePosition;
	Vec4 relativeOrientation;
	Vec3 getPosition();
	Vec4 getOrientation();
	Vehicle* system;
};
	

class SingleTrack : public Vehicle {
public:
	SingleTrack(float x, float y, float psi);
	void integrate(SingleTrackInput input, float h);
	Vec3 getPosition();
	float getBeta();
	Body rearWheel;
	Body frontWheel;
	unsigned int getGear();
private:
	const float pi = 3.141593f;
	//float S = 0.0f;
	const float mass = 1239.0f;
	const float g = 9.81f;
	const float lf = 1.19016f;
	const float lr = 1.37484f;
	const float R = 0.302f;
	const float Iz = 1752.0f;
	const float IR = 1.5f;
	const float i[5] = { 3.91f, 2.002f, 1.33f, 1.0f, 0.805f };
	const float i0 = 3.91f;
	const float Bf = 10.96f;
	const float Cf = 1.3f;
	const float Df = 4560.4f;
	const float Ef = -0.5f;
	const float Br = 12.67f;
	const float Cr = 1.3f;
	const float Dr = 3947.81f;
	const float Er = -0.5f;
	const float p0 = -37.8f;
	const float p1 = 1.54f;
	const float p2 = -0.0019f;
	const float q0 = -34.9f;
	const float q1 = -0.0019f;
	const float r0 = 0.009f;
	const float r1 = 7.2e-5f;
	const float r2 = 0.0f;
	const float r3 = 0.0f;
	const float r4 = 5.0388e-10f;
	float beta;
	float omega;
	float dx;
	float dz;
	float dpsi;
	float dphi;
	unsigned int lastGear;
};
