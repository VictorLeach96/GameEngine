#include "internal/platform.h"
#include <GL/glew.h>
#include <map>
#include <string>

#include "Shaders/Shader.h"

class MeshRenderer;

class BasicShader : public Shader{
	
private:

	GLuint vaoId;
	GLuint vertexId;
	GLuint colourId;

	int size;

public:

	BasicShader() : Shader("shaders/Basic_Vertex.glsl", "shaders/Basic_Fragment.glsl") {}

	void awake(weak<MeshRenderer> renderer);
	void update(weak<MeshRenderer> renderer, float delta);
	void render(weak<MeshRenderer> renderer);
	void destroy(weak<MeshRenderer> renderer);
};