#include "LogFunctions.h"

#include "../OpenFile/OpenFile.h"

void callLog(const std::string logMessage) {
    std::ofstream fout;
    writeFile(fout, "Log.txt", std::ios::app);
    fout << logMessage << '\n';
    fout.close();
}
