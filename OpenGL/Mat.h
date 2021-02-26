#pragma once
#include <vector>
#include <glm\glm.hpp>
#include "Tools.h"


template <unsigned int nRows, unsigned int nCols>
struct Mat {
	Mat(float entries[nRows][nCols]);
	Mat();
	Mat<nCols, nRows> trans();
	Mat<nRows, nCols>& operator+=(const Mat<nRows, nCols>& rhs);

	template <unsigned int nRows1, unsigned int nCols1, unsigned int nCols2>
	friend Mat<nRows1, nCols2> operator*(const Mat<nRows1, nCols1> &m1, const Mat<nCols1, nCols2> &m2);
	template <unsigned int nRows, unsigned int nCols>
	friend Mat<nRows, nCols> operator*(const float &s, const Mat<nRows, nCols> &m);
	template <unsigned int nRows, unsigned int nCols>
	friend Mat<nRows, nCols> operator*(const Mat<nRows, nCols> &m, const float &s);
	template <unsigned int nRows, unsigned int nCols>
	friend Mat<nRows, nCols> operator/(const Mat<nRows, nCols> &m, const float &s);
	template <unsigned int nRows, unsigned int nCols>
	friend Mat<nRows, nCols> operator+(const Mat<nRows, nCols> &m1, const Mat<nRows, nCols> &m2);
	template <unsigned int nRows, unsigned int nCols>
	friend Mat<nRows, nCols> operator-(const Mat<nRows, nCols> &m1, const Mat<nRows, nCols> &m2);
	template <unsigned int nRows1, unsigned int nRows2, unsigned int nCols>
	friend Mat<nRows1 + nRows2, nCols> vertcat(const Mat<nRows1, nCols> &m1, const Mat<nRows2, nCols> &m2);
	template <unsigned int nRows, unsigned int nCols1, unsigned int nCols2>
	friend Mat<nRows, nCols1 + nCols2> horzcat(const Mat<nRows, nCols1> &m1, const Mat<nRows, nCols2> &m2);
	template <unsigned int nRows, unsigned int nCols>
	friend Mat<nRows, nCols> elementMult(const Mat<nRows, nCols> &m1, const Mat<nRows, nCols> &m2);
	template <unsigned int nRows, unsigned int nCols>
	friend Mat<nRows, nCols> elementPow(const Mat<nRows, nCols> &m, const float exponent);
	template <unsigned int nRows, unsigned int nCols>
	friend Mat<nRows, nCols> signs(const Mat<nRows, nCols> &m);
	//template <unsigned int nRowsIn, unsigned int nRowsOut, unsigned int nCols>
	//friend testM<nRowsOut, nCols> vertsub(const testM<nRowsIn, nCols> &m, unsigned int firstRow, nRowsIn - nRowsOut);

	float entries[nRows][nCols];
};

template <unsigned int nRows>
struct Vec : public Mat<nRows, 1> {
	Vec(float entries[nRows][1]) : Mat<nRows, 1>(entries) {};
	Vec(Mat<nRows, 1> m) : Mat<nRows, 1>(m.entries) {};
	Vec(float uniValue);
	Vec() : Mat<nRows, 1>() {};
	float norm();

	Vec<nRows> normalize();

	template <unsigned int nRows>
	friend float scalar(Vec<nRows> &v1, Vec<nRows> &v2);

};

struct Scal : public Vec<1> {
	Scal(float value) : Vec<1>(value) {};
	Scal() : Vec<1>() {};
};

struct Vec2 : public Vec<2> {
	Vec2(float x, float y);
	Vec2(float uniValue) : Vec<2>(uniValue) {};
	Vec2(Mat<2, 1> m) : Vec<2>(m.entries) {};
	Vec2() : Vec<2>() {};
	float x() { return entries[0][0]; };
	float y() { return entries[0][1]; };
	glm::vec2 toGLM() { return glm::vec2(x(), y()); };
};


struct Vec3 : public Vec<3> {
	Vec3(float x, float y, float z);
	Vec3(float uniValue) : Vec<3>(uniValue) {};
	Vec3(Mat<3, 1> m) : Vec<3>(m.entries) {};
	Vec3() : Vec<3>() {};
	float x() { return entries[0][0]; };
	float y() { return entries[0][1]; };
	float z() { return entries[0][2]; };
	glm::vec3 toGLM() { return glm::vec3(x(), y(), z()); };
	friend Vec3 cross(const Vec3 &v1, const Vec3 &v2);
};

struct Vec4 : public Vec<4> {
	Vec4(float x, float y, float z, float w);
	Vec4(float uniValue) : Vec<4>(uniValue) {};
	Vec4(Mat<4, 1> m) : Vec<4>(m.entries) {};
	Vec4() : Vec<4>() {};
	float x() { return entries[0][0]; };
	float y() { return entries[0][1]; };
	float z() { return entries[0][2]; };
	float w() { return entries[0][3]; };
	glm::vec4 toGLM() { return glm::vec4(x(), y(), z(), w()); };
};

//struct Vec6 : public Vec<6> {
//	Vec4(float x, float y, float z, float w);
//	Vec4(Mat<4, 1> m) : Vec<4>(m.entries) {};
//	Vec4() : Vec<4>() {};
//	float x() { return entries[0][0]; };
//	float y() { return entries[0][1]; };
//	float z() { return entries[0][2]; };
//	float w() { return entries[0][3]; };
//	glm::vec4 toGLM() { return glm::vec4(x(), y(), z(), w()); };
//};

template <unsigned int size>
struct MatQ : public Mat<size, size> {
	MatQ(float entries[size][size]) : Mat<size, size>(entries) {};
	MatQ(Mat<size, size> m) : Mat<size, size>(m.entries) {};
	MatQ() : Mat<size, size>() {};
	MatQ<size> cholesky();
	MatQ<size> inv();
};



struct Mat4 : MatQ<4> {
	Mat4(float entries[4][4]) : MatQ<4>(entries) {};
	Mat4(Mat<4, 4> m) : MatQ<4>(m.entries) {};
	Mat4() : MatQ<4>() {};
	glm::mat4 toGLM();
};

struct Mat3 : MatQ<3> {
	Mat3(float entries[3][3]) : MatQ<3>(entries) {};
	Mat3(Mat<3, 3> m) : MatQ<3>(m.entries) {};
	Mat3() : MatQ<3>() {};
	Mat4 homogenous();
};

Vec4 concatRotations(Vec4 q1, Vec4 q2);
Vec4 quaternion(float eulerX, float eulerY, float eulerZ);
Vec4 quaternion();
Vec4 quaternion(float angle, Vec3 axis);
Mat3 eye3();
Mat3 rotation3(Vec4 quaternion);
Mat4 rotation4(Vec4 quaternion);

template<unsigned int nRows, unsigned int nCols>
inline Mat<nRows, nCols>::Mat(float entries[nRows][nCols]) {
	for (unsigned int i = 0; i < nRows; i++) {
		for (unsigned int j = 0; j < nCols; j++) {
			this->entries[i][j] = entries[i][j];
		}
	}
}

template<unsigned int nRows, unsigned int nCols>
inline Mat<nRows, nCols>::Mat() {
	for (unsigned int i = 0; i < nRows; i++) {
		for (unsigned int j = 0; j < nCols; j++) {
			entries[i][j] = 0.0f;
		}
	}
}

template<unsigned int nRowsIn, unsigned int nColsIn>
inline Mat<nColsIn, nRowsIn> Mat<nRowsIn, nColsIn>::trans() {
	Mat<nColsIn, nRowsIn> result = Mat<nColsIn, nRowsIn>();
	for (unsigned int i = 0; i < nRowsIn; i++) {
		for (unsigned int j = 0; j < nColsIn; j++) {
			result.entries[j][i] = entries[i][j];
		}
	}
	return result;
}

template<unsigned int nRows, unsigned int nCols>
inline Mat<nRows, nCols>& Mat<nRows, nCols>::operator+=(const Mat<nRows, nCols>& rhs) {
	for (unsigned int i = 0; i < nRows; i++) {
		for (unsigned int j = 0; j < nCols; j++) {
			entries[i][j] += rhs.entries[i][j];
		}
	}
	return *this;
}

template<unsigned int nRows1, unsigned int nCols1, unsigned int nCols2>
inline Mat<nRows1, nCols2> operator*(const Mat<nRows1, nCols1>& m1, const Mat<nCols1, nCols2>& m2) {
	Mat<nRows1, nCols2> result = Mat<nRows1, nCols2>();
	for (unsigned int r1 = 0; r1 < nRows1; r1++) {
		for (unsigned int c2 = 0; c2 < nCols2; c2++) {
			for (unsigned int c1 = 0; c1 < nCols1; c1++) {
				result.entries[r1][c2] += m1.entries[r1][c1] * m2.entries[c1][c2];
			}
		}
	}
	return result;
}

template<unsigned int nRows, unsigned int nCols>
inline Mat<nRows, nCols> operator+(const Mat<nRows, nCols>& m1, const Mat<nRows, nCols>& m2) {
	Mat<nRows, nCols> result = Mat<nRows, nCols>();
	for (unsigned int i = 0; i < nRows; i++) {
		for (unsigned int j = 0; j < nCols; j++) {
				result.entries[i][j] = m1.entries[i][j] + m2.entries[i][j];
		}
	}
	return result;
}

template<unsigned int nRows, unsigned int nCols>
inline Mat<nRows, nCols> operator-(const Mat<nRows, nCols>& m1, const Mat<nRows, nCols>& m2) {
	Mat<nRows, nCols> result = Mat<nRows, nCols>();
	for (unsigned int i = 0; i < nRows; i++) {
		for (unsigned int j = 0; j < nCols; j++) {
			result.entries[i][j] = m1.entries[i][j] - m2.entries[i][j];
		}
	}
	return result;
}

template<unsigned int nRows1, unsigned int nRows2, unsigned int nCols>
inline Mat<nRows1 + nRows2, nCols> vertcat(const Mat<nRows1, nCols>& m1, const Mat<nRows2, nCols>& m2) {
	Mat<nRows1 + nRows2, nCols> result = Mat<nRows1 + nRows2, nCols>();
	for (unsigned int j = 0; j < nCols; j++) {
		for (unsigned int i = 0; i < nRows1; i++) {
			result.entries[i][j] = m1.entries[i][j];
		}
		for (unsigned int i = 0; i < nRows2; i++) {
			result.entries[i+nRows1][j] = m2.entries[i][j];
		}
	}
	return result;
}

template<unsigned int nRows, unsigned int nCols1, unsigned int nCols2>
inline Mat<nRows, nCols1 + nCols2> horzcat(const Mat<nRows, nCols1>& m1, const Mat<nRows, nCols2>& m2) {
	Mat<nRows, nCols1 + nCols2> result = Mat<nRows, nCols1 + nCols2>();
	for (unsigned int i = 0; i < nRows; i++) {
		for (unsigned int j = 0; j < nCols1; j++) {
			result.entries[i][j] = m1.entries[i][j];
		}
		for (unsigned int j = 0; j < nCols2; j++) {
			result.entries[i][nCols1 + j] = m2.entries[i][j];
		}
	}
	return result;
}

template<unsigned int nRows, unsigned int nCols>
inline Mat<nRows, nCols> elementMult(const Mat<nRows, nCols>& m1, const Mat<nRows, nCols>& m2) {
	Mat<nRows, nCols> result = Mat<nRows, nCols>();
	for (unsigned int i = 0; i < nRows; i++) {
		for (unsigned int j = 0; j < nCols; j++) {
			result.entries[i][j] = m1.entries[i][j] * m2.entries[i][j];
		}
	}
	return result;
}

template<unsigned int nRows, unsigned int nCols>
inline Mat<nRows, nCols> elementPow(const Mat<nRows, nCols>& m, const float exponent) {
	Mat<nRows, nCols> result = Mat<nRows, nCols>();
	for (unsigned int i = 0; i < nRows; i++) {
		for (unsigned int j = 0; j < nCols; j++) {
			result.entries[i][j] = pow(m.entries[i][j], exponent);
		}
	}
	return result;
}

template<unsigned int nRows, unsigned int nCols>
inline Mat<nRows, nCols> signs(const Mat<nRows, nCols>& m) {
	Mat<nRows, nCols> result = Mat<nRows, nCols>();
	for (unsigned int i = 0; i < nRows; i++) {
		for (unsigned int j = 0; j < nCols; j++) {
			result.entries[i][j] = sign(m.entries[i][j]);
		}
	}
	return result;
}

template<unsigned int nRows>
inline float scalar(Vec<nRows>& v1, Vec<nRows>& v2) {
	return (v1.trans() * v2).entries[0][0];
}

//template<unsigned int nRowsIn, unsigned int nRowsOut, unsigned int nCols>
//inline testM<nRowsOut, nCols> vertsub(const testM<nRowsIn, nCols>& m, unsigned int firstRow, nRowsIn - nRowsOut) {
//	testM<nRowsOut, nCols> result = testM<nRowsOut, nCols>();
//	for (unsigned int i = 0; i < nRowsOut; i++) {
//		for (unsigned int j = 0; j < nCols; j++) {
//			result.entries[i][j] = m.entries[firstRow + i][j];
//		}
//	}
//	return result;
//}

template<unsigned int size>
MatQ<size> eye() {
	MatQ<size> result = MatQ<size>();
	for (unsigned int i = 0; i < size; i++) {
		result.entries[i][i] = 1.0f;
	}
}

template<unsigned int nRows, unsigned int nCols>
inline Mat<nRows, nCols> operator*(const float & s, const Mat<nRows, nCols>& m) {
	Mat<nRows, nCols> result = Mat<nRows, nCols>();
	for (unsigned int i = 0; i < nRows; i++) {
		for (unsigned int j = 0; j < nCols; j++) {
			result.entries[i][j] = s * m.entries[i][j];
		}
	}
	return result;
}

template<unsigned int nRows, unsigned int nCols>
inline Mat<nRows, nCols> operator*(const Mat<nRows, nCols>& m, const float & s) {
	return s * m;
}

template<unsigned int nRows, unsigned int nCols>
inline Mat<nRows, nCols> operator/(const Mat<nRows, nCols>& m, const float & s) {
	Mat<nRows, nCols> result = Mat<nRows, nCols>();
	for (unsigned int i = 0; i < nRows; i++) {
		for (unsigned int j = 0; j < nCols; j++) {
			result.entries[i][j] = m.entries[i][j] / s;
		}
	}
	return result;
}

template<unsigned int nRows>
inline Vec<nRows>::Vec(float uniValue) {
	for (unsigned int i = 0; i < nRows; i++) {
		entries[i][0] = uniValue;
	}
}

template<unsigned int nRows>
inline float Vec<nRows>::norm() {
	float result = 0.0f;
	for (unsigned int i = 0; i < nRows; i++) {
		result += pow(entries[i][0], 2);
	}
	return sqrt(result);
}

template<unsigned int nRows>
inline Vec<nRows> Vec<nRows>::normalize() {
	return *this / this->norm();
}

template<unsigned int size>
inline MatQ<size> MatQ<size>::cholesky() {
	MatQ<size> result = *this;
	float temp;
	for (unsigned int i = 0; i < size; i++) {
		for (unsigned int j = 0; j <= i; j++) {
			temp = result.entries[i][j];
			for (unsigned int k = 0; k < j; k++) {
				temp = temp - result.entries[i][k] * result.entries[j][k];
			}
			if (i > j)
				result.entries[i][j] = temp / result.entries[j][j];
			else if (temp > 0)
				result.entries[i][j] = sqrt(temp);
			else {
				return MatQ<size>();
			}
		}
	}
	return result;
}

template<unsigned int size>
inline MatQ<size> MatQ<size>::inv() {
	// pos. def. only!
	MatQ<size> L = cholesky();
	MatQ<size> Linv = MatQ<size>();
	for (unsigned int i = 0; i < size; i++) {
		for (unsigned int j = 0; j <= i; j++) {
			if (i == j) {
				Linv.entries[i][i] = 1 / L.entries[i][i];
			}
			else {
				for (unsigned int k = j; k < i; k++) {
					Linv.entries[i][j] = Linv.entries[i][j] - L.entries[i][k] * Linv.entries[k][j];
				}
				Linv.entries[i][j] = Linv.entries[i][j] / L.entries[i][i];
			}
		}
	}
	return Linv.trans()*Linv;
}
