#pragma once
#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <vector>
#include "Mat.h"

class FreeCamera {
public:
	Vec3 position;
	Vec4 orientation;
	Vec3 front;
	Vec3 up;
	Vec3 right;

	FreeCamera() : FreeCamera(Vec3(), quaternion()) {};

	FreeCamera(Vec3 position, Vec4 orientation) : position(position), orientation(orientation){
		updateCameraVectors();
	}
	
	glm::mat4 GetViewMatrix() {
		return glm::lookAt(position.toGLM(), Vec3(position + front).toGLM(), up.toGLM());
	}

	void setOrientation(Vec4 orientation) {
		this->orientation = orientation;
		updateCameraVectors();
	}

private:
	void updateCameraVectors() {
		Mat3 rotationMatrix = rotation3(orientation);
		front = rotationMatrix * Vec3(1.0f, 0.0f, 0.0f);
		right = rotationMatrix * Vec3(0.0f, 0.0f, 1.0f);
		up = rotationMatrix * Vec3(0.0f, 1.0f, 0.0f);
	}
};
