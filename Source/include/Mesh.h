#include "internal/platform.h"

#include <glm/ext.hpp>
#include <vector>
#include <string>

class Mesh {

private:

	vector<glm::vec3> verticies;
	vector<glm::vec2> uvs;
	vector<glm::vec3> normals;

	vector<glm::vec3> faceVerticies;
	vector<glm::vec3> faceUvs;
	vector<glm::vec3> faceNormals;

	vector<glm::vec3> finalVerticies;
	vector<glm::vec2> finalUvs;
	vector<glm::vec3> finalNormals;
	vector<glm::vec3> finalTangents;
	vector<glm::vec3> finalBitangents;

	void loadLine(string line);
	void buildMesh();

public:

	Mesh() {}

	static shared<Mesh> loadFile(string file);

	vector<glm::vec3> getVerticies();
	vector<glm::vec2> getUvs();
	vector<glm::vec3> getNormals();
	vector<glm::vec3> getTangents();
	vector<glm::vec3> getBitangents();
};