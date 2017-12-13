#include "Components/Transform.h"

#include "GameObject.h"

glm::mat4 Transform::matrix() {

	//Check whether parent exists
	glm::mat4 start;
	if (this->gameObject.lock()->getParent().expired()) {
		start = glm::mat4(1.0f);
	}else{
		
		//Apply parent transforms
		start = this->gameObject.lock()->getParent().lock()->getComponent<Transform>()->matrix();
	}

	//Calculate position
	glm::mat4 translate = glm::translate(start, this->position);

	//Rotate position
	glm::mat4 rotateX = glm::rotate(translate, glm::radians(this->rotation.x), glm::vec3(1.0f, 0.0f, 0.0f));
	glm::mat4 rotateY = glm::rotate(rotateX, glm::radians(this->rotation.y), glm::vec3(0.0f, 1.0f, 0.0f));
	glm::mat4 rotateZ = glm::rotate(rotateY, glm::radians(this->rotation.z), glm::vec3(0.0f, 0.0f, 1.0f));

	return rotateZ;
}

glm::vec3 Transform::forwards() {
	
	//Calculate foward matrix
	glm::mat4 foward = glm::rotate(glm::mat4(1.0f), glm::radians(90.0f), glm::vec3(0.0f, 0.0f, 1.0f));
	foward = glm::translate(foward, glm::vec3(0.0f, 0.0f, 1.0f));
	return foward * glm::vec4(0.0f, 0.0f, 0.0f, 1.0f);
}

void Transform::moveFowards(float delta, float amount) {

	//Move point fowards amount
	this->position += this->forwards() * delta * amount;
}

void Transform::moveBackwards(float delta, float amount) {

	//Move point backwards amount
	this->position -= this->forwards() * delta * amount;
}

void Transform::awake(){
}

void Transform::update(float delta){
}

void Transform::render(){
}

void Transform::destroy(){	
}