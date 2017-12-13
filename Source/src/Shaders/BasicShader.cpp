#include "Shaders/BasicShader.h"

#include <glm/glm.hpp>
#include <iostream>

#include "GameObject.h"
#include "Mesh.h"

#include "Components/MeshRenderer.h"

void BasicShader::awake(weak<MeshRenderer> renderer) {

	//Check whether mesh exists
	if (renderer.lock()->mesh.get() == nullptr){
		cerr << "BasicShader: Could not find mesh on mesh renderer component" << endl;
	}

	//Create vertex arrays
	glGenVertexArrays(1, &this->vaoId);
	glBindVertexArray(this->vaoId);

	//Get verticies from mesh
	vector<glm::vec3> verticies = renderer.lock()->mesh->getVerticies();
	this->size = verticies.size();

	//Add mesh verticies to vertex array buffer
	glGenBuffers(1, &this->vertexId);
	glBindBuffer(GL_ARRAY_BUFFER, this->vertexId);
	glBufferData(GL_ARRAY_BUFFER, verticies.size() * sizeof(glm::vec3), &verticies[0], GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(0);

	//Get colour from mesh
	weak<glm::vec3> colour = renderer.lock()->colour;
	
	//Generate array of colours
	vector<glm::vec3> colours = vector<glm::vec3>();
	for (int i = 0; i < this->size; i++) {

		//Generate random colour if not found
		if (colour.expired()) {
			float x = rand() / double(RAND_MAX);
			float y = rand() / double(RAND_MAX);
			float z = rand() / double(RAND_MAX);
			colours.push_back(glm::vec3(x, y, z));
		} else {

			//Use colour selected
			colours.push_back(*colour.lock().get());
		}
	}

	//Add mesh verticies to vertex array buffer
	glGenBuffers(1, &this->colourId);
	glBindBuffer(GL_ARRAY_BUFFER, this->colourId);
	glBufferData(GL_ARRAY_BUFFER, colours.size() * sizeof(glm::vec3), &colours[0], GL_STATIC_DRAW);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(1);
}

void BasicShader::update(weak<MeshRenderer> renderer, float delta) {
}

void BasicShader::render(weak<MeshRenderer> renderer) {
	
	//Draw vbo
	glBindVertexArray(this->vaoId);
	glDrawArrays(GL_TRIANGLES, 0, this->size);
	glBindVertexArray(0);
}

void BasicShader::destroy(weak<MeshRenderer> renderer) {
}