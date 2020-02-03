// Includes for the assignment
#include "Vector4f.h"
#include "Matrix4f.h"
#include <iostream>

// Tests for comparing our library
// You may compare your operations against the glm library
// which is a well tested library.
#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtc/matrix_transform.hpp>

// Sample unit test comparing against GLM.
bool unitTest0(){
	glm::mat4 glmIdentityMatrix = glm::mat4(1.0f);
	Matrix4f myIdentity( 1.0f,0,0,0,
        			     0,1.0f,0,0,
		        	     0,0,1.0f,0,
			             0,0,0,1.0f);

    if(
        glmIdentityMatrix[0][0]==myIdentity[0][0] &&
        glmIdentityMatrix[0][1]==myIdentity[0][1] &&
        glmIdentityMatrix[0][2]==myIdentity[0][2] &&
        glmIdentityMatrix[0][3]==myIdentity[0][3] &&
        glmIdentityMatrix[1][0]==myIdentity[1][0] &&
        glmIdentityMatrix[1][1]==myIdentity[1][1] &&
        glmIdentityMatrix[1][2]==myIdentity[1][2] &&
        glmIdentityMatrix[1][3]==myIdentity[1][3] &&
        glmIdentityMatrix[2][0]==myIdentity[2][0] &&
        glmIdentityMatrix[2][1]==myIdentity[2][1] &&
        glmIdentityMatrix[2][2]==myIdentity[2][2] &&
        glmIdentityMatrix[2][3]==myIdentity[2][3] &&
        glmIdentityMatrix[3][0]==myIdentity[3][0] &&
        glmIdentityMatrix[3][1]==myIdentity[3][1] &&
        glmIdentityMatrix[3][2]==myIdentity[3][2] &&
        glmIdentityMatrix[3][3]==myIdentity[3][3]){
            return true;
    }
	
    return false;	
}

bool unitTest1(){
	glm::mat4 glmIdentityMatrix = glm::mat4(1.0f);
	Matrix4f myIdentity( 1.0f,0,0,0,
        			     0,1.0f,0,0,
		        	     0,0,1.0f,0,
			             0,0,0,1.0f);

    if(
        glmIdentityMatrix[0][0]==myIdentity(0,0) &&
        glmIdentityMatrix[0][1]==myIdentity(0,1) &&
        glmIdentityMatrix[0][2]==myIdentity(0,2) &&
        glmIdentityMatrix[0][3]==myIdentity(0,3) &&
        glmIdentityMatrix[1][0]==myIdentity(1,0) &&
        glmIdentityMatrix[1][1]==myIdentity(1,1) &&
        glmIdentityMatrix[1][2]==myIdentity(1,2) &&
        glmIdentityMatrix[1][3]==myIdentity(1,3) &&
        glmIdentityMatrix[2][0]==myIdentity(2,0) &&
        glmIdentityMatrix[2][1]==myIdentity(2,1) &&
        glmIdentityMatrix[2][2]==myIdentity(2,2) &&
        glmIdentityMatrix[2][3]==myIdentity(2,3) &&
        glmIdentityMatrix[3][0]==myIdentity(3,0) &&
        glmIdentityMatrix[3][1]==myIdentity(3,1) &&
        glmIdentityMatrix[3][2]==myIdentity(3,2) &&
        glmIdentityMatrix[3][3]==myIdentity(3,3)){
            return true;
    }
	
    return false;	
}

// Sample unit test comparing against GLM.
bool unitTest2(){
	glm::mat4 glmIdentityMatrix = glm::mat4(1.0f);
	Vector4f a(1.0f ,0.0f,  0.0f,   0.0f);
	Vector4f b(0.0f ,1.0f,  0.0f,   0.0f);
	Vector4f c(0.0f ,0.0f,  1.0f,   0.0f);
	Vector4f d(0.0f ,0.0f,  0.0f,   1.0f);
	Matrix4f myIdentity(a,b,c,d);

    if(
        glmIdentityMatrix[0][0]==myIdentity[0][0] &&
        glmIdentityMatrix[0][1]==myIdentity[0][1] &&
        glmIdentityMatrix[0][2]==myIdentity[0][2] &&
        glmIdentityMatrix[0][3]==myIdentity[0][3] &&
        glmIdentityMatrix[1][0]==myIdentity[1][0] &&
        glmIdentityMatrix[1][1]==myIdentity[1][1] &&
        glmIdentityMatrix[1][2]==myIdentity[1][2] &&
        glmIdentityMatrix[1][3]==myIdentity[1][3] &&
        glmIdentityMatrix[2][0]==myIdentity[2][0] &&
        glmIdentityMatrix[2][1]==myIdentity[2][1] &&
        glmIdentityMatrix[2][2]==myIdentity[2][2] &&
        glmIdentityMatrix[2][3]==myIdentity[2][3] &&
        glmIdentityMatrix[3][0]==myIdentity[3][0] &&
        glmIdentityMatrix[3][1]==myIdentity[3][1] &&
        glmIdentityMatrix[3][2]==myIdentity[3][2] &&
        glmIdentityMatrix[3][3]==myIdentity[3][3]){
            return true;
    }
	
    return false;	
}

// Sample unit test comparing against GLM.
// TODO: Test against glm::scale
bool unitTest3(){
	glm::mat4 glmScale = glm::mat4(2.0f);
	Vector4f a(1.0f,0,0,0);
	Vector4f b(0.0f,1.0f,0,0);
	Vector4f c(0,0,1.0f,0);
	Vector4f d(0,0,0,1.0f);
	Matrix4f myScaled(a,b,c,d);
    myScaled.MakeScale(2.0f,2.0f,2.0f);

    if(
        glmScale[0][0]==myScaled[0][0] &&
        glmScale[0][1]==myScaled[0][1] &&
        glmScale[0][2]==myScaled[0][2] &&
        glmScale[0][3]==myScaled[0][3] &&
        glmScale[1][0]==myScaled[1][0] &&
        glmScale[1][1]==myScaled[1][1] &&
        glmScale[1][2]==myScaled[1][2] &&
        glmScale[1][3]==myScaled[1][3] &&
        glmScale[2][0]==myScaled[2][0] &&
        glmScale[2][1]==myScaled[2][1] &&
        glmScale[2][2]==myScaled[2][2] &&
        glmScale[2][3]==myScaled[2][3] &&
        glmScale[3][0]==myScaled[3][0] &&
        glmScale[3][1]==myScaled[3][1] &&
        glmScale[3][2]==myScaled[3][2] &&
        glmScale[3][3]==myScaled[3][3]){
            return true;
    }
	
    return false;	
}

// Sample unit test comparing against GLM.
// Testing operator
bool unitTest4(){
	glm::mat4 glmTest = glm::mat4(1.0f);
    glmTest[1][3] = 72.0f;
    glmTest[2][3] = 2.1f;

	Matrix4f myMatrix(0,0,0,0,
                      0,0,0,0,
                      0,0,0,0,
                      0,0,0,0);

    myMatrix[1][3] = 72.0f;
    myMatrix[2][3] = 2.1f;

    if( glmTest[1][3]==myMatrix[1][3] &&
        glmTest[2][3]==myMatrix[2][3] ){
            return true;
    }
	
    return false;	
}

// Sample unit test testing your library
bool unitTest5(){
  Vector4f a(1,1,1,1);
  Vector4f b(0,0,0,0);
  Vector4f c = a + b;

  if(c.x == 1 && c.y == 1 && c.z ==1 && c.w==1){
    return true;
  }
    return false;
}

//Vector4D Tests
bool unitTestV0() {
    Vector4f a(1, 2, 3, 4);

    if (a[0] == 1 && a[1] == 2 && a[2] == 3 && a[3] == 4) {
        return true;
    }
    return false;
}

bool unitTestV1() {
    Vector4f a(1, 2, 3, 4);
    a *= 3;

    if (a[0] == 3 && a[1] == 6 && a[2] == 9 && a[3] == 12) {
        return true;
    }
    return false;
}

bool unitTestV2() {
    Vector4f a(1, 2, 3, 4);
    a /= 2;

    if (a[0] == 0.5 && a[1] == 1 && a[2] == 1.5 && a[3] == 2) {
        return true;
    }
    return false;
}


bool unitTestV3() {
    Vector4f a(1, 2, 3, 4);
    Vector4f b(1, 2, 3, 4);

    a += b;

    if (a[0] == 2 && a[1] == 4 && a[2] == 6 && a[3] == 8) {
        return true;
    }
    return false;
}

bool unitTestV4() {
    Vector4f a(1, 2, 3, 4);
    Vector4f b(1, 2, 3, 4);

    a -= b;

    if (a[0] == 0 && a[1] == 0 && a[2] == 0 && a[3] == 0) {
        return true;
    }
    return false;
}

bool unitTestV5() {
    Vector4f a(1, 2, 3, 4);
    Vector4f b(4, 3, 2, 1);

    float c = Dot(a, b);

    if (c == 20) {
        return true;
    }
    return false;
}

bool unitTestV6() {
    Vector4f a(4, 4, 4, 4);

    float b = Magnitude(a);
       
    if (b == 8) {
        return true;
    }
    return false;
}

bool unitTestV7() {
    Vector4f a(2, 2, 2, 2);
    Vector4f b(4, 1, 2, 1);

    Vector4f c = Project(a, b);


    if (c[0] == 2 && c[1] == 2 && c[2] == 2 && c[3] == 2) {
        return true;
    }
    return false;
}

bool unitTestV8() {
    Vector4f a(2, 2, 2, 2);

    Vector4f b = Normalize(a);


    if (b[0] == .5 && b[1] == .5 && b[2] == .5 && b[3] == .5) {
        return true;
    }
    return false;
}

bool unitTestV9() {
    Vector4f a(1, 2, 3, 4);
    Vector4f b(4, 3, 2, 1);

    Vector4f c = CrossProduct(a, b);


    if (c[0] == -5 && c[1] == 10 && c[2] == -5 && c[3] == 1) {
        return true;
    }
    return false;
}

int main(){
    // Keep track of the tests passed
    unsigned int testsPassed = 0;

    // Run 'unit tests'
    std::cout << "Passed 0: " << unitTest0() << " \n";
    std::cout << "Passed 1: " << unitTest1() << " \n";
    std::cout << "Passed 2: " << unitTest2() << " \n";
    std::cout << "Passed 3: " << unitTest3() << " \n";
    std::cout << "Passed 4: " << unitTest4() << " \n";
    std::cout << "Passed 5: " << unitTest5() << " \n";

    //Vector4D Tests
    std::cout << "Passed Vector4D Test 0: " << unitTestV0() << " \n";
    std::cout << "Passed Vector4D Test 1: " << unitTestV1() << " \n";
    std::cout << "Passed Vector4D Test 2: " << unitTestV2() << " \n";
    std::cout << "Passed Vector4D Test 3: " << unitTestV3() << " \n";
    std::cout << "Passed Vector4D Test 4: " << unitTestV4() << " \n";
    std::cout << "Passed Vector4D Test 5: " << unitTestV5() << " \n";
    std::cout << "Passed Vector4D Test 6: " << unitTestV6() << " \n";
    std::cout << "Passed Vector4D Test 7: " << unitTestV7() << " \n";
    std::cout << "Passed Vector4D Test 8: " << unitTestV8() << " \n";
    std::cout << "Passed Vector4D Test 9: " << unitTestV9() << " \n";


    return 0;
}
