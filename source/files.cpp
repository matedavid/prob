#include "../header/files.h"

void copyFile(std::string pathFile, std::string pahToCopy) {
    
}

bool seeIfInList(std::string thing, stringvec array) {
    for (int i = 0; i < array.size(); i++) {
        if (compareString(array[i], thing)) {
            return true;
        }
    }
    return false;
}

void clearFile(std::fstream& fileToClear, std::string path) {
    fileToClear.close();
    std::ofstream clear(path, std::ofstream::trunc);
    clear.close();
}