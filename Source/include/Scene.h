#include "internal/platform.h"

#include <sdl/SDL.h>
#include <vector>
#include <bullet/btBulletDynamicsCommon.h>

class Camera;
class Transform;
class GameObject;

class Scene : public enable_shared_from_this<Scene>{
	
public:
	
	vector<shared<GameObject>> gameObjects;
	
	shared<GameObject> camera;
	
	btDiscreteDynamicsWorld* physicsWorld;

	btBroadphaseInterface* broadphase;
	btSequentialImpulseConstraintSolver* solver;
	btDefaultCollisionConfiguration* collisionConfiguration;
	btCollisionDispatcher* dispatcher;

	template <typename T> shared<T> addGameObject(){
		
		//Create game object and add to list
		shared<T> gameObject = make_shared<GameObject>();
		gameObject->scene = shared_from_this();
		this->gameObjects.push_back(gameObject);
		return gameObject;
	}

	void setup();
	void setupPhysics();
	
	void awake();
	void update(float delta);
	void render();
	void destroy();
	
};