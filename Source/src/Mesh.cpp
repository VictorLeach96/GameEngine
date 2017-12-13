#include "Mesh.h"

#include <sstream>
#include <fstream>

shared<Mesh> Mesh::loadFile(string file) {

	//Create new mesh
	shared<Mesh> mesh = make_shared<Mesh>();

	//Setup buffers and streams
	ifstream stream;
	string buffer;

	//Loop through each line and make a string
	stream.open(file, ifstream::in);
	while (getline(stream, buffer)) {
		if (buffer != "" && buffer != " ") {

			//Feed each of the strings through the string loading method
			mesh->loadLine(buffer);
		}
	}

	//Close the file and compile the data
	stream.close();

	//Build mesh objects
	mesh->buildMesh();
	
	return mesh;
}

void Mesh::loadLine(string line) {

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

	//Check the prefix of section and direct to pass it into the required load function
	if (prefix == "v") {

		//Load XYZ co-ordinate positions
		float x = stof(sections[0]);
		float y = stof(sections[1]);
		float z = stof(sections[2]);

		//Add vertex to list
		this->verticies.push_back(glm::vec3(x, y, z));

	}else if (prefix == "vt") {

		//Load XYZ co-ordinate positions
		float x = stof(sections[0]);
		float y = stof(sections[1]);

		//Add uv to list
		this->uvs.push_back(glm::vec2(x, y));

	} else if (prefix == "vn") {

		//Load XYZ co-ordinate positions
		float x = stof(sections[0]);
		float y = stof(sections[1]);
		float z = stof(sections[2]);

		//Add normal to list
		this->normals.push_back(glm::vec3(x, y, z));

	} else if (prefix == "f") {

		//Prepare destination for 
		glm::vec3 faceVertex;
		glm::vec3 faceUv;
		glm::vec3 faceNormal;

		//Split string using / into a vector

		//Split and add X position
		string buffer;
		stringstream stream(sections[0]);
		vector<string> subsections;
		while (getline(stream, buffer, '/')) {
			subsections.push_back(buffer);
		}

		//Set each vector value of the face
		faceVertex.x = stoi(subsections[0]);
		faceUv.x = stoi(subsections[1]);
		faceNormal.x = stoi(subsections[2]);

		//Split and add Y position
		stringstream stream2(sections[1]);
		subsections.clear();
		while (getline(stream2, buffer, '/')) {
			subsections.push_back(buffer);
		}

		//Set each vector value of the face
		faceVertex.y = stoi(subsections[0]);
		faceUv.y = stoi(subsections[1]);
		faceNormal.y = stoi(subsections[2]);

		//Split and add Z position
		stringstream stream3(sections[2]);
		subsections.clear();
		while (getline(stream3, buffer, '/')) {
			subsections.push_back(buffer);
		}

		//Set each vector value of the face
		faceVertex.z = stoi(subsections[0]);
		faceUv.z = stoi(subsections[1]);
		faceNormal.z = stoi(subsections[2]);

		//Add each to list
		this->faceVerticies.push_back(faceVertex);
		this->faceUvs.push_back(faceUv);
		this->faceNormals.push_back(faceNormal);
	}
}

void Mesh::buildMesh() {

	//Clear all vbos first
	this->finalVerticies.clear();
	this->finalUvs.clear();
	this->finalNormals.clear();

	//Loop through each face and pick out verticies
	for (int i = 0; i < this->faceVerticies.size(); i++) {
		glm::vec3 face = this->faceVerticies[i];

		//Lookup each vertex index
		this->finalVerticies.push_back(this->verticies[face.x - 1]);
		this->finalVerticies.push_back(this->verticies[face.y - 1]);
		this->finalVerticies.push_back(this->verticies[face.z - 1]);
	}

	//Loop through each face and pick out uv
	for (int i = 0; i < this->faceUvs.size(); i++) {
		glm::vec3 face = this->faceUvs[i];

		//Lookup each uv index
		//We ues 1.0f- to invert the texture to correct the orientation caused by SDL IMG_LOAD function
		this->finalUvs.push_back(glm::vec2(this->uvs[face.x - 1].x, 1.0f - this->uvs[face.x - 1].y));
		this->finalUvs.push_back(glm::vec2(this->uvs[face.y - 1].x, 1.0f - this->uvs[face.y - 1].y));
		this->finalUvs.push_back(glm::vec2(this->uvs[face.z - 1].x, 1.0f - this->uvs[face.z - 1].y));
	}

	//Loop through each face and pick out normal
	for (int i = 0; i < this->faceNormals.size(); i++) {
		glm::vec3 face = this->faceNormals[i];

		//Lookup each normal index
		this->finalNormals.push_back(this->normals[face.x - 1]);
		this->finalNormals.push_back(this->normals[face.y - 1]);
		this->finalNormals.push_back(this->normals[face.z - 1]);
	}

	//Loop through each vertex and calculate its tangent and bitangent data
	for (int i = 0; i < this->finalVerticies.size(); i += 3){

		//Calculate the delta vertex position
		glm::vec3 deltaVertex1 = this->finalVerticies[i + 1] - this->finalVerticies[i + 0];
		glm::vec3 deltaVertex2 = this->finalVerticies[i + 2] - this->finalVerticies[i + 0];

		//Calculate the delta uv position
		glm::vec2 deltaUV1 = this->finalUvs[i + 1] - this->finalUvs[i + 0];
		glm::vec2 deltaUV2 = this->finalUvs[i + 2] - this->finalUvs[i + 0];

		//Calculate tangent and bittangent
		float r = 1.0f / (deltaUV1.x * deltaUV2.y - deltaUV1.y * deltaUV2.x);
		glm::vec3 tangent = (deltaVertex1 * deltaUV2.y - deltaVertex2 * deltaUV1.y) * r;
		glm::vec3 bitangent = (deltaVertex2 * deltaUV1.x - deltaVertex1 * deltaUV2.x) * r;

		//Add tangents to data
		this->finalTangents.push_back(tangent);
		this->finalTangents.push_back(tangent);
		this->finalTangents.push_back(tangent);

		//Add bitangents to data
		this->finalBitangents.push_back(bitangent);
		this->finalBitangents.push_back(bitangent);
		this->finalBitangents.push_back(bitangent);
	}
}

vector<glm::vec3> Mesh::getVerticies() {
	return this->finalVerticies;
}
vector<glm::vec2> Mesh::getUvs() {
	return this->finalUvs;
}
vector<glm::vec3> Mesh::getNormals() {
	return this->finalNormals;
}
vector<glm::vec3> Mesh::getTangents() {
	return this->finalTangents;
}
vector<glm::vec3> Mesh::getBitangents() {
	return this->finalBitangents;
}