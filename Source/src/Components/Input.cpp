#include "Components/Input.h"

#include <iostream>

vector<SDL_Keycode> Input::keys = vector<SDL_Keycode>();

bool Input::isDown(SDL_Keycode type) {
	
	//Check whether key exists in list
	for (int i = 0; i < Input::keys.size(); i++) {
		if (Input::keys[i] == type) {
			return true;
		}
	}
	return false;
}

bool Input::poll() {

	//Collect pressed keys
	SDL_Event incomingEvent;
	while (SDL_PollEvent(&incomingEvent)) {

		//Handle quit event
		if (incomingEvent.type == SDL_QUIT) {
			return false;
		}

		//Handle key down events
		if (incomingEvent.type == SDL_KEYDOWN) {

			//Check whether to quit
			if (incomingEvent.key.keysym.sym == SDLK_ESCAPE) {
				return true;
			}

			//Check whether key exists in list already
			bool found = false;
			for (int i = 0; i < Input::keys.size(); i++) {
				if (Input::keys[i] == incomingEvent.key.keysym.sym) {
					found = true;
				}
			}

			//Add key to list if not already
			if (!found) {
				Input::keys.push_back(incomingEvent.key.keysym.sym);
			}
		}

		//Handle key down events
		if (incomingEvent.type == SDL_KEYUP) {

			//Remove key from list
			for (int i = 0; i < Input::keys.size(); i++) {
				if (Input::keys[i] == incomingEvent.key.keysym.sym) {
					Input::keys.erase(Input::keys.begin() + i);
					continue;
				}
			}
		}
	}

	return false;
}

void Input::awake() {
}

void Input::update(float delta) {
}

void Input::render() {
}

void Input::destroy() {
}