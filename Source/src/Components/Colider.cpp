#include "Components/Colider.h"

#include <iostream>

#include "Mesh.h"
#include "GameObject.h"

#include "Components/MeshRenderer.h"

void Colider::awake(){
}

void Colider::update(float delta){
}

void Colider::render(){
}

void Colider::destroy(){

	//Remove shape if found
	if (this->shape != NULL) {
		delete this->shape;
	}
}

void Colider::setBox(glm::vec3 size) {
	this->shape = new btBoxShape(btVector3(size.x, size.y, size.z));
}

void Colider::setPlane(glm::vec3 size) {
	this->shape = new btStaticPlaneShape(btVector3(size.x, size.y, size.z), 1.0f);
}

void Colider::setSphere(float radius) {
	this->shape = new btSphereShape(radius);
}

void Colider::setMesh(shared<Mesh> mesh){
	btConvexHullShape* shape = new btConvexHullShape();

	//Get mesh from gameobject
	vector<glm::vec3> points;
	if (mesh == nullptr || mesh.get() == nullptr) {

		//Find mesh renderer
		shared<MeshRenderer> renderer = this->gameObject.lock()->getComponent<MeshRenderer>();

		//Check game object has transform
		if (renderer.get() == nullptr) {
			cerr << "Colider: Could not find mesh renderer on gameobject" << endl;
		} else {
			points = this->gameObject.lock()->getComponent<MeshRenderer>()->mesh->getVerticies();
		}

	}else{
		points = mesh->getVerticies();
	}

	//Add points from mesh
	for (int i = 0; i < points.size(); i++) {
		shape->addPoint(btVector3(points[i].x, points[i].y, points[i].z));
	}

	this->shape = shape;
}