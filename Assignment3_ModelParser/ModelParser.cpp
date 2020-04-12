#include "ModelParser.h"
#include <QtGui>
#include <QtWidgets>
#include <QtOpenGL>

ModelParser::ModelParser(std::string filename) {
	std::ifstream file(filename);

	if (!file) {
		std::cout << "Error opening " << filename << std::endl;
	}

	std::string line;
	while (std::getline(file, line)) {

		std::stringstream linestr(line);
		std::string next;
		linestr >> next;
		if (next == "v") {
			//Gather the vertices into a vector
			GLfloat x, y, z;
			linestr >> x >> y >> z;
			if (!linestr) {
				std::cout << "Error reading " << filename << " in line: "
					<< line << std::endl;
			}
			else {
				vertices.push_back(x);
				vertices.push_back(y);
				vertices.push_back(z);
			}
		}
		else if (next == "vn") {
			//Gather the vertex normals into a vector
			GLfloat nx, ny, nz;
			linestr >> nx >> ny >> nz;
			if (!linestr) {
				std::cout << "Error reading " << filename << " in line: "
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
				//Disregard the normals (for now). We just want vertex indices.
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

QVector<GLuint> ModelParser::getIndices() {
	return indices;
}

QVector<GLfloat> ModelParser::getVertices() {
	return vertices;
}

QVector<GLfloat> ModelParser::getNormals() {
	return normals;
}