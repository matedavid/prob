#include "../header/files.h"

void copyFile(std::string pathFile, std::string pathToCopy) {
    std::ifstream copy(pathFile);
    std::ofstream paste(pathToCopy);
    //std::cout << pathToCopy << std::endl;

    if (copy.is_open() && paste.is_open()) {
        std::string line;
        while (getline(copy, line)) {
            paste << line << '\n';
        }
        std::cout << pathFile << " copied to: " << pathToCopy << std::endl;
        copy.close();
        paste.close();
    } else {
        std::cout << "[ERROR/s]: Something was wrong when copying " << pathToCopy << std::endl;
    }
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