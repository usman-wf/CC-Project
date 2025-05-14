#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "fast_lang.tab.h"

using namespace std;

extern FILE* yyin;
extern int yyparse();
extern vector<string> threeAddressCode;

void writeThreeAddressCodeToFile(const string& filename) {
    ofstream outFile(filename);
    if (!outFile) {
        cerr << "Error: Could not open output file " << filename << endl;
        return;
    }

    for (const auto& line : threeAddressCode) {
        outFile << line << endl;
    }

    outFile.close();
    cout << "Three-address code has been written to " << filename << endl;
}

int main() {
    string inputFilename;
    cout << "Enter the name of the input file: ";
    cin >> inputFilename;

    FILE* inputFile = nullptr;
    errno_t err = fopen_s(&inputFile, inputFilename.c_str(), "r");
    if (err != 0 || !inputFile) {
        cerr << "Error: Could not open input file " << inputFilename << endl;
        return 1;
    }
    yyin = inputFile;

    int parseResult = yyparse();

    fclose(inputFile);

    if (parseResult == 0) {
        cout << "Parsing completed successfully." << endl;

        string outputFilename = inputFilename.substr(0, inputFilename.find_last_of('.')) + ".tac";

        writeThreeAddressCodeToFile(outputFilename);
        return 0;
    }
    else {
        cerr << "Parsing failed." << endl;
        return 1;
    }
}