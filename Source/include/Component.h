#ifndef COMPONENT_H
#define COMPONENT_H

#include "internal/platform.h"

class GameObject;

class Component{
	
	friend class GameObject;
	
public:
	
	weak<GameObject> gameObject;
	
public:
	
	virtual void awake(){}
	virtual void update(float delta){}
	virtual void render(){}
	virtual void destroy(){}
	
};

#endif