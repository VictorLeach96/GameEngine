#ifndef SHADER_H
#define SHADER_H

#include "internal/platform.h"

#include <GL/glew.h>
#include <sdl\SDL.h>
#include <vector>
#include <string>

class MeshRenderer;

class Shader{
	
private:

	GLuint programId;
	GLuint vertexShaderId;
	GLuint fragmentShaderId;

	GLuint projId;
	GLuint viewId;
	GLuint modelId;
	GLuint diffuseId;
	
	string vertexShader;
	string fragmentShader;

	static vector<shared<Shader>> shaders;

protected:

	Shader(string vertex, string fragment) {
		this->loadVertexShader(vertex);
		this->loadFragmentShader(fragment);
		this->buildShader();
		this->checkShader();
	}

	GLuint loadTexture(SDL_Surface* surface);

	void loadVertexShader(string file);
	void loadFragmentShader(string file);
	void buildShader();
	void checkShader();

public:

	virtual void awake(weak<MeshRenderer> renderer) {}
	virtual void update(weak<MeshRenderer> renderer, float delta) {}
	virtual void render(weak<MeshRenderer> renderer) {}
	virtual void destroy(weak<MeshRenderer> renderer) {}

	void bind() { glUseProgram(this->programId); }
	void unbind() { glUseProgram(0); }

	template <typename T> static shared<T> addShader() {

		//Create shader and add to list
		shared<T> shader = make_shared<T>();
		Shader::shaders.push_back(shader);
		return shader;
	}

	template <typename T> static shared<T> getShader() {

		//Check each shader
		for (int i = 0; i < Shader::shaders.size(); i++) {

			//Cast shader to type
			shared<T> shader = dynamic_pointer_cast<T>(Shader::shaders[i]);

			//Check whether shader was found and return
			if (shader) {
				return shader;
			}
		}
		return NULL;
	}

	GLuint getProgramId();

	GLuint getProjId();
	GLuint getViewId();
	GLuint getModelId();
};

#endif