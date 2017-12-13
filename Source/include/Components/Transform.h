#include <sdl/SDL.h>
#include <glm/ext.hpp>

#include "Component.h"

class Transform: public Component{
	
public:

	Transform() {
		this->position = glm::vec3();
		this->rotation = glm::vec3();
	}

	void awake();
	void update(float delta);
	void render();
	void destroy();

	glm::vec3 position;
	glm::vec3 rotation;
	
	glm::mat4 matrix();
	glm::vec3 forwards();

	void moveFowards(float delta, float amount);
	void moveBackwards(float delta, float amount);

};