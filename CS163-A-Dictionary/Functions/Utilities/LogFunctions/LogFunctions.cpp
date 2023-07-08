#include "LogFunctions.h"

#include "../OpenFile/OpenFile.h"

void clearLog() {
    std::ofstream fout;
    writeFile(fout, "Log.txt");
    fout.close();
}

void callLog(const std::string logMessage) {
    std::ofstream fout;
    writeFile(fout, "Log.txt", std::ios::app);
    fout << logMessage << '\n';
    fout.close();
}
