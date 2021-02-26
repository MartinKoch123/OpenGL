#include "SingleTrack.h"

SingleTrack::SingleTrack(float x, float y, float psi) : Vehicle(x, y, psi) {
	omega = 0;
	beta = 0;
	dx = 1.0f;
	dz = 0;
	dpsi = 0;
	dphi = 0;
	rearWheel = Body(this, Vec3(-lr, 0.0f, 0.0f), quaternion());
	frontWheel = Body(this, Vec3(lf, 0.0f, 0.0f), quaternion());
	lastGear = 0;
}

void SingleTrack::integrate(SingleTrackInput input, float h) {
	//if (input.phiVar > 0)
		//float abc = 1;
	//delta = -delta;
	//input.phiVar = 0.01f;
	float S = 0;
	/*if (v < R*dphi)
		S = (R*dphi - v) / R / dphi;
	else
		S = (v - R * dphi) / v;
	if (S != S)
		S = 0;*/
	float l = lf + lr;
	float n = (v*i[input.G - 1] * i0) / (R - R*S);
	if (n != n)
		n = 0.0f;
	if (n > 4800.0f * pi / 30.0f)
		n = 4800.0f * pi / 30.0f;
	float TM = 200 * input.phiVar*(15.0f - 14.0f*input.phiVar)*(1.0f - pow(30.0f / pi*n, 5.0f*input.phiVar) / pow(4800.0f, 5.0f*input.phiVar));
	float alphaf = input.delta - atan((lf*dpsi - v*sin(beta)) / v / cos(beta));
	if (alphaf != alphaf)
		alphaf = 0.0f;
	float alphar = atan((lr*dpsi + v*sin(beta)) / v / cos(beta));
	if (alphar != alphar)
		alphar = 0.0f;
	float mu = r0 + r1*abs(v) + r2*pow(abs(v), 2) + r3*pow(abs(v), 3) + r4*pow(abs(v), 4);
	float Fxf = -sign(v*cos(beta))*(1 - input.xi)*input.Fb - sign(v*cos(beta))*mu*m*g*lr / l;
	float Fxr = 1 / R*i[input.G - 1] * i0*TM - sign(v * cos(beta))*input.xi*input.Fb - sign(v*cos(beta))*mu*m*g*lf / l;
	float Fyf = 0.0f;
	float Fyr = 0.0f;
	if (abs(v) > 0.01f) {
		Fyf = Df*sin(Cf*atan(Bf*alphaf - Ef*(Bf*alphaf - atan(Bf * alphaf))));
		Fyr = Dr*sin(Cr*atan(Br*alphar - Er*(Br*alphar - atan(Br * alphar))));
	}
	float xNew = x + h*v*cos(psi - beta);
	float zNew = z + h*v*sin(psi - beta);
	float betaNew = beta + h*(omega - 1 / m / v*(Fxr*sin(beta) + Fxf*sin(input.delta + beta) + Fyr*cos(beta) + Fyf*cos(input.delta + beta)));
	if (betaNew != betaNew)
		betaNew = beta;
	float psiNew = psi + h*omega;
	float omegaNew = omega + h / Iz*(Fyf*lf*cos(input.delta) - Fyr*lr + Fxf*lf*sin(input.delta));
	float vNew = v + h / m*(Fxr*cos(beta) + Fxf*cos(input.delta + beta) - Fyr*sin(beta) - Fyf*sin(input.delta + beta));
	float dxNew = dx + h / m*((Fxr + Fxf*cos(input.delta) - Fyf*sin(input.delta))*cos(psi) - (Fyr + Fxf*sin(input.delta) + Fyf*cos(input.delta))*sin(psi));
	float dzNew = dz + h / m*((Fxr + Fxf*cos(input.delta) - Fyf*sin(input.delta))*sin(psi) + (Fyr + Fxf*sin(input.delta) + Fyf*cos(input.delta))*cos(psi));
	float dpsiNew = dpsi + h / Iz*(Fyf*lf*cos(input.delta) - Fyr*lr + Fxf*lf*sin(input.delta));
	dphi = dphi + h * R*Fxr / IR;
	x = xNew;
	z = zNew;
	v = vNew;
	beta = betaNew;
	psi = psiNew;
	omega = omegaNew;
	dx = dxNew;
	dz = dzNew;
	dpsi = dpsiNew;
	lastGear = input.G;
}

Vec3 SingleTrack::getPosition() {
	return Vec3(x, 0.0f, -z);
}

float SingleTrack::getBeta() {
	return psi;
}

unsigned int SingleTrack::getGear() {
	return lastGear;
}

Body::Body(Vehicle* system, Vec3 relativePosition, Vec4 relativeOrientation) {
	this->system = system;
	this->relativePosition = relativePosition;
	this->relativeOrientation = relativeOrientation;
}

Body::Body() {}


Vec3 Body::getPosition() {
	if (system == NULL)
		return Vec3();
	return system->getPosition() + rotation3(system->getOrientation()) * relativePosition;
}

Vec4 Body::getOrientation() {
	if (system == NULL)
		return Vec4();
	return system->getOrientation() + relativeOrientation;
}
