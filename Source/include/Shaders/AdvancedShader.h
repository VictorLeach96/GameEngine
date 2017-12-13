#include "internal/platform.h"

#include <GL/glew.h>
#include <map>
#include <string>

#include "Shaders/Shader.h"

class MeshRenderer;

class AdvancedShader : public Shader{
	
private:

	GLuint vaoId;
	GLuint verticiesId;
	GLuint uvsId;
	GLuint normalsId;
	GLuint tangentsId;
	GLuint bitangentsId;

	GLuint diffuseTexture;
	GLuint diffuseTextureId;

	GLuint normalTexture;
	GLuint normalTextureId;

	GLuint specularTexture;
	GLuint specularTextureId;

	GLuint lightPosId;
	GLuint lightColourId;
	GLuint lightPowerId;

	GLuint diffuseId;
	GLuint specularId;
	GLuint ambientId;

	int size;

public:

	AdvancedShader() : Shader("shaders/Advanced_Vertex.glsl", "shaders/Advanced_Fragment.glsl") {}

	void awake(weak<MeshRenderer> renderer);
	void update(weak<MeshRenderer> renderer, float delta);
	void render(weak<MeshRenderer> renderer);
	void destroy(weak<MeshRenderer> renderer);
};