#include "Model.hpp"
#include "../vendors/lib.h"

using namespace std;

Model::Model() { }

Model::Model(string filePath)
{
	this->filePath = filePath;
}

Model::~Model() { }

void Model::loadModel()
{
	ifstream	file(this->filePath);
	string		line;

	if (!file.is_open()) {
		cout << "loadModel: Unable to open file: " << this->filePath << endl;
		return ;
	}
	while (getline(file, line))
		this->parseLine(line);
	file.close();
	this->normalizeVertices();
}

void Model::parseLine(string line)
{
	if (line[0] == 'v' && line[1] == ' ') {
		this->parseV(line);
	}
	else if (line[0] == 'f' && line[1] == ' ') {
		this->parseF(line);
	}
	else if (line[0] == 'm' && line[1] == 't' && line[2] == 'l' && line[3] == 'l' && line[4] == 'i' && line[5] == 'b') {
		this->parseMtlLib(line);
	}
	else if (line[0] == 'u' && line[1] == 's' && line[2] == 'e' && line[3] == 'm' && line[4] == 't' && line[5] == 'l') {
		this->parseMtlName(line);
	}
	else if (line[0] == 's' && line[1] == ' ') {
		this->parseSmoothing(line);
	}
	else if (line[0] == 'o' && line[1] == ' ') {
		this->parseObjectName(line);
	} else if (line[0] == 'v' && line[1] == 'n') {
		this->parseVN(line);
	} else if (line[0] == 'v' && line[1] == 't') {
		this->parseVT(line);
	}
}

// Parse the vertices (v) from the .obj file
void Model::parseV(string line)
{
	vector<float> vertex;
	stringstream ss(line);
	string word;
	float value;

	ss >> word;
	while (ss >> value) {
		vertex.push_back(value);
	}
	this->vertices.push_back(vertex);
}

// Parse the texture coordinates (vt) from the .obj file
void Model::parseVT(string line)
{
	vector<float> vertex;
	stringstream ss(line);
	string word;
	float value;

	ss >> word;
	while (ss >> value) {
		vertex.push_back(value);
	}
	this->verticeTextCoords.push_back(vertex);
}

// Parse the vertex normals (vn) from the .obj file
void Model::parseVN(string line)
{
	vector<float> vertex;
	stringstream ss(line);
	string word;
	float value;

	ss >> word;
	while (ss >> value) {
		vertex.push_back(value);
	}
	this->verticeNormals.push_back(vertex);
}

// Parse the face elements (f) from the .obj file
void Model::parseF(string line)
{

	vector<FaceVertex>		face;
	istringstream			iss(line);
	string					token;

	// need to be able to parse the faces that are in the format "f 1/1/1 2/2/2 3/3/3 4/4/4"
	// and the ones that are in the format "f 1 2 3 4"

	while (iss >> token) {
		if (token == "f")
			continue;		
		FaceVertex faceVertex;

		// If the face is in the format "f 1/1/1 2/2/2 3/3/3 4/4/4"
		if (token.find("/") != string::npos) {
			istringstream faceVertexStream(token);
			string faceVertexToken;
			int i = 0;
			while (getline(faceVertexStream, faceVertexToken, '/')) {
				if (faceVertexToken.empty()) {
					i++;
					continue;
				}
				if (i == 0)
					faceVertex.vertexIndex = stoi(faceVertexToken);
				else if (i == 1)
					faceVertex.textureIndex = stoi(faceVertexToken);
				else if (i == 2)
					faceVertex.normalIndex = stoi(faceVertexToken);
				i++;
			}
		}
		// If the face is in the format "f 1 2 3 4"
		else {
			faceVertex.vertexIndex = stoi(token);
			faceVertex.normalIndex = 0;
			faceVertex.textureIndex = 0;
		}
		face.push_back(faceVertex);
	}

	// Triangulate the face if it has 4 vertices (quad)
	if (face.size() == 4) {
		vector<FaceVertex> newFace1 = { face[0], face[1], face[2] };
		vector<FaceVertex> newFace2 = { face[2], face[3], face[0] };
		this->faces.push_back(newFace1);
		this->faces.push_back(newFace2);
	}
	else
		this->faces.push_back(face);
}

void Model::parseMtlLib(string line)
{
	stringstream ss(line);
	string word;
	string value;

	ss >> word;
	ss >> value;
	this->mtlLib = value;
}

void Model::parseMtlName(string line)
{
	stringstream ss(line);
	string word;
	string value;

	ss >> word;
	ss >> value;
}

void Model::parseSmoothing(string line)
{
	stringstream ss(line);
	string word;
	string value;

	ss >> word;
	ss >> value;
	this->smoothing = value;
}

void Model::parseObjectName(string line)
{
	stringstream ss(line);
	string word;
	string value;

	ss >> word;
	ss >> value;
	this->modelName = value;
}

// Rotate the model by specified angles around the X, Y, and Z axes.
void Model::Rotate(float angle, float dirX, float dirY, float dirZ)
{
	this->rotationMatrix = this->rotationMatrix.rotate(angle, dirX, dirY, dirZ);
}

// Translate (move) the model by specified offsets in the X, Y, and Z directions.
void Model::Translate(float offsetX, float offsetY, float offsetZ)
{
	this->translationMatrix.translate(Vec3(offsetX, offsetY, offsetZ));
}

// Scale the model uniformly by a specified factor.
void Model::Scale(float scale)
{
	this->scaleMatrix.scale(Vec3(scale, scale, scale));
}

Mat4 Model::createFinalMatrix()
{
	// Create final transformation matrix
	Mat4 finalMatrix = Mat4();
	finalMatrix = finalMatrix * rotationMatrix;
	finalMatrix = finalMatrix * scaleMatrix;
	finalMatrix = finalMatrix * translationMatrix;
	return finalMatrix;
}

void	Model::normalizeVertices() {
	float minX = 0;
	float minY = 0;
	float minZ = 0;
	float maxX = 0;
	float maxY = 0;
	float maxZ = 0;

	for (auto& vertex : this->vertices) {
		if (vertex[0] < minX)
			minX = vertex[0];
		if (vertex[1] < minY)
			minY = vertex[1];
		if (vertex[2] < minZ)
			minZ = vertex[2];
		if (vertex[0] > maxX)
			maxX = vertex[0];
		if (vertex[1] > maxY)
			maxY = vertex[1];
		if (vertex[2] > maxZ)
			maxZ = vertex[2];
	}
	float x = (maxX + minX) / 2;
	float y = (maxY + minY) / 2;
	float z = (maxZ + minZ) / 2;
	float max = maxX - minX;
	if (max < maxY - minY)
		max = maxY - minY;
	if (max < maxZ - minZ)
		max = maxZ - minZ;
	for (auto& vertex : this->vertices) {
		vertex[0] = (vertex[0] - x) / max;
		vertex[1] = (vertex[1] - y) / max;
		vertex[2] = (vertex[2] - z) / max;
	}

}

float*	Model::transformVertices() {
	float* vertices = new float[this->vertices.size() * currMode];
	int i = 0;

	for (auto& vertex : this->vertices) {
		vertices[i] = vertex[0];
		vertices[i + 1] = vertex[1];
		vertices[i + 2] = vertex[2];
		// cout << "Vertex: " << vertex.size() << endl;
		if (vertex.size() == 6 ) {
			vertices[i + 3] = vertex[3];
			vertices[i + 4] = vertex[4];
			vertices[i + 5] = vertex[5];
			i += 6;
		}
		else if (vertex.size() == 5) {
			vertices[i + 3] = vertex[3];
			vertices[i + 4] = vertex[4];
			vertices[i + 5] = vertex[5];
			vertices[i + 6] = vertex[6];
			i += 5;
		}
		else if (vertex.size() == 8) {
			vertices[i + 3] = vertex[3];
			vertices[i + 4] = vertex[4];
			vertices[i + 5] = vertex[5];
			vertices[i + 6] = vertex[6];
			vertices[i + 7] = vertex[7];
			i += 8;
		}
		else {
			i += 3;
		}
	}
	return vertices;
}

int*	Model::transformFaces() {
	int* faces = new int[this->faces.size() * 3];
	int i = 0;
	for (auto& face : this->faces) {
		faces[i] = face[0].vertexIndex - 1;
		faces[i + 1] = face[1].vertexIndex - 1;
		faces[i + 2] = face[2].vertexIndex - 1;
		i += 3;
	}
	return faces;
}

float randomFloat() {
	return static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
}

void Model::setVertices(int mode)
{
	vector<vector<float>> newVertices;

	if (mode == NO_COLOR_MODE) {
		for (int i = 0; i < this->vertices.size(); i++) {
			vector<float> vertex = this->vertices[i];
			vertex.erase(vertex.begin() + 3, vertex.end());
			newVertices.push_back(vertex);
		}
		this->currMode = NO_COLOR_MODE;
		this->vertices = newVertices;
		setupBuffers();
	}
	else if (mode == RAND_COLOR_MODE) {
		for (int i = 0; i < this->vertices.size(); i++) {
			vector<float> vertex = this->vertices[i];
			// Replace / Insert the color values at the end of the vertex / at the 3rd index
			vertex.erase(vertex.begin() + 3, vertex.end());
	
			vertex.push_back(randomFloat());
			vertex.push_back(randomFloat());
			vertex.push_back(randomFloat());

			newVertices.push_back(vertex);
		}
		this->currMode = RAND_COLOR_MODE;
		this->vertices = newVertices;
		setupBuffers();
	}
	else if (mode == TEXTURE_MODE) {
		// Keep 3 vertices for each vertex
		for (int i = 0; i < this->vertices.size(); i++) {
			vector<float> vertex = this->vertices[i];
			if (vertex.size() != 3) {
				vertex.erase(vertex.begin() + 3, vertex.end());
			}
			vertex.push_back(randomFloat());
			vertex.push_back(randomFloat());
			vertex.push_back(randomFloat());

			// if we have parsed the texture coordinates, we can use them to map the texture to the model
			// if (this->verticeTextCoords.size() > 0) {
			// 	vector<float> textCoords = this->verticeTextCoords[i];
			// 	vertex.push_back(textCoords[0]);
			// 	vertex.push_back(textCoords[1]);
			// }
			// else {
				float t = atan2(vertex[2], vertex[0]);
				float p = acos(vertex[1] / sqrt(pow(vertex[0], 2) + pow(vertex[1], 2) + pow(vertex[2], 2)));
				vertex.push_back((t + M_PI) / (2.f * M_PI));
				vertex.push_back(p / M_PI);
			// }
			newVertices.push_back(vertex);
		}
		this->currMode = TEXTURE_MODE;
		this->vertices = newVertices;
		setupBuffers();
	}
}

void Model::loadTexture(const char* path) {
	this->texture.loadTexture(path);
}

void Model::setupBuffers() {

	float* vertices = this->transformVertices();
	int* faces = this->transformFaces(); 

	cout << "Curr Mode : " << currMode << endl;

	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);

	// bind VAO
	glBindVertexArray(VAO);

	// bind VBO
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * this->vertices.size() * currMode, vertices, GL_STATIC_DRAW);

	// positions
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, currMode * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	// colors
	if (currMode == RAND_COLOR_MODE) {
		glUniform1i(texLoc, 0);
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, currMode * sizeof(float), (void*)(3 * sizeof(float))); // Décalage de 3 composantes
		glEnableVertexAttribArray(1);
	}
	else if (currMode == TEXTURE_MODE) {
		glUniform1i(texLoc, 1);
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, currMode * sizeof(float), (void*)(3 * sizeof(float))); // Décalage de 3 composantes
		glEnableVertexAttribArray(1);
		glBindTexture(GL_TEXTURE_2D, this->textureID);
		glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, currMode * sizeof(float), (void*)(6 * sizeof(float))); // Décalage de 3 composantes
		glEnableVertexAttribArray(2);
	}

	// set up EBO
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(int) * this->faces.size() * 3, faces, GL_STATIC_DRAW);
}

void	Model::draw(unsigned int shaderID) {

	glUniformMatrix4fv(glGetUniformLocation(shaderID, "transform"), 1, GL_FALSE, this->createFinalMatrix().GetDataPtr());

	// Bind VAO and other buffers to draw the model
	this->setupBuffers();

	glDrawElements(GL_TRIANGLES, this->faces.size() * 3, GL_UNSIGNED_INT, 0);

	// Unbind VAO to to let the next model use its own VAO
	glBindVertexArray(0);
}

void Model::deleteBuffers() {
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteBuffers(1, &EBO);
}

ostream& operator<<(ostream& os, const Model& model)
{
	os << "Model: " << model.modelName << endl;
	os << "  Smoothing: " << model.smoothing << endl;
	os << "  Vertices: " << model.vertices.size() << endl;
	os << "  VerticeNormals: " << model.verticeNormals.size() << endl;
	os << "  VerticeTextCoords: " << model.verticeTextCoords.size() << endl;
	os << "  Faces: " << model.faces.size() << endl;
	os << endl;
	return os;
}