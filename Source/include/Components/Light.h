#include "Component.h"

#include <glm/ext.hpp>

class Light: public Component{
	
public:
	
	Light(){
		
		//Set default colour and power
		this->colour = glm::vec3(0.5, 0.5, 0.5);
		this->power = 100.0f;
	}
	
	void awake();
	void update(float delta);
	void render();
	void destroy();

	glm::vec3 colour;
	float power;
};