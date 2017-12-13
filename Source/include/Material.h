#include "internal/platform.h"

#include <GL/glew.h>
#include <sdl/SDL.h>
#include <glm/glm.hpp>
#include <string>

class Material{

private:

	void loadLine(string line);
	
	glm::vec3 diffuse;
	glm::vec3 ambient;
	glm::vec3 specular;

	SDL_Surface* diffuseTexture;
	SDL_Surface* normalTexture;
	SDL_Surface* specularTexture;

public:

	Material() {};

	static shared<Material> loadFile(string file);

	void awake();
	void update(float delta);
	void render();
	void destroy();

	glm::vec3 getDiffuse();
	glm::vec3 getAmbient();
	glm::vec3 getSpecular();

	SDL_Surface* getDiffuseTexture();
	SDL_Surface* getNormalTexture();
	SDL_Surface* getSpecularTexture();
};