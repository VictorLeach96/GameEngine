#include "Components/Movement.h"

#include <sdl/SDL.h>
#include <iostream>

#include "GameObject.h"
#include "Components/Transform.h"
#include "Components/Input.h"

void Movement::awake() {

	//Collect components to use
	shared<Input> input = this->gameObject.lock()->getComponent<Input>();
	shared<Transform> transform = this->gameObject.lock()->getComponent<Transform>();

	//Check game object has transform
	if (input.get() == nullptr) {
		cerr << "Movement: Could not find input on gameobject" << endl;
	}

	//Check game object has transform
	if (transform.get() == nullptr) {
		cerr << "Movement: Could not find transform on gameobject" << endl;
	}
}

void Movement::update(float delta) {

	//Collect components to use
	shared<Input> input = this->gameObject.lock()->getComponent<Input>();
	shared<Transform> transform = this->gameObject.lock()->getComponent<Transform>();

	//Handle movement
	if (input->isDown(SDLK_w)) {
		transform->position.z += this->walkSpeed * delta;
	}
	if (input->isDown(SDLK_s)) {
		transform->position.z -= this->walkSpeed * delta;
	}
	if (input->isDown(SDLK_a)) {
		transform->position.x += this->walkSpeed * delta;
	}
	if (input->isDown(SDLK_d)) {
		transform->position.x -= this->walkSpeed * delta;
	}
	if (input->isDown(SDLK_q)) {
		transform->position.y += this->walkSpeed * delta;
	}
	if (input->isDown(SDLK_e)) {
		transform->position.y -= this->walkSpeed * delta;
	}

	//Handle rotation
	if (input->isDown(SDLK_LEFT)) {
		transform->rotation.y -= this->rotateSpeed * delta;
	}
	if (input->isDown(SDLK_RIGHT)) {
		transform->rotation.y += this->rotateSpeed * delta;
	}
	if (input->isDown(SDLK_UP)) {
		transform->rotation.x -= this->rotateSpeed * delta;
	}
	if (input->isDown(SDLK_DOWN)) {
		transform->rotation.x += this->rotateSpeed * delta;
	}
}

void Movement::render() {
}

void Movement::destroy() {
}