#include "PPM.h"

std::ifstream& GotoLine(std::ifstream& file, unsigned int num) {
    for (int i = 0; i < num - 1; ++i) {
        file.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
    return file;
}

// Constructor loads a filename with the .ppm extension
PPM::PPM(std::string fileName){
    // TODO:    Load and parse a ppm to get its pixel
    //          data stored properly.


    std::ifstream inFile;

    inFile.open(fileName);

    if (inFile.is_open())
    {
      std::string line;

       GotoLine(inFile, 3);
        
       //gets the width
       getline(inFile, line, ' ');
       m_width = stoi(line);

       //gets the height
       getline(inFile, line);
       m_height = stoi(line);

       //goes to the pixel data
        GotoLine(inFile, 5);
        
        char * tok;
        int i = 0;
        
        while (getline(inFile, line))
        {
            const char* cStr = new char[line.length()];
            cStr = line.c_str();

            while (tok != NULL)
            {
                m_PixelData[i] = (unsigned) tok;
                tok = strtok(NULL, " ");
                i++;
            }
            
            delete[] cStr;
        }
    }
}

// Destructor clears any memory that has been allocated
PPM::~PPM(){
    
}

// Saves a PPM Image to a new file.
void PPM::savePPM(std::string outputFileName){

    std::ofstream outFile;

    outFile.open(outputFileName);

    outFile.close();
}



// Darken subtracts 50 from each of the red, green
// and blue color components of all of the pixels
// in the PPM. Note that no values may be less than
// 0 in a ppm.
void PPM::darken(){
    // TODO: Output a 'filtered' PPM image.



}

// Sets a pixel to a specific R,G,B value 
void PPM::setPixel(int x, int y, int R, int G, int B){
    // TODO: Implement

    if (R <= 50)
    {
        R = 0;
    }
    else
    {
        R = R - 50;
    }

    if (B <= 50)
    {
        B = 0;
    }
    else
    {
        B = B - 50;
    }

    if (G <= 50)
    {
        G = 0;
    }
    else
    {
        G = G - 50;
    }
}
