#include "Render.h"
#include <QtGui>
#include <QtWidgets>
#include <QtOpenGL>


Render::Render(std::string filename) {
	std::ifstream file(filename);

	if (!file) {
		std::cout << "Couldn't open " << filename << std::endl;
	}

	std::string line;
	while (std::getline(file, line)) {

		std::stringstream linestr(line);
		std::string next;
		linestr >> next;

		if (next == "v") {
			//Gather the vertices into a vector
			GLfloat vx, vy, vz;
			linestr >> vx >> vy >> vz;

			if (!linestr) {
				std::cout << "Couldn't open " << filename << " in line: "
					<< line << std::endl;
			}
			else {
				vertices.push_back(vx);
				vertices.push_back(vy);
				vertices.push_back(vz);
			}
		}
		if (next == "vt") {
			//Gather the vertex textures into a vector
			GLfloat vtx, vty;
			linestr >> vtx >> vty;

			if (!linestr) {
				std::cout << "Couldn't open " << filename << " in line: "
					<< line << std::endl;
			}
			else {
				textures.push_back(vtx);
				textures.push_back(vty);
			}
		}
		else if (next == "vn") {
			//Gather the vertex normals into a vector
			GLfloat nx, ny, nz;
			linestr >> nx >> ny >> nz;

			if (!linestr) {
				std::cout << "Couldn't open " << filename << " in line: "
					<< line << std::endl;
			}
			else {
				normals.push_back(nx);
				normals.push_back(ny);
				normals.push_back(nz);
			}
		}
		else if (next == "f") {
			//Gather the face indices into a vector using a tokenizer
			std::string lineAsString = linestr.str();
			char* lineCStr = new char[lineAsString.size() + 1];;
			std::strcpy(lineCStr, lineAsString.c_str());
			char* lineToken;
			lineToken = std::strtok(lineCStr, " ");
			int i = 1;

			while (lineToken != NULL) {
				bool inIndex = false;
				if (strlen(lineToken) > 3) {

					//std::cout << "Full length " << lineToken << std::endl;
					IndexData curr = createFace(lineToken);

					for each (IndexData temp in indxData) {
						if (temp == curr) {
							inIndex = true;
						}
					}
					if (!inIndex) {
						indxData.push_back(curr);
						indices.push_back(curr.x);
						indices.push_back(curr.y);
						indices.push_back(curr.z);
					}

				}
				lineToken = std::strtok(NULL, " ");
			}
		}
		else if (next == "mtllib")
		{
			std::string lib;
			linestr >> lib;

			if (!linestr) {
				std::cout << "Couldn't open " << filename << " in line: "
					<< line << std::endl;
			}
			else {
				mLib = lib;
			}
		}
		else {
			continue;
		}
	}

	file.close();
}

IndexData Render::createFace(char* data) {
	std::string str(data);
	std::string lineToken;

	lineToken = str.substr(0, str.find("/"));
	float x = stof(lineToken);
	float y = stof(lineToken);
	float z = stof(lineToken);

	lineToken = str.substr(str.find("/") + 1, str.find("/"));
	float s = stof(lineToken);
	float t = stof(lineToken);

	IndexData newData(x, y, z, s, t);
	return newData;
}

QVector<GLfloat> Render::getIndx() {
	return indices;
}

QVector<GLfloat> Render::getVerts() {
	return vertices;
}

QVector<GLfloat> Render::getTexs() {
	return textures;
}

QVector<GLfloat> Render::getNormals() {
	return normals;
}

std::string Render::getMLib() {
	return mLib;
}