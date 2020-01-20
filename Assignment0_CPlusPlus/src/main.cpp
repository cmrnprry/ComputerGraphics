// Include our custom library
#include "PPM.h"

int main(){

    PPM myPPM("../textures/test.ppm");
    myPPM.darken();
    myPPM.savePPM("../textures/test_darken.ppm");

    return 0;
}
