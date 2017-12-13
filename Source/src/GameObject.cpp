#include "GameObject.h"
#include "Component.h"

#include <iostream>

void GameObject::awake(){
	
	//Awake each component
	for (int i=0; i < this->components.size(); i++){
		this->components[i]->awake();
	}
}

void GameObject::update(float delta){
	
	//Update each component
	for (int i=0; i < this->components.size(); i++){
		this->components[i]->update(delta);
	}
}

void GameObject::render(){
	
	//Update each component
	for (int i=0; i < this->components.size(); i++){
		this->components[i]->render();
	}
}

void GameObject::destroy(){
	
	//Destroy each component
	for (int i=0; i < this->components.size(); i++){
		this->components[i]->destroy();
	}
}

void GameObject::setParent(weak<GameObject> parent) {
	this->parent = parent;
}

weak<GameObject> GameObject::getParent() {
	return this->parent;
}