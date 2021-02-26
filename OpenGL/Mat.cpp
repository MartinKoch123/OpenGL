#include "Mat.h"

Vec3 cross(const Vec3 & v1, const Vec3 & v2) {
	Vec3 result = Vec3();
	result.entries[0][0] = v1.entries[1][0] * v2.entries[2][0] - v1.entries[2][0] * v2.entries[1][0];
	result.entries[1][0] = v1.entries[2][0] * v2.entries[0][0] - v1.entries[0][0] * v2.entries[2][0];
	result.entries[2][0] = v1.entries[0][0] * v2.entries[1][0] - v1.entries[1][0] * v2.entries[0][0];
	return result;
}

Vec4 quaternion(float eulerX, float eulerY, float eulerZ) {
	return concatRotations(concatRotations(quaternion(eulerX, Vec3(1.0f, 0.0f, 0.0f)), quaternion(eulerY, Vec3(0.0f, 1.0f, 0.0f))), quaternion(eulerZ, Vec3(0.0f, 0.0f, 1.0f)));
}

Vec4 quaternion() {
	return Vec4(1.0f, 0.0f, 0.0f, 0.0f);
}

Vec4 quaternion(float angle, Vec3 axis) {
	if (angle == 0 || axis.norm() == 0.0f)
		return quaternion();
	axis = axis.normalize();
	return Vec4(cos(angle / 2.0f), sin(angle / 2.0f)*axis.x(), sin(angle / 2.0f)*axis.y(), sin(angle / 2.0f)*axis.z());
}

Mat3 eye3() {
	Mat3 result = Mat3();
	for (unsigned int i = 0; i < 3; i++) {
		result.entries[i][i] = 1.0f;
	}
	return result;
}

Mat3 rotation3(Vec4 quaternion) {
	float r[4][4];
	for (unsigned int i = 0; i < 4; i++) {
		for (unsigned int j = 0; j < 4; j++) {
			r[i][j] = 2 * quaternion.entries[i][0] * quaternion.entries[j][0];
		}
	}
	float entries[3][3] = {
		1 - r[2][2] - r[3][3],	r[1][2] - r[0][3],		r[1][3] + r[0][2],
		r[1][2] + r[0][3],		1 - r[1][1] - r[3][3],	r[2][3] - r[0][1],
		r[1][3] - r[0][2],		r[2][3] + r[0][1],		1 - r[1][1] - r[2][2],
	};
	return Mat3(entries);
}

Mat4 rotation4(Vec4 quaternion) {
	return rotation3(quaternion).homogenous();
}


Vec4 concatRotations(Vec4 first, Vec4 second) {
	Vec3 q1_r13 = Vec3(first.y(), first.z(), first.w());
	Vec3 q2_r13 = Vec3(second.y(), second.z(), second.w());
	
	Vec4 result = vertcat(
		Scal(first.x() * second.x()) - q1_r13.trans() * q2_r13,
		first.x() * q2_r13 + second.x() * q1_r13 + cross(q2_r13, q1_r13)
	);
	return result;
}

Vec3::Vec3(float x, float y, float z) {
	entries[0][0] = x;
	entries[0][1] = y;
	entries[0][2] = z;
}

Vec4::Vec4(float x, float y, float z, float w) {
	entries[0][0] = x;
	entries[0][1] = y;
	entries[0][2] = z;
	entries[0][3] = w;
}


Mat4 Mat3::homogenous() {
	return horzcat(vertcat(*this, Mat<1, 3>()), Vec4(0.0f, 0.0f, 0.0f, 1.0f));
}

glm::mat4 Mat4::toGLM() {
	glm::mat4 result;
	for (unsigned int i = 0; i < 4; i++) {
		for (unsigned int j = 0; j < 4; j++) {
			result[j][i] = entries[i][j];
		}
	}
	return result;
}

Vec2::Vec2(float x, float y) {
	entries[0][0] = x;
	entries[0][1] = y;
}
