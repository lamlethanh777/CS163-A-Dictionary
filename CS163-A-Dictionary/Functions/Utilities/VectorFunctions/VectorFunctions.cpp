#include "VectorFunctions.h"

#include <iostream>

#include "../OpenFile/OpenFile.h"

void loadVector(std::vector<std::string>& container, const std::string sourceFilePath) {
    std::string line;

    std::ifstream fin;
    readFile(fin, sourceFilePath);
    while (getline(fin, line)) {
        container.push_back(line);
    }

    fin.close();
}

void saveVector(std::vector<std::string>& container, const std::string sourceFilePath) {
    std::ofstream fout;
    writeFile(fout, sourceFilePath);

    for (unsigned int i = 0; i < container.size(); ++i) {
        fout << container[i] << '\n';
    }
    
    fout.close();
    std::cout << "Vector saved!\n";
}

void displayVector(std::vector<std::string>& container) {
    for (int i = container.size() - 1; i >= 0; --i) {
        std::cout << container[i] << '\n';
    }
}
