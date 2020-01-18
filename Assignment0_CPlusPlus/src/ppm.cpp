#include "PPM.h"

struct myPixel {
    int R;
    int B;
    int G;

    myPixel(int red, int blue, int green)
    {
        R = red;
        B = blue;
        G = green;
    }
};

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
    std::vector<unsigned int> pixels;
    
    inFile.open(fileName);

    if (inFile.is_open())
    {
        std::string line;
        GotoLine(inFile, 5);

        while (getline(inFile, line))
        {
            pixels.push_back(stoi(line));
        }

        for (int i = 0; i < pixels.size(); i += 3)
        {
            myPixel x = myPixel(i, i + 1, i + 2);
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
