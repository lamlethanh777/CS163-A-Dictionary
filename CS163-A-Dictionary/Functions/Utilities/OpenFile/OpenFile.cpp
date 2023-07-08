#include "OpenFile.h"

#include <iostream>
#include <exception>

std::string getFolderPath(const std::string& filePath) {
	int found = filePath.find_last_of("/\\");
	return filePath.substr(0, found + 1);
}

void readFile(std::ifstream& fin, const std::string& filePath) {
	fin.open(filePath);

	if (!fin.good()) {
		throw std::invalid_argument("Dictionary source is inaccessible, please try again later!\n");
	}
}

void writeFile(std::ofstream& fout, const std::string& filePath, std::ios::openmode openmode) {
	fout.open(filePath, openmode);

	if (!fout.good()) {
        std::cout << "Cannot open file!\n";
		throw std::invalid_argument("Dictionary source is inaccessible, please try again later!\n");
	}
}
