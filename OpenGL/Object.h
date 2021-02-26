#pragma once
#include "Mesh.h"
#include "Shader.h"
#include "Material.h"
#include <glad\glad.h>
#include "PointLight.h"
#include "ShaderSet.h"
#include <vector>
#include <iostream>
#include <string>
#include "Mat.h"

class Object {
public:
	glm::vec3 position;
	Vec4 orientation;
	glm::vec3 scaling;
	Object(glm::vec3 position, glm::vec3 orientation, glm::vec3 scaling) {
		this->position = position;
		this->orientation = quaternion(orientation.x, orientation.y, orientation.z);
		this->scaling = scaling;
		this->updateModelMatrix();
	}
	Object() {};
	void updateModelMatrix();
	glm::mat4 getModelMatrix();
protected:
	glm::mat4 modelMatrix;
};

class SingleObject : public Object {
public:
	SingleObject(glm::vec3 position, glm::vec3 orientation, glm::vec3 scaling)
		: Object(position, orientation, scaling){ }
	SingleObject() {};
	virtual void draw(ShaderSet* shaders, glm::mat4 multiBodyModelMatrix) = 0;
	virtual void renderDepthMap(ShaderSet* shaders, glm::mat4 multiBodyModelMatrix) = 0;
};

template <typename meshType>
class MeshObject : public SingleObject {
public:
	MeshObject(meshType* mesh, glm::vec3 position, glm::vec3 orientation, glm::vec3 scaling) :
		SingleObject(position, orientation, scaling){
		this->mesh = mesh;
	}
	MeshObject() {};
	meshType* getMesh() {
		return mesh;
	};
	virtual void renderDepthMap(ShaderSet* shaders, glm::mat4 multiBodyModelMatrix);
protected:
	meshType* mesh;
};


class UnicolorObject : public MeshObject<Mesh<Vertex>>{
public:
	using MeshObject<Mesh<Vertex>>::MeshObject;
	UnicolorObject(Mesh<Vertex>* mesh, glm::vec3 position, glm::vec3 orientation, glm::vec3 scaling, Material material);
	UnicolorObject() {};
	Material material;
	void draw(ShaderSet* shaders, glm::mat4 multiBodyModelMatrix);
};

class TextureObject : public MeshObject<TextureMesh> {
public:
	using MeshObject<TextureMesh>::MeshObject;
	TextureObject(TextureMesh* mesh, glm::vec3 position, glm::vec3 orientation, glm::vec3 scaling, float shininess);
	float shininess;
	void draw(ShaderSet* shaders, glm::mat4 multiBodyModelMatrix);
};

class LightSourceObject : public MeshObject<Mesh<Vertex>> {
public:
	using MeshObject<Mesh<Vertex>>::MeshObject;
	LightSourceObject(Mesh<Vertex>* mesh, glm::vec3 position, glm::vec3 orientation, glm::vec3 scaling, glm::vec3 color);
	glm::vec3 color;
	void draw(ShaderSet* shaders, glm::mat4 multiBodyModelMatrix);
};

class MaterialMeshObject : public MeshObject<MaterialMesh> {
public:
	using MeshObject<MaterialMesh>::MeshObject;
	MaterialMeshObject(MaterialMesh* mesh, glm::vec3 position, glm::vec3 orientation, glm::vec3 scaling);
	void draw(ShaderSet* shaders, glm::mat4 multiBodyModelMatrix);
};

class ParticlesObject : public UnicolorObject {
public:
	ParticlesObject(Mesh<Vertex>* mesh, glm::vec3 position, glm::vec3 orientation, glm::vec3 scaling, Material material, unsigned int numberParticles);
	ParticlesObject() {};
	std::vector<glm::vec3> particlePositions;
	void draw(ShaderSet* shaders, glm::mat4 multiBodyModelMatrix);
	void renderDepthMap(ShaderSet* shaders, glm::mat4 multiBodyModelMatrix);
private:
	
};

template<typename meshType>
inline void MeshObject<meshType>::renderDepthMap(ShaderSet * shaders, glm::mat4 multiBodyModelMatrix) {
	shaders->defaultShadowMappingShader->use();
	shaders->defaultShadowMappingShader->setMat4("model", multiBodyModelMatrix);
	shaders->defaultShadowMappingShader->setMat4("body", modelMatrix);
	mesh->draw();
}
