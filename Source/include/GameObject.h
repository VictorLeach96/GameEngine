#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include "internal/platform.h"

#include <sdl/SDL.h>
#include <vector>

class Component;
class Scene;

class GameObject : public enable_shared_from_this<GameObject>{
	
	friend class Scene;
	
public:
	
	weak<Scene> scene;
	
	weak<GameObject> parent;

	vector<shared<Component>> components;
	
public:
	
	template <typename T> shared<T> addComponent(){
		
		//Create component and add to list
		shared<T> component = make_shared<T>();
		component->gameObject = shared_from_this();
		this->components.push_back(component);
		return component;
	}

	template <typename T> shared<T> getComponent(){
	
		//Check each component
		for (int i=0; i < this->components.size(); i++){
			
			//Cast commponent to type
			shared<T> component = dynamic_pointer_cast<T>(this->components[i]);
		
			//Check whether component was found and return
			if (component){
				return component;
			}
		}
		return NULL;
	}

	template <typename T> vector<shared<T>> getComponents() {

		//Check each component
		vector<T> components = vector<T>();
		for (int i = 0; i < this->components.size(); i++) {

			//Cast commponent to type
			shared<T> component = dynamic_pointer_cast<T>(this->components[i]);

			//Check whether component was found and add to list
			if (component) {
				components.push_back(component);
			}
		}
		return components;
	}
	
	void awake();
	void update(float delta);
	void render();
	void destroy();

	void setParent(weak<GameObject> parent);
	weak<GameObject> getParent();
	
};

#endif