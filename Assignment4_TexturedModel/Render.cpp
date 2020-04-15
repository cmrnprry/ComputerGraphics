#include "Render.h"
#include <QtGui>
#include <QtWidgets>
#include <QtOpenGL>


Render::Render(std::string filename) {
	std::ifstream file(filename);
	unsigned int count = 0;

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
				QVector3D pos(vx, vy, vz);
				temp_vertices.push_back(pos);
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
				QVector2D tex(vtx, vty);
				temp_textures.push_back(tex);
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
				QVector3D norm(nx, ny, nz);
				temp_normals.push_back(norm);
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

					for (int k = 0; k < indxData.size(); k++) {
						if (indxData[k] == curr) {
							inIndex = true;
							indices.push_back(k);
							break;
						}
					}

					if (!inIndex) {
						indxData.push_back(curr);
						indices.push_back(count);
						count++;
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

	ProcessData();

	file.close();
}

IndexData Render::createFace(char* data) {
	std::string str(data); //str is in format: #/#/#
	std::string lineToken;
	std::size_t foundAt;

	lineToken = str.substr(0, str.find("/"));
	foundAt = str.find("/");
	unsigned int vIndx = stoi(lineToken);

	lineToken = str.substr(str.find("/") + 1, str.find("/"));
	unsigned int vtIndx = stoi(lineToken);
	foundAt = str.find("/", foundAt + 1);

	lineToken = str.substr(foundAt + 1, str.find("/"));
	unsigned int normIndx = stoi(lineToken);

	IndexData newData(vIndx, vtIndx, normIndx);
	return newData;
}

void Render::ProcessData()
{
	QVector3D pos, norm;
	QVector2D tex;

	std::cout << "index data: " << indxData.size() << std::endl;
	std::cout << "normals data: " << temp_normals.size() << std::endl;
	std::cout << "vertex data: " << temp_vertices.size() << std::endl;
	std::cout << "texture data: " << temp_textures.size() << std::endl;

	for (int i = 0; i < indxData.size(); i++)
	{
		IndexData data = indxData[i];
		
		pos = temp_vertices[data.vIndx - 1];
		norm = temp_normals[data.normIndx - 1];
		tex = temp_textures[data.vtIndx - 1];

		vertices.push_back(pos);
		normals.push_back(norm);
		textures.push_back(tex);
	}
}

QVector<unsigned int> Render::getIndx() {
	return indices;
}

QVector<QVector3D> Render::getVerts() {
	return vertices;
}

QVector<QVector2D> Render::getTexs() {
	return textures;
}

QVector<QVector3D> Render::getNormals() {
	return normals;
}

std::string Render::getMLib() {
	return mLib;
}