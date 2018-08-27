// File with all the path related functions

#include "../header/pathFuncs.h"

void read_directory(const std::string& name, stringvec& v)
{
    DIR* dirp = opendir(name.c_str());
    struct dirent * dp;
    while ((dp = readdir(dirp)) != NULL) {
        v.push_back(dp->d_name);
    }
    closedir(dirp);
}

int createfile(std::string filePath, std::string fileType) {
    std::ofstream fileToCreate(filePath);
    if (fileToCreate.is_open()) {
        std::cout << fileType << " created succesfully" << std::endl;
        return 1;
    } else {
        std::cout << "[ERROR/s]: File could not be created" << std::endl;
        return 0;
    }
    fileToCreate.close();
}

int createFolder(std::string folderPath) {
    int success = mkdir(folderPath.c_str(), S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);
    return success;
}