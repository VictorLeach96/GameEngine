#include "Application.h"

#include "internal/platform.h"
#include <sdl/SDL.h>

#undef main

int main(int argc, char* argv[]){
	
	Application* app = new Application();
	app->init(argc, argv);
	app->loop();
	app->destroy();
	
    return 0;
}