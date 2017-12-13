#include "Material.h"

#include <sstream>
#include <fstream>
#include <iostream>
#include <vector>
#include <sdl_image/SDL_image.h>

void Material::awake() {
}

void Material::update(float delta) {
}

void Material::render() {
}

void Material::destroy() {
}

shared<Material> Material::loadFile(string file) {

	//Create material
	shared<Material> material = make_shared<Material>();

	//Setup buffers and streams
	ifstream stream;
	string buffer;

	//Loop through each line and make a string
	stream.open(file, ifstream::in);
	while (getline(stream, buffer)) {
		if (buffer != "" && buffer != " ") {

			//Feed each of the strings through the string loading method
			material->loadLine(buffer);
		}
	}

	//Close the file and compile the data
	stream.close();

	return material;
}

void Material::loadLine(string line) {

	//Seperate the given string contents by spaces and store in the `sections` vector
	string buffer;
	stringstream stream(line);
	vector<string> sections;
	while (stream >> buffer) {
		sections.push_back(buffer);
	}

	//Get prefix and remove it from the sections
	string prefix = sections[0];
	sections.erase(sections.begin());

	//Check each section of file
	if (prefix == "map_Kd") {
		
		//Load texture into SDL surface
		this->diffuseTexture = IMG_Load(sections[0].c_str());

	}else if (prefix == "map_Bump") {

		//Load texture into SDL surface
		this->normalTexture = IMG_Load(sections[0].c_str());

	}else if (prefix == "map_Ks") {

		//Load texture into SDL surface
		this->specularTexture = IMG_Load(sections[0].c_str());

	}else if (prefix == "Kd") {

		//Load XYZ co-ordinate positions
		float x = stof(sections[0]);
		float y = stof(sections[1]);
		float z = stof(sections[2]);

		//Save diffuse
		this->diffuse = glm::vec3(x, y, z);

	} else if (prefix == "Kd") {

		//Load XYZ co-ordinate positions
		float x = stof(sections[0]);
		float y = stof(sections[1]);
		float z = stof(sections[2]);

		//Save ambient
		this->ambient = glm::vec3(x, y, z);

	} else if (prefix == "Kd") {

		//Load XYZ co-ordinate positions
		float x = stof(sections[0]);
		float y = stof(sections[1]);
		float z = stof(sections[2]);

		//Save specular
		this->specular = glm::vec3(x, y, z);
	}
}

glm::vec3 Material::getDiffuse() {
	return this->diffuse;
}
glm::vec3 Material::getAmbient() {
	return this->ambient;
}
glm::vec3 Material::getSpecular() {
	return this->specular;
}

SDL_Surface* Material::getDiffuseTexture() {
	return this->diffuseTexture;
}
SDL_Surface* Material::getNormalTexture() {
	return this->normalTexture;
}
SDL_Surface* Material::getSpecularTexture() {
	return this->specularTexture;
}