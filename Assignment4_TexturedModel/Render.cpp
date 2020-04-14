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
				QVector3D pos(vx, vy, vz);
				vertices.push_back(pos);
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
				textures.push_back(tex);
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
				QVector3D pos(nx, ny, nz);
				normals.push_back(pos);
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
	std::cout << "vn size: " << normals.size() << std::endl;
	std::cout << "vt size: " << textures.size() << std::endl;
	std::cout << "v size: " << vertices.size() << std::endl;

	file.close();
}

IndexData Render::createFace(char* data) {
	std::string str(data);
	std::string lineToken;

	lineToken = str.substr(0, str.find("/"));
	unsigned int x = stoi(lineToken);
	unsigned int y = stoi(lineToken);
	unsigned int z = stoi(lineToken);

	lineToken = str.substr(str.find("/") + 1, str.find("/"));
	unsigned int s = stoi(lineToken);
	unsigned int t = stoi(lineToken);

	IndexData newData(x, y, z, s, t);
	return newData;
}

void Render::ProcessData()
{
	float j, k;
	QVector3D pos, norm;
	QVector2D tex;

	QVector<QVector3D> temp_vertices, temp_normals;
	QVector<QVector2D> temp_textures;

	for (int i = 0; i < indxData.size(); i++)
	{
		IndexData data = indxData[i];
		j = data.x;
		k = data.s;
		
		pos = vertices[j - 1];
		norm = vertices[j - 1];
		tex = textures[k - 1];

		temp_vertices.push_back(pos);
		temp_normals.push_back(norm);
		temp_textures.push_back(tex);
	}

	vertices = temp_vertices;
	normals = temp_normals;
	textures = temp_textures;
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