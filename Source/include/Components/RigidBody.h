#include "Component.h"

#include <glm/ext.hpp>
#include <bullet/btBulletDynamicsCommon.h>

class RigidBody : public Component{
	
public:
	
	RigidBody() {
		this->mass = -1;
	}
	
	void awake();
	void update(float delta);
	void render();
	void destroy();

	btRigidBody* rigidBody;

	float mass;

};