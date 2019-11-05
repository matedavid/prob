// File with all extra functions

#include "../header/extraFuncs.h"

void showHelp(std::string path) {
    std::ifstream helpFile(path);
    if (helpFile.is_open()) {
        std::string line;
        while (getline(helpFile, line)) {
            std::cout << line << std::endl;
        }
        helpFile.close();
    } else {
        std::cout << "File not opened" << std::endl;
    }
}

bool compareString(std::string originalString, std::string toCompare) {
    if (originalString.compare(toCompare) == 0) {
        return true;
    } else {
        return false;
    }
}
