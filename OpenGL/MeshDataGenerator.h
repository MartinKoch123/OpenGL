#pragma once
#include <glm\glm.hpp>
#include <glad\glad.h>
#include <vector>
#include "Mesh.h"
#include "Tools.h"


namespace MeshDataGenerator {
	std::vector<Vertex> square();
	std::vector<Vertex> cylinder(float height, unsigned int numberEdges);
	std::vector<Vertex> sphere(unsigned int numberEdges);
	std::vector<Vertex> spherePart(unsigned int n, float innerAngle, float outerAngle);
	std::vector<Vertex> pyramid(unsigned int n);
	std::vector<Vertex> cube();
	void rotate(std::vector<Vertex>* data, float angle, glm::vec3 axis);
	void attach(std::vector<Vertex>* base, std::vector<Vertex>* add);
	void quadrangleToTriangles(std::vector<Vertex>* data);
	std::vector<TextureVertex> textureSquare();
	std::vector<TextureVertex> textureCube();
	std::vector<MaterialVertex> toMaterialVertex(std::vector<Vertex> data, Material material);
	void addTriangle(std::vector<Vertex>* data, glm::vec3 point1, glm::vec3 point2, glm::vec3 point3);
	void addQuad(std::vector<Vertex>* data, glm::vec3 point1, glm::vec3 point2, glm::vec3 point3, glm::vec3 point4);
};
