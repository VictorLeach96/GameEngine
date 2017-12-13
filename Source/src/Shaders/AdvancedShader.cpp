#include "Shaders/AdvancedShader.h"

#include <glm/glm.hpp>
#include <iostream>

#include "Scene.h"
#include "GameObject.h"
#include "Material.h"
#include "Mesh.h"

#include "Components/MeshRenderer.h"
#include "Components/Light.h"
#include "Components/Transform.h"

void AdvancedShader::awake(weak<MeshRenderer> renderer) {

	//Check whether mesh exists
	if (renderer.lock()->mesh.get() == nullptr){
		cerr << "AdvancedShader: Could not find mesh on mesh renderer component" << endl;
	}

	//Create vertex arrays
	glGenVertexArrays(1, &this->vaoId);
	glBindVertexArray(this->vaoId);

	//Get mesh details from mesh renderer
	vector<glm::vec3> verticies = renderer.lock()->mesh->getVerticies();
	vector<glm::vec2> uvs = renderer.lock()->mesh->getUvs();
	vector<glm::vec3> normals = renderer.lock()->mesh->getNormals();
	vector<glm::vec3> tangents = renderer.lock()->mesh->getTangents();
	vector<glm::vec3> bitangents = renderer.lock()->mesh->getBitangents();
	this->size = verticies.size();

	//Add mesh verticies to vertex array buffer
	glGenBuffers(1, &this->verticiesId);
	glBindBuffer(GL_ARRAY_BUFFER, this->verticiesId);
	glBufferData(GL_ARRAY_BUFFER, verticies.size() * sizeof(glm::vec3), &verticies[0], GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(0);
	
	//Add mesh verticies to vertex array buffer
	glGenBuffers(1, &this->uvsId);
	glBindBuffer(GL_ARRAY_BUFFER, this->uvsId);
	glBufferData(GL_ARRAY_BUFFER, uvs.size() * sizeof(glm::vec2), &uvs[0], GL_STATIC_DRAW);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(1);

	//Add mesh normals to vertex array buffer
	glGenBuffers(1, &this->normalsId);
	glBindBuffer(GL_ARRAY_BUFFER, this->normalsId);
	glBufferData(GL_ARRAY_BUFFER, normals.size() * sizeof(glm::vec3), &normals[0], GL_STATIC_DRAW);
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(2);

	//Add mesh tangents to vertex array buffer
	glGenBuffers(1, &this->tangentsId);
	glBindBuffer(GL_ARRAY_BUFFER, this->tangentsId);
	glBufferData(GL_ARRAY_BUFFER, tangents.size() * sizeof(glm::vec3), &tangents[0], GL_STATIC_DRAW);
	glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(3);

	//Add mesh bitangents to vertex array buffer
	glGenBuffers(1, &this->bitangentsId);
	glBindBuffer(GL_ARRAY_BUFFER, this->bitangentsId);
	glBufferData(GL_ARRAY_BUFFER, bitangents.size() * sizeof(glm::vec3), &bitangents[0], GL_STATIC_DRAW);
	glVertexAttribPointer(4, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(4);
	
	//Get material details from material component
	SDL_Surface* diffuse = renderer.lock()->material->getDiffuseTexture();
	SDL_Surface* normal = renderer.lock()->material->getNormalTexture();
	SDL_Surface* specular = renderer.lock()->material->getSpecularTexture();

	//Get diffuse texture uniform locations
	this->diffuseTextureId = glGetUniformLocation(this->getProgramId(), "txDiffuse");
	this->diffuseTexture = this->loadTexture(diffuse);

	//Get normal texture uniform locations
	this->normalTextureId = glGetUniformLocation(this->getProgramId(), "txNormal");
	this->normalTexture = this->loadTexture(normal);

	//Get specular texture uniform locations
	this->specularTextureId = glGetUniformLocation(this->getProgramId(), "txSpecular");
	this->specularTexture = this->loadTexture(specular);

	//Get material uniform locations
	this->diffuseId = glGetUniformLocation(this->getProgramId(), "uMaterialDiffuse");
	this->specularId = glGetUniformLocation(this->getProgramId(), "uMaterialSpecular");
	this->ambientId = glGetUniformLocation(this->getProgramId(), "uMaterialAmbient");

	//Get light uniform locations
	this->lightPosId = glGetUniformLocation(this->getProgramId(), "uLightPos");
	this->lightColourId = glGetUniformLocation(this->getProgramId(), "uLightColor");
	this->lightPowerId = glGetUniformLocation(this->getProgramId(), "uLightPower");
}

void AdvancedShader::update(weak<MeshRenderer> renderer, float delta) {
}

void AdvancedShader::render(weak<MeshRenderer> renderer) {

	//Find light from scene
	vector<shared<GameObject>> gameObjects = renderer.lock()->gameObject.lock()->scene.lock()->gameObjects;
	for (int i = 0; i < gameObjects.size(); i++) {
		
		//Find light and transform in game object and check whether exists
		shared<Light> light = gameObjects[i]->getComponent<Light>();
		shared<Transform> transform = gameObjects[i]->getComponent<Transform>();
		if (light.get() != nullptr && transform.get() != nullptr) {

			//Update lighting uniforms
			glUniform3f(this->lightPosId, transform->position.x, transform->position.y, transform->position.z);
			glUniform3f(this->lightColourId, light->colour.x, light->colour.y, light->colour.z);
			glUniform1f(this->lightPowerId, light->power);

			break;
		}
	}

	//Get material details from material component
	glm::vec3 diffuse = renderer.lock()->material->getDiffuse();
	glm::vec3 specular = renderer.lock()->material->getSpecular();
	glm::vec3 ambient = renderer.lock()->material->getAmbient();

	//Update material uniforms
	glUniform3f(this->diffuseId, diffuse.x, diffuse.y, diffuse.z);
	glUniform3f(this->specularId, specular.x, specular.y, specular.z);
	glUniform3f(this->ambientId, ambient.x, ambient.y, ambient.z);

	//Bind diffuse texture map to unit
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, this->diffuseTexture);
	glUniform1i(this->diffuseTextureId, 0);

	//Bind normal texture map to unit
	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, this->normalTexture);
	glUniform1i(this->normalTextureId, 1);

	//Bind specular texture map to unit
	glActiveTexture(GL_TEXTURE2);
	glBindTexture(GL_TEXTURE_2D, this->specularTexture);
	glUniform1i(this->specularTextureId, 2);

	//Draw vbo
	glBindVertexArray(this->vaoId);
	glDrawArrays(GL_TRIANGLES, 0, this->size);
	glBindVertexArray(0);

	//Unbind textures
	glBindTexture(GL_TEXTURE_2D, 0);
	glBindTexture(GL_TEXTURE_2D, 1);
	glBindTexture(GL_TEXTURE_2D, 2);
}

void AdvancedShader::destroy(weak<MeshRenderer> renderer) {
}