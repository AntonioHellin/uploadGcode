/**
 * @file filetest.cpp
 * @brief G-Code parser and dimensional boundary analyzer.
 *
 * Analyzes G-code movement commands (G1) to extract:
 * - Extrusion move counts
 * - Non-extrusion move counts
 * - Total distinct layer heights (Z transitions)
 * - Maximum spatial coordinates (X, Y, Z)
 */

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <cstdlib>

using namespace std;

int main(int argc, char *argv[])
{
    if (argc < 2)
    {
        cerr << "Usage: " << argv[0] << " <filepath>" << endl;
        return 1;
    }

    ifstream inputFile(argv[1]);
    if (!inputFile.is_open())
    {
        cerr << "Error: Unable to open file: " << argv[1] << endl;
        return 1;
    }

    string line;
    float maxX = 0.0f;
    float maxY = 0.0f;
    float maxZ = 0.0f;
    int nCounterG1ne = 0;  // Non-extrusion move count
    int nCounterG1e = 0;   // Extrusion move count
    int nCounterZ = 0;     // Layer count

    while (getline(inputFile, line))
    {
        if (line.empty()) continue;

        // Check for G1 command at the beginning of the line
        if (line.rfind("G1", 0) == 0)
        {
            // Extrusion check: presence of 'E' parameter
            size_t posE = line.find('E');
            if (posE != string::npos)
            {
                nCounterG1e++;
            }
            else
            {
                nCounterG1ne++;
            }

            // Z axis inspection (layer height)
            size_t posZ = line.find('Z');
            if (posZ != string::npos)
            {
                nCounterZ++;
                try
                {
                    float valZ = stof(line.substr(posZ + 1));
                    if (valZ > maxZ) maxZ = valZ;
                }
                catch (...) {}
            }

            // X axis inspection
            size_t posX = line.find('X');
            if (posX != string::npos)
            {
                try
                {
                    float valX = stof(line.substr(posX + 1));
                    if (valX > maxX) maxX = valX;
                }
                catch (...) {}
            }

            // Y axis inspection
            size_t posY = line.find('Y');
            if (posY != string::npos)
            {
                try
                {
                    float valY = stof(line.substr(posY + 1));
                    if (valY > maxY) maxY = valY;
                }
                catch (...) {}
            }
        }
    }

    inputFile.close();

    cout << "Number of extrusion movements: " << nCounterG1e << "\n" << endl;
    cout << "Number of non-extrusion movements: " << nCounterG1ne << "\n" << endl;
    cout << "Number of layers in the 3D model: " << nCounterZ << "\n" << endl;
    cout << "Max X: " << maxX << "\n" << endl;
    cout << "Max Y: " << maxY << "\n" << endl;
    cout << "Max Z: " << maxZ << "\n" << endl;

    return 0;
}
