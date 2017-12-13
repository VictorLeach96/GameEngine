#include <fstream>
#include <sstream>
#include <iostream>

#include "Shaders/Shader.h"

vector<shared<Shader>> Shader::shaders = vector<shared<Shader>>();

GLuint Shader::getProgramId() {
	return this->programId;
}

GLuint Shader::getProjId() {
	return this->projId;
}

GLuint Shader::getViewId() {
	return this->viewId;
}

GLuint Shader::getModelId() {
	return this->modelId;
}

void Shader::loadVertexShader(string file) {

	//Setup file and string streams
	ifstream stream;
	string buffer;
	string output;

	//Loop through each line and make a string
	stream.open(file, std::ifstream::in);
	while (getline(stream, buffer)){
		output.append(buffer + '\n');
	}

	//Close the file and return
	stream.close();

	//Assign shader
	this->vertexShader = output;
}
void Shader::loadFragmentShader(string file) {

	//Setup file and string streams
	ifstream stream;
	string buffer;
	string output;

	//Loop through each line and make a string
	stream.open(file, std::ifstream::in);
	while (getline(stream, buffer)) {
		output.append(buffer + '\n');
	}

	//Close the file and return
	stream.close();

	//Assign shader
	this->fragmentShader = output;
}

void Shader::buildShader(){

	//Convert shaders to char
	const char *vertexShaderData = this->vertexShader.c_str();
	const char *fragmentShaderData = this->fragmentShader.c_str();

	//Create vertex shader
	this->vertexShaderId = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(this->vertexShaderId, 1, &vertexShaderData, NULL);
	glCompileShader(this->vertexShaderId);

	//Create fragment shader
	this->fragmentShaderId = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(this->fragmentShaderId, 1, &fragmentShaderData, NULL);
	glCompileShader(this->fragmentShaderId);

	//Create shader program
	this->programId = glCreateProgram();
	glAttachShader(this->programId, this->vertexShaderId);
	glAttachShader(this->programId, this->fragmentShaderId);
	glLinkProgram(this->programId);

	//Create shader uniform locations
	this->modelId = glGetUniformLocation(this->programId, "uModelMat");
	this->viewId = glGetUniformLocation(this->programId, "uViewMat");
	this->projId = glGetUniformLocation(this->programId, "uProjMat");
}

void Shader::checkShader() {
	GLint compiled;

	//Check whether vertex shader failed to compile
	glGetShaderiv(this->vertexShaderId, GL_COMPILE_STATUS, &compiled);
	if (!compiled) {
		GLsizei len;
		glGetShaderiv(this->vertexShaderId, GL_INFO_LOG_LENGTH, &len);
		GLchar* log = new GLchar[len + 1];
		glGetShaderInfoLog(this->vertexShaderId, len, &len, log);
		cerr << "Vertex Shader: compilation failed,  " << log << endl;
		delete[] log;
	}

	//Check whether fragment shader failed to compile
	glGetShaderiv(this->fragmentShaderId, GL_COMPILE_STATUS, &compiled);
	if (!compiled) {
		GLsizei len;
		glGetShaderiv(this->fragmentShaderId, GL_INFO_LOG_LENGTH, &len);
		GLchar* log = new GLchar[len + 1];
		glGetShaderInfoLog(this->fragmentShaderId, len, &len, log);
		cerr << "Fragment Shader: compilation failed,  " << log << endl;
		delete[] log;
	}
}

GLuint Shader::loadTexture(SDL_Surface* surface){

	//Setup the temporary buffer for texture
	GLuint texture = 0;
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);

	//Check the format and channel values for the surface
	int textureMode = GL_BGR;

	//Texture has an alpha channel
	if (surface->format->BytesPerPixel == 4) {

		//Check the order of alpha channels
		if (surface->format->Rmask == 0x000000ff) {
			textureMode = GL_RGBA;
		}
		else {
			textureMode = GL_BGRA;
		}

	}
	else if (surface->format->BytesPerPixel == 3) {
		//Texture doesn't have an alpha channel

		//Check the order of alpha channels
		if (surface->format->Rmask == 0x000000ff) {
			textureMode = GL_RGB;
		}
		else {
			textureMode = GL_BGR;
		}
	}

	//Generate the texture
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, surface->w, surface->h, 0, textureMode, GL_UNSIGNED_BYTE, surface->pixels);

	//Set texture parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	//Generate mipmaps
	glGenerateMipmap(GL_TEXTURE_2D);

	//Unbind texture
	glBindTexture(GL_TEXTURE_2D, 0);

	return texture;
}