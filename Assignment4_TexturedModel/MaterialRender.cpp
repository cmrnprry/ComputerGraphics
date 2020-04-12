#include "MaterialRender.h"
#include <QtGui>
#include <QtWidgets>
#include <QtOpenGL>

MaterialRender::MaterialRender(std::string filename) {
    std::ifstream file(filename);

    if (!file) {
        std::cout << "Couldn't open " << filename << std::endl;
    }

    std::string line;
    while (std::getline(file, line)) {

        std::stringstream linestr(line);
        std::string next;
        linestr >> next;

        if (next == "newmtl") {
            std::string name;
            linestr >> name;

            if (!linestr) {
                std::cout << "Couldn't open " << filename << " in line: "
                    << line << std::endl;
            }
            else {
                matName = name;
            }
        }
        else if (next == "map_Kd") {
            std::string kd;
            linestr >> kd;


            if (!linestr) {
                std::cout << "Couldn't open " << filename << " in line: "
                    << line << std::endl;
            }
            else {
                diffuseColor = kd;
            }
        }
        else {
            continue;
        }
    }
    file.close();
}