#pragma once
#include "Quadrocopter.h"

class QuadcopterController {
public:
	QuadcopterController();
	virtual QuadrocopterInput getInput(Vec3 position, Vec4 orientation, TransRotPair velocity, float deltaTime) = 0;
	virtual void reset();
protected:
	float hoverForce;
};

class QCC_Height_PD : public QuadcopterController{
public:
	QCC_Height_PD();
	QuadrocopterInput getInput(Vec3 position, Vec4 orientation, TransRotPair velocity, float deltaTime);
private:
	Mat<1, 2> K;
};

class QCC_Height_PID : public QuadcopterController {
public:
	QCC_Height_PID();
	QuadrocopterInput getInput(Vec3 position, Vec4 orientation, TransRotPair velocity, float deltaTime);
	void reset();
private:
	Mat<1, 3> K;
	float integratedError = 0.0f;
};

