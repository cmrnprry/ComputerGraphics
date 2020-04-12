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
			//Gather the face indices into a vector using a tokenizer (to deal with the slashes)
			std::string lineAsString = linestr.str();
			char* lineCStr = new char[lineAsString.size() + 1];;
			std::strcpy(lineCStr, lineAsString.c_str());
			char* lineToken;
			lineToken = std::strtok(lineCStr, "f// ");
			int i = 1;
			
			while (lineToken != NULL) {
				GLuint curr = std::stoi(lineToken) - 1;
				if (i % 2 == 1) {
					indices.push_back(curr);
				}
				i++;
				lineToken = std::strtok(NULL, "f// ");
			}
		}
		else {
			continue;
		}
	}
	file.close();
}

QVector<GLuint> Render::getIndx() {
	return indices;
}

QVector<GLfloat> Render::getVerts() {
	return vertices;
}

QVector<GLfloat> Render::getNormals() {
	return normals;
}