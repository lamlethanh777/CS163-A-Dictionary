#include "OpenFile.h"

#include <exception>

void readFile(std::ifstream& fin, const std::string& filePath) {
	fin.open(filePath);

	if (!fin.good()) {
		throw std::invalid_argument("Dictionary source is inaccessible, please try again later!\n");
	}
}

void writeFile(std::ofstream& fout, const std::string& filePath, std::ios::openmode openmode = std::ios::trunc) {
	fout.open(filePath, openmode);

	if (!fout.good()) {
		throw std::invalid_argument("Dictionary source is inaccessible, please try again later!\n");
	}
}
