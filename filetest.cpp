#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <stdio.h>
#include <stdlib.h>

using namespace std;

int main(int argc, char *argv[]){
    fstream inputFile;
    string line;
    string fragm1;
    string fragm2;
    string X;
    string Y;
    string Z;
    float maxX = 0;
    float maxY =0;
    float maxZ = 0;
    int nCounterG1ne = 0;   //Number of non-extrusion movements
    int nCounterG1e = 0;    //Number of extrusion movements
    int nCounterZ = 0;      //Number of layers in the 3D model
    int pos1 = 0;
    int pos2 = 0;
    int posX = 0;
    int posY = 0;
    int posZ = 0;
    float integerX = 0;
    float integerY = 0;
    float integerZ = 0;

    inputFile.open("",ios::in);
    //inputFile.open(argv[1],ios::in);
    if (inputFile.is_open()) {
        while (! inputFile.eof() ) {
            getline (inputFile,line);
            fragm1 = line.substr(0,2);
            fragm2 = line.substr(0,4);

            if (fragm2 == "G1 Z"){
                nCounterZ++;
                posZ = line.find("Z",2);
                if(posZ != -1){
                    Z = line.substr(posZ+1,posZ+3);
                    integerZ = atof(Z.c_str());
                    if (integerZ > maxZ){
                        maxZ = integerZ;
                    }
                    else{
                        maxZ = maxZ;
                    }
                }

                pos1 = line.find("E",2);
                if (pos1 != -1){
                    nCounterG1e++;
                }
                else if (pos1 == -1){
                    nCounterG1ne++;
                }
            }
            else if (fragm1 == "G1"){
                pos2 = line.find("E",2);
                if (pos2 != -1){
                    nCounterG1e++;
                }
                else if (pos2 == -1){
                    nCounterG1ne++;
                }
                posX = line.find("X",2);
                if (posX != -1){
                    X = line.substr(posX+1,posX+3);
                    integerX = atof(X.c_str());
                    if (integerX > maxX){
                        maxX = integerX;
                    }
                    else{
                        maxX = maxX;
                    }
                }
                posY = line.find("Y",2);
                if (posY != -1){
                    Y = line.substr(posY+1,posY+3);
                    integerY = atof(Y.c_str());
                    if (integerY > maxY){
                        maxY = integerY;
                    }
                    else{
                        maxY = maxY;
                    }
                }
            }
        }
        inputFile.close();
        cout << "Number of extrusion movements:" << nCounterG1e << "\n" << endl;
        cout << "Number of non-extrusion movements:" << nCounterG1ne << "\n" << endl;
        cout << "Number of layers in the 3D model:" << nCounterZ << "\n" << endl;
        cout << "Max X:" << maxX << "\n" << endl;
        cout << "Max Y:" << maxY << "\n" << endl;
        cout << "Max Z:" << maxZ << "\n" << endl;
    }
    else {
        cout << "Error" << endl;
    }
    return 1;
}
