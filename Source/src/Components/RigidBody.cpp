#include "Components/RigidBody.h"

#include <iostream>

#include "GameObject.h"
#include "Scene.h"

#include "Components/Colider.h"
#include "Components/Transform.h"

void RigidBody::awake(){

	//Get colider and transform
	shared<Colider> colider = this->gameObject.lock()->getComponent<Colider>();
	shared<Transform> transform = this->gameObject.lock()->getComponent<Transform>();

	//Check game object has colider
	if (colider.get() == nullptr) {
		cerr << "RigidBody: Could not find colider on gameobject" << endl;
	}

	//Check game object has transform
	if (transform.get() == nullptr) {
		cerr << "RigidBody: Could not find transform on gameobject" << endl;
	}

	//Create motion state
	btQuaternion quaternion = btQuaternion(0, 0, 0, 1);
	btVector3 position = btVector3(transform->position.x, transform->position.y, transform->position.z);
	btDefaultMotionState* motionState = new btDefaultMotionState(btTransform(quaternion, position));

	//Create rigid body with and without mass
	if (this->mass > 0) {

		//Calculate inertia
		btVector3 inertia(0, 0, 0);
		colider->shape->calculateLocalInertia(this->mass, inertia);
		
		//Create rigid body info
		btRigidBody::btRigidBodyConstructionInfo groundRigidBodyCI(this->mass, motionState, colider->shape, inertia);
		this->rigidBody = new btRigidBody(groundRigidBodyCI);

	} else {

		//Create rigid body info
		btRigidBody::btRigidBodyConstructionInfo groundRigidBodyCI(0, motionState, colider->shape, btVector3(0, 0, 0));
		this->rigidBody = new btRigidBody(groundRigidBodyCI);
	}

	//Add rigid body to scene
	this->gameObject.lock()->scene.lock()->physicsWorld->addRigidBody(this->rigidBody);
}

void RigidBody::update(float delta){

	//Update position based on physics
	btTransform trans;
	this->rigidBody->getMotionState()->getWorldTransform(trans);
	
	//Update transform of this game object
	shared<Transform> transform = this->gameObject.lock()->getComponent<Transform>();
	transform->position = glm::vec3(trans.getOrigin().getX(), trans.getOrigin().getY(), trans.getOrigin().getZ());
}

void RigidBody::render(){
}

void RigidBody::destroy(){

	//Remove rigid body
	this->gameObject.lock()->scene.lock()->physicsWorld->removeRigidBody(this->rigidBody);

	//Delete rigid body
	delete this->rigidBody->getMotionState();
	delete this->rigidBody;
}