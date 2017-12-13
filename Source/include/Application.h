#ifndef APPLICATION_H
#define APPLICATION_H

#include "internal/platform.h"
#include <GL/glew.h>
#include <sdl/SDL.h>

class Application{
	
private:
	
	SDL_GLContext context;
	SDL_Window* window;
	SDL_Renderer* renderer;
	
	bool running;
	
public:

	void init(int argc, char* argv[]);
	void loop();
	void quit();
	void destroy();
	
	Application(){
		this->running = false;
	}
	
	~Application(){}
	
};

#endif