#include "Scene.h"
#include "GameObject.h"

#include <cstddef>
#include <iostream>

#include "GameObject.h"
#include "Mesh.h"
#include "Material.h"

#include "Components/Camera.h"
#include "Components/Transform.h"
#include "Components/Input.h"
#include "Components/Movement.h"
#include "Components/MeshRenderer.h"
#include "Components/Light.h"
#include "Components/Colider.h"
#include "Components/RigidBody.h"

#include "Shaders/Shader.h"
#include "Shaders/BasicShader.h"
#include "Shaders/AdvancedShader.h"

void Scene::setup() {

	//Create camera
	this->camera = this->addGameObject<GameObject>();
	this->camera->addComponent<Transform>();
	this->camera->addComponent<Camera>();
	this->camera->addComponent<Input>();
	this->camera->addComponent<Movement>();

	this->camera->getComponent<Transform>()->position = glm::vec3(0.0f, -10.0f, -20.0f);
	this->camera->getComponent<Transform>()->rotation = glm::vec3(20.0f, 0.0f, 0.0f);

	//Create bottom box
	shared<GameObject> box = this->addGameObject<GameObject>();
	box->addComponent<Transform>();
	box->addComponent<MeshRenderer>();
	box->addComponent<Colider>();
	box->addComponent<RigidBody>();

	box->getComponent<Transform>()->position = glm::vec3(0, 4.0f, -20.0f);
	box->getComponent<Transform>()->rotation = glm::vec3(0, 0, 0);
	
	box->getComponent<MeshRenderer>()->material = Material::loadFile("models/box/Box.mtl");
	box->getComponent<MeshRenderer>()->mesh = Mesh::loadFile("models/box/BoxSmall.obj");
	box->getComponent<MeshRenderer>()->shader = Shader::getShader<AdvancedShader>();

	box->getComponent<Colider>()->setMesh(box->getComponent<MeshRenderer>()->mesh);
	box->getComponent<RigidBody>()->mass = 1.0f;

	//Create top box (child of bottom box)
	shared<GameObject> box2 = this->addGameObject<GameObject>();
	box2->addComponent<Transform>();
	box2->addComponent<MeshRenderer>();
	box2->setParent(box);
	
	box2->getComponent<Transform>()->position = glm::vec3(0, 10.0f, 0.0f);
	box2->getComponent<Transform>()->rotation = glm::vec3(0, 0, 0);

	box2->getComponent<MeshRenderer>()->material = box->getComponent<MeshRenderer>()->material;
	box2->getComponent<MeshRenderer>()->mesh = box->getComponent<MeshRenderer>()->mesh;
	box2->getComponent<MeshRenderer>()->shader = Shader::getShader<AdvancedShader>();

	//Create light
	shared<GameObject> light = this->addGameObject<GameObject>();
	light->addComponent<Transform>();
	light->addComponent<Light>();

	light->getComponent<Transform>()->position = glm::vec3(0.0f, 10.0f, 5.0f);

	light->getComponent<Light>()->power = 1000.0f;

	//Create plane
	shared<GameObject> plane = this->addGameObject<GameObject>();
	plane->addComponent<Transform>();
	plane->addComponent<MeshRenderer>();
	plane->addComponent<Colider>();
	plane->addComponent<RigidBody>();

	plane->getComponent<Transform>()->position = glm::vec3(0.0f, -10.0f, -5.0f);
	plane->getComponent<Transform>()->rotation = glm::vec3(0, 0, 0);
	
	plane->getComponent<MeshRenderer>()->mesh = Mesh::loadFile("models/plane/plane.obj");
	plane->getComponent<MeshRenderer>()->shader = Shader::getShader<BasicShader>();
	plane->getComponent<MeshRenderer>()->colour = make_shared<glm::vec3>(glm::vec3(0.11f, 0.56f, 1.0f));

	plane->getComponent<Colider>()->setMesh(plane->getComponent<MeshRenderer>()->mesh);
}

void Scene::setupPhysics() {

	//Setup physics configuration objects
	this->broadphase = new btDbvtBroadphase();
	this->solver = new btSequentialImpulseConstraintSolver;
	this->collisionConfiguration = new btDefaultCollisionConfiguration();
	this->dispatcher = new btCollisionDispatcher(collisionConfiguration);

	//Create physics world with gravity
	this->physicsWorld = new btDiscreteDynamicsWorld(dispatcher, broadphase, solver, collisionConfiguration);
	this->physicsWorld->setGravity(btVector3(0, -10, 0));
}

void Scene::awake(){
	
	//Update each game object
	for (int i=0; i < this->gameObjects.size(); i++){
		this->gameObjects[i]->awake();
	}
}

void Scene::update(float delta) {

	//Update each game object
	for (int i = 0; i < this->gameObjects.size(); i++) {
		this->gameObjects[i]->update(delta);
	}

	//Update physics world last
	try {
		this->physicsWorld->stepSimulation(delta, 10);
	} catch (...) {
		cout << "Error occured calculating physics step" << endl;
	}
}

void Scene::render(){
	
	//Update each game object
	for (int i=0; i < this->gameObjects.size(); i++){
		this->gameObjects[i]->render();
	}
}

void Scene::destroy(){
	
	//Update each game object
	for (int i=0; i < this->gameObjects.size(); i++){
		this->gameObjects[i]->destroy();
	}

	//Remove physics objects
	delete this->physicsWorld;
	delete this->solver;
	delete this->collisionConfiguration;
	delete this->dispatcher;
	delete this->broadphase;
}