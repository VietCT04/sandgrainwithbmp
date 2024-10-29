#include <iostream>
#include <fstream>
#include <string>
#include <stdexcept>
#include "sandpile.h"
#include "bmp_writer.h"

using namespace std;

// Utility function to parse command-line arguments
void parseArguments(int argc, char* argv[], string &inputFile, string &outputDir, int &maxIter, int &frequency) {
    for (int i = 1; i < argc; i++) {
        if (string(argv[i]) == "-i" || string(argv[i]) == "--input") {
            inputFile = argv[++i];
        } else if (string(argv[i]) == "-o" || string(argv[i]) == "--output") {
            outputDir = argv[++i];
        } else if (string(argv[i]) == "-m" || string(argv[i]) == "--max-iter") {
            maxIter = stoi(argv[++i]);
        } else if (string(argv[i]) == "-f" || string(argv[i]) == "--freq") {
            frequency = stoi(argv[++i]);
        } else {
            throw invalid_argument("Invalid argument");
        }
    }
}

int main(int argc, char* argv[]) {
    string inputFile, outputDir;
    int maxIter = 5, frequency = 1;

    try {
        parseArguments(argc, argv, inputFile, outputDir, maxIter, frequency);
    } catch (const exception& e) {
        cerr << "Error: " << e.what() << "\n";
        return 1;
    }

    SandpileModel model;
    cout << "Initializing model with input file: " << inputFile << endl;
    model.initialize(inputFile);
    /*
    cout << "Height: " << model.getHeight()  << endl;
        cout << "Width: " << model.getWidth()  << endl;
        for (int x = 0; x < model.getHeight(); x++){
            for (int y = 0; y < model.getWidth();y++){
                cout << model.getCell(x, y) << " ";
            }
            cout << endl;
        }*/
    for (int i = 0; i < maxIter; i++) {
        model.update();
        cout << "Iteration " << i << " completed." << endl;

        if (frequency > 0 && i % frequency == 0) {
            BMPWriter::save(model, outputDir, i);
            cout << "Saved BMP for iteration " << i << endl;
        }

        if (model.isStable()) {
            cout << "Model reached stability at iteration " << i << endl;
            break;
        }

        /*
        cout << "Height: " << model.getHeight()  << endl;
        cout << "Width: " << model.getWidth()  << endl;

        for (int x = 0; x < model.getHeight(); x++){
            for (int y = 0; y < model.getWidth();y++){
                cout << model.getCell(x, y) << " ";
            }
            cout << endl;
        }
        */
    }
    BMPWriter::save(model, outputDir, maxIter);
    cout << "Final BMP saved." << endl;

    return 0;
}
