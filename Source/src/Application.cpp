#include "internal/platform.h"
#include <iostream>

#include "Application.h"
#include "Scene.h"

#include "Components/Input.h"

#include "Shaders/Shader.h"
#include "Shaders/BasicShader.h"
#include "Shaders/AdvancedShader.h"

void Application::init(int argc, char* argv[]){
	
	//Setup SDL video
	if (SDL_Init(SDL_INIT_VIDEO) < 0){
		cerr << "SDL Initialization failed!" << endl;
		return;
	}

	//Setup SDL attributes and versions
	//SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
	//SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
	//SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

	//Attach renderer and context to window
	this->window = SDL_CreateWindow("Game Thingy", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 840, 840, SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL);
	this->renderer = SDL_CreateRenderer(this->window, -1, 0);
	this->context = SDL_GL_CreateContext(this->window);

	//OpenGL options
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);

	//Setup glew
	glewExperimental = GL_TRUE;
	GLenum err = glewInit();
	if(GLEW_OK != err){
		cerr << "Glew Initializatoin failed!" << std::endl << glewGetErrorString(err) << endl;
		return;
	}
	
	this->running = true;
}

void Application::loop(){
	
	//Create shaders
	Shader::addShader<BasicShader>();
	Shader::addShader<AdvancedShader>();

	//Create scene
	shared<Scene> scene = make_shared<Scene>();
	scene->setup();
	scene->setupPhysics();
	scene->awake();
	
	//Execute the game loop
	int lastTick = SDL_GetTicks();
	while(this->running){
		
		//Calculate delta time
		unsigned int currentTick = SDL_GetTicks();
		float deltaTime = (float) (currentTick - lastTick) / 1000.0f;
		lastTick = currentTick;

		//Clear the frame buffer to black
		glClearColor(0.0f,0.0f,0.0f,0.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		
		//Poll events
		if (Input::poll()) {
			this->running = false;
		}
		
		//Update scene and render
		scene->update(deltaTime);
		scene->render();
		
		//Double buffering
		SDL_GL_SwapWindow(window);
		
		//Limit the fps if its running too high
		if(deltaTime < (1.0f/50.0f)) {
			SDL_Delay((unsigned int) (((1.0f/50.0f) - deltaTime)*1000.0f) );
		}
	}
	
	//Destroy scene
	scene->destroy();
}

void Application::quit(){
	this->running = false;
}

void Application::destroy(){

	//Cleanup and quit SDL
	SDL_GL_DeleteContext(this->context);
	SDL_DestroyWindow(this->window);
	SDL_Quit();
}