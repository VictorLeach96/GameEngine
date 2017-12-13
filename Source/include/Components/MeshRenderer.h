#include <GL/glew.h>
#include <glm/ext.hpp>

#include "Component.h"

class Mesh;
class Material;
class Shader;

class MeshRenderer : public Component, public enable_shared_from_this<MeshRenderer>{
	
private:

	GLuint vaoId;
	GLuint vertexId;
	GLuint uvId;
	
	GLuint projId;
	GLuint viewId;
	GLuint modelId;
	
	int size;

public:

	void awake();
	void update(float delta);
	void render();
	void destroy();
	
	weak<Shader> shader;

	shared<Mesh> mesh;
	shared<Material> material;
	shared<glm::vec3> colour;

};