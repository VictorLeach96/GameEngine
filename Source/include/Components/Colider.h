#include "Component.h"

#include <glm/ext.hpp>
#include <bullet/btBulletDynamicsCommon.h>

class Mesh;

class Colider : public Component{

public:

	void awake();
	void update(float delta);
	void render();
	void destroy();

	btCollisionShape* shape;

	void setBox(glm::vec3 size);
	void setPlane(glm::vec3 size);
	void setSphere(float radius);
	void setMesh(shared<Mesh> mesh = nullptr);

};