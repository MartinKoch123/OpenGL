#pragma once
#include <vector>
#include <glm/glm.hpp>
#include <glad/glad.h>
#include "Shader.h"
#include "Texture.h"
#include "Material.h"

struct Vertex {
	glm::vec3 position;
	glm::vec3 normal;

	Vertex(glm::vec3 position, glm::vec3 normal) {
		this->position = position;
		this->normal = normal;
	}
	
};

struct TextureVertex : Vertex {
	glm::vec2 textureCoordinates;

	TextureVertex(glm::vec3 position, glm::vec3 normal, glm::vec2 texureCoordinates) : Vertex(position, normal) {
		this->textureCoordinates = textureCoordinates;
	}
};

struct MaterialVertex : Vertex {
	Material material;
	MaterialVertex(glm::vec3 position, glm::vec3 normal, Material material) : Vertex(position, normal) {
		this->material = material;
	}
};

template <typename vertexType>
class Mesh {
public:
	
	Mesh(std::vector<vertexType> vertices);
	Mesh() {};
	void draw();
	void setupInstancing();
	void drawInstances(unsigned int numberInstances);
	unsigned int instanceVBO;
protected:
	unsigned int VAO;
	unsigned int VBO;
	std::vector<vertexType> vertices;
	bool instancingWasSetUp = false;
};

class TextureMesh : public Mesh<TextureVertex> {
public:
	TextureMesh(std::vector<TextureVertex> vertices, Texture* texture, Texture* specularMap);
	TextureMesh() {};
	Texture* texture;
	Texture* specularMap;
};

class MaterialMesh : public Mesh<MaterialVertex> {
public:
	MaterialMesh(std::vector<MaterialVertex> vertices) {
		this->vertices = vertices;
		glGenBuffers(1, &VBO);
		glGenVertexArrays(1, &VAO);
		glBindVertexArray(VAO);
		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(MaterialVertex), &vertices[0], GL_STATIC_DRAW);
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(MaterialVertex), (void*)0);
		glEnableVertexAttribArray(1);
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(MaterialVertex), (void*)offsetof(MaterialVertex, normal));
		glEnableVertexAttribArray(2);
		glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(MaterialVertex), (void*)offsetof(MaterialVertex, material.ambient));
		glEnableVertexAttribArray(3);
		glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, sizeof(MaterialVertex), (void*)offsetof(MaterialVertex, material.diffuse));
		glEnableVertexAttribArray(4);
		glVertexAttribPointer(4, 3, GL_FLOAT, GL_FALSE, sizeof(MaterialVertex), (void*)offsetof(MaterialVertex, material.specular));
		glEnableVertexAttribArray(5);
		glVertexAttribPointer(5, 1, GL_FLOAT, GL_FALSE, sizeof(MaterialVertex), (void*)offsetof(MaterialVertex, material.shininess));
	};
};


template <typename vertexType>
Mesh<vertexType>::Mesh(std::vector<vertexType> vertices) {
	this->vertices = vertices;
	glGenBuffers(1, &VBO);
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), &vertices[0], GL_STATIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, normal));
}


template<typename vertexType>
inline void Mesh<vertexType>::draw() {
	glBindVertexArray(VAO);
	glDrawArrays(GL_TRIANGLES, 0, vertices.size());
}

template<typename vertexType>
inline void Mesh<vertexType>::setupInstancing() {
	if (instancingWasSetUp)
		return;
	glGenBuffers(1, &instanceVBO);
	glBindVertexArray(VAO);
	glEnableVertexAttribArray(2);
	glBindBuffer(GL_ARRAY_BUFFER, instanceVBO); // this attribute comes from a different vertex buffer
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glVertexAttribDivisor(2, 1); // tell OpenGL this is an instanced vertex attribute.
	instancingWasSetUp = true;
}

template<typename vertexType>
inline void Mesh<vertexType>::drawInstances(unsigned int numberInstances) {
	glBindVertexArray(VAO);
	glDrawArraysInstanced(GL_TRIANGLES, 0, vertices.size(), numberInstances);
}

