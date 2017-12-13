#include <glm/ext.hpp>

#include "Component.h"

class Camera: public Component{
	
public:
	
	Camera(){
		
		//Create projection matrix
		this->projMatrix = glm::perspective(45.0f, 640.0f / 480.0f, 0.01f, 1000.0f);
	}
	
	void awake();
	void update(float delta);
	void render();
	void destroy();

	glm::mat4 projMatrix;
};