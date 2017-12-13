#include "Component.h"

class Movement : public Component {

public:

	Movement() {
		this->walkSpeed = 20.0f;
		this->rotateSpeed = 50.0f;
	}

	void awake();
	void update(float delta);
	void render();
	void destroy();

	float walkSpeed;
	float rotateSpeed;

};