#include "Object.h"


void Object::updateModelMatrix() {
	modelMatrix = glm::translate(glm::mat4(1.0f), position) * rotation4(orientation).toGLM() * glm::scale(glm::mat4(1.0f), scaling);
}

glm::mat4 Object::getModelMatrix() {
	return modelMatrix;
}


UnicolorObject::UnicolorObject(Mesh<Vertex>* mesh, glm::vec3 position, glm::vec3 orientation, glm::vec3 scaling, Material material)
	: MeshObject(mesh, position, orientation, scaling){
	this->mesh = mesh;
	this->material = material;
}

void UnicolorObject::draw(ShaderSet * shaders, glm::mat4 multiBodyModelMatrix) {
	shaders->defaultShader->use();
	shaders->defaultShader->setMat4("model", multiBodyModelMatrix);
	shaders->defaultShader->setVec3("material.lightColors.ambient", material.ambient);
	shaders->defaultShader->setVec3("material.lightColors.diffuse", material.diffuse);
	shaders->defaultShader->setVec3("material.lightColors.specular", material.specular);
	shaders->defaultShader->setFloat("material.shininess", material.shininess);
	shaders->defaultShader->setMat4("body", modelMatrix);
	mesh->draw();
}

TextureObject::TextureObject(TextureMesh* mesh, glm::vec3 position, glm::vec3 orientation, glm::vec3 scaling, float shininess)
	: MeshObject(mesh, position, orientation, scaling) {
	this->mesh = mesh;
	this->shininess = shininess;
}

void TextureObject::draw(ShaderSet * shaders, glm::mat4 multiBodyModelMatrix) {
	shaders->textureShader->use();
	shaders->textureShader->setMat4("model", multiBodyModelMatrix);
	shaders->textureShader->setMat4("body", modelMatrix);
	shaders->textureShader->setInt("material.texture", 0);
	shaders->textureShader->setInt("material.specularTexture", 1);
	shaders->textureShader->setFloat("material.shininess", shininess);
	mesh->texture->use(0);
	mesh->specularMap->use(1);
	mesh->draw();
}

LightSourceObject::LightSourceObject(Mesh<Vertex>* mesh, glm::vec3 position, glm::vec3 orientation, glm::vec3 scaling, glm::vec3 color)
		: MeshObject(mesh, position, orientation, scaling) {
	this->mesh = mesh;
	this->color = color;
}

void LightSourceObject::draw(ShaderSet * shaders, glm::mat4 multiBodyModelMatrix) {
	shaders->lightSourceShader->use();
	shaders->lightSourceShader->setMat4("model", multiBodyModelMatrix);
	shaders->lightSourceShader->setVec3("color", color);
	shaders->lightSourceShader->setMat4("body", modelMatrix);
	mesh->draw();
}

MaterialMeshObject::MaterialMeshObject(MaterialMesh* mesh, glm::vec3 position, glm::vec3 orientation, glm::vec3 scaling)
	: MeshObject(mesh, position, orientation, scaling)	{
}

void MaterialMeshObject::draw(ShaderSet * shaders, glm::mat4 multiBodyModelMatrix) {
	shaders->materialMeshShader->use();
	shaders->materialMeshShader->setMat4("model", multiBodyModelMatrix);
	shaders->materialMeshShader->setMat4("body", modelMatrix);
	mesh->draw();
}

ParticlesObject::ParticlesObject(Mesh<Vertex>* mesh, glm::vec3 position, glm::vec3 orientation, glm::vec3 scaling, Material material, unsigned int numberParticles) :
	UnicolorObject(mesh, position, orientation, scaling, material){
	for (unsigned int i = 0; i < numberParticles; i++) {
		particlePositions.push_back(glm::vec3());
	}
	mesh->setupInstancing();
}

void ParticlesObject::draw(ShaderSet * shaders, glm::mat4 multiBodyModelMatrix) {
	
	glBindBuffer(GL_ARRAY_BUFFER, mesh->instanceVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec3) * particlePositions.size(), &particlePositions[0], GL_DYNAMIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	shaders->particleShader->use();
	shaders->particleShader->setMat4("model", multiBodyModelMatrix);
	shaders->particleShader->setVec3("material.lightColors.ambient", material.ambient);
	shaders->particleShader->setVec3("material.lightColors.diffuse", material.diffuse);
	shaders->particleShader->setVec3("material.lightColors.specular", material.specular);
	shaders->particleShader->setFloat("material.shininess", material.shininess);
	shaders->particleShader->setMat4("body", modelMatrix);
	

	mesh->drawInstances(particlePositions.size());
}

void ParticlesObject::renderDepthMap(ShaderSet * shaders, glm::mat4 multiBodyModelMatrix) {
	glBindBuffer(GL_ARRAY_BUFFER, mesh->instanceVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec3) * particlePositions.size(), &particlePositions[0], GL_DYNAMIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	shaders->instancingShadowMappingShader->use();
	shaders->instancingShadowMappingShader->setMat4("model", multiBodyModelMatrix);
	shaders->instancingShadowMappingShader->setMat4("body", modelMatrix);
	mesh->drawInstances(particlePositions.size());
}

