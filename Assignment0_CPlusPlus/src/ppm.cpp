#include "PPM.h"

std::ifstream& GotoLine(std::ifstream& file, unsigned int num) {
	for (int i = 0; i < (num - 1); ++i) {
		file.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	}
	return file;
}

// Constructor loads a filename with the .ppm extension
PPM::PPM(std::string fileName) {
	std::ifstream inFile;

	inFile.open(fileName);

	if (inFile.is_open())
	{
		std::string line;

		GotoLine(inFile, 3);

		//gets the width
		getline(inFile, line, ' ');
		std::cout << "width: " << line << std::endl;
		m_width = stoi(line);

		//gets the height
		getline(inFile, line);
		std::cout << "height: " << line << std::endl;
		m_height = stoi(line);

		int size = getWidth() * getHeight() * 3;
		m_PixelData = new unsigned char[size];

		//assigning pixel data
		char* tok;
		int i = 0;

		getline(inFile, line);
		std::cout << "Line after width x height: " << line << std::endl;

		while (getline(inFile, line))
		{
			char* cStr = new char[line.length() + 1];
			std::strcpy(cStr, line.c_str());

			tok = strtok(cStr, " ");
			
			while (tok != NULL)
			{
				m_PixelData[i] = (unsigned char)atoi(tok);
				tok = strtok(NULL, " ");
				i++;
			}

			delete[] cStr;
		}
	}
}

// Destructor clears any memory that has been allocated
PPM::~PPM() {
	delete[] pixelData();
}

// Saves a PPM Image to a new file.
void PPM::savePPM(std::string outputFileName) {

	std::ofstream outFile;

	outFile.open(outputFileName);

	outFile << "P3" << std::endl;
	outFile << "#PLease" << std::endl;
	outFile << getWidth() << " " << getHeight() << std::endl;
	outFile << "255" << std::endl;
	for (int i = 0; i < ((getWidth() * getHeight()) * 3); i++) {
		outFile << (int)pixelData()[i] << std::endl;
	}
	outFile.close();
}



// Darken subtracts 50 from each of the red, green
// and blue color components of all of the pixels
// in the PPM. Note that no values may be less than
// 0 in a ppm.
void PPM::darken() {
	//std::cout << (int)pixelData()[0];

	for (int x = 0; x < (getWidth() * getHeight() * 3); x += 3)
	{
		setPixel(x, 0, (int)pixelData()[x], (int)pixelData()[x + 1], (int)pixelData()[x + 2]);
	}
	
}

// Sets a pixel to a specific R,G,B value 
void PPM::setPixel(int x, int y, int R, int G, int B) {
	
	
	(R <= 50) ? R = 0 : R -= 50;
	(G <= 50) ? G = 0 : G -= 50;
	(B <= 50) ? B = 0 : B -= 50;

	pixelData()[x] = (unsigned char)R;
	pixelData()[(x + 1)] = (unsigned char)G;
	pixelData()[x + 2] = (unsigned char)B;

	//std::cout << "line number " << x << "," << y << ": " << (int)pixelData()[x] << " " << (int)pixelData()[x + 1] << " " << (int)pixelData()[x + 2] << std::endl;

}
