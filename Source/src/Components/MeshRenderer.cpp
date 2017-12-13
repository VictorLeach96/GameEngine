#include "Components/MeshRenderer.h"

#include "GameObject.h"
#include "Scene.h"

#include "Components/Camera.h"
#include "Components/Transform.h"

#include "Shaders/Shader.h"

void MeshRenderer::awake(){
	
	//Pass operation to shader
	if (!this->shader.expired()){
		this->shader.lock()->awake(shared_from_this());
	}
}

void MeshRenderer::update(float delta){

	//Pass operation to shader
	if (!this->shader.expired()) {
		this->shader.lock()->update(shared_from_this(), delta);
	}
}

void MeshRenderer::render(){

	//Pass operation to shader
	if (!this->shader.expired()) {

		//Bind shader
		this->shader.lock()->bind();

		//Collect mvp matrix items
		glm::mat4 projMatrix = this->gameObject.lock()->scene.lock()->camera->getComponent<Camera>()->projMatrix;
		glm::mat4 viewMatrix = this->gameObject.lock()->scene.lock()->camera->getComponent<Transform>()->matrix();
		glm::mat4 modelMatrix = this->gameObject.lock()->getComponent<Transform>()->matrix();

		//Update matrix locations with new values
		glUniformMatrix4fv(this->shader.lock()->getModelId(), 1, GL_FALSE, glm::value_ptr(modelMatrix));
		glUniformMatrix4fv(this->shader.lock()->getViewId(), 1, GL_FALSE, glm::value_ptr(viewMatrix));
		glUniformMatrix4fv(this->shader.lock()->getProjId(), 1, GL_FALSE, glm::value_ptr(projMatrix));

		//Draw mesh
		this->shader.lock()->render(shared_from_this());

		//Bind shader
		this->shader.lock()->unbind();
	}
}

void MeshRenderer::destroy(){

	//Pass operation to shader
	if (!this->shader.expired()) {
		this->shader.lock()->destroy(shared_from_this());
	}
}