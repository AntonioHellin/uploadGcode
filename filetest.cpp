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
    float maxX = 0;         //Maximal X axis value
    float maxY =0;          //Maximal Y axis value
    float maxZ = 0;         //Maximal Z axis value
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

    /*Open file*/

    /*  In order to open a file with a stream object I use the function open(filename,mode).**
    **  For open the file, I used the input parameters to the program.                      **
    **  argv[1] will be the file to send by the webinterface.                               */

    inputFile.open(argv[1],ios::in);
    if (inputFile.is_open()) {          //To check if a file stream was successful opening a file.
        while (! inputFile.eof() ) {    //Return true if a file open for reading has reached the end.
            getline (inputFile,line);   //Read the file line by line.
            fragm1 = line.substr(0,2);  //Returns a substring of the object line (Only the first 2 character).
            fragm2 = line.substr(0,4);  //Returns a substring of the object line (Only the first 4 character).

            if (fragm2 == "G1 Z"){          //When the substring fragm2 is the same that "G1 Z"
                nCounterZ++;                //Counter layers +1
                posZ = line.find("Z",2);    //Get the maximal Z axis value
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

                //Check if the instruction is extrusion or not

                pos1 = line.find("E",2);
                if (pos1 != -1){
                    nCounterG1e++;
                }
                else if (pos1 == -1){
                    nCounterG1ne++;
                }
            }
            else if (fragm1 == "G1"){

                //Check if the instruction is extrusion or not

                pos2 = line.find("E",2);
                if (pos2 != -1){
                    nCounterG1e++;
                }
                else if (pos2 == -1){
                    nCounterG1ne++;
                }

                //Get the maximal X axis value

                posX = line.find("X",2);
                if (posX != -1){

                    //Returns a substring of the object line (X axis value).

                    X = line.substr(posX+1,posX+3);
                    integerX = atof(X.c_str());
                    if (integerX > maxX){
                        maxX = integerX;
                    }
                    else{
                        maxX = maxX;
                    }
                }

                //Get the maximal Y axis value

                posY = line.find("Y",2);
                if (posY != -1){

                    //Returns a substring of the object line (Y axis value).

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

        /*Closing file*/
        inputFile.close();

        /*Print on the screen the final values*/
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
