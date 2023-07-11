#ifndef VECTOR_FUNCTIONS_H
#define VECTOR_FUNCTIONS_H

#include <vector>
#include <string>

void loadVector(std::vector<std::string>& container, const std::string sourceFilePath);

void saveVector(std::vector<std::string>& container, const std::string sourceFilePath);

void displayVector(std::vector<std::string>& container);

#endif // !VECTOR_FUNCTIONS_H
