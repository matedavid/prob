// File with all the path related functions

#include "../header/pathFuncs.h"

void read_directory(const std::string& name, stringvec& v, std::string toAdd)
{
    DIR* dirp = opendir(name.c_str());
    struct dirent * dp;
    stringvec toIgnore;
    std::ifstream probIgnore(std::string(directory) + "/.probignore");
    if (probIgnore.is_open()) {
        std::string file;
        while (getline(probIgnore, file)) {
            toIgnore.push_back(file);
        }
        toIgnore.push_back(".probignore");
    }
    
    while ((dp = readdir(dirp)) != NULL) {
        if (!compareString(dp->d_name, ".") && !compareString(dp->d_name, "..") && !compareString(dp->d_name, ".DS_Store") && !compareString(dp->d_name, "prob")) {
            if (toIgnore.size() > 0) {
                if (!seeIfInList(dp->d_name, toIgnore)) {
                    std::string name = std::string(directory) + "/" + dp->d_name;
                    if (opendir(name.c_str())) {
                        read_directory(name, v, dp->d_name + std::string("/"));
                    } else if (!compareString(toAdd, "") && !compareString(toAdd, " ")){
                        name = std::string(directory) + "/" + toAdd + dp->d_name;
                        if (opendir(name.c_str())) {
                            std::string newToAdd = toAdd + dp->d_name + "/";
                            read_directory(name, v, newToAdd);
                        } else {
                            v.push_back(toAdd + dp->d_name);
                        }
                    } else {
                        v.push_back(dp->d_name);
                    }
                }
            } else {
                std::string name = std::string(directory) + "/" + dp->d_name;
                if (opendir(name.c_str())) {
                    read_directory(name, v, "");
                } else if (!compareString(toAdd, "") && !compareString(toAdd, " ")) {
                    name = std::string(directory) + "/" + toAdd + dp->d_name;
                    if (opendir(name.c_str())) {
                        std::string newToAdd = toAdd + dp->d_name + "/";
                        read_directory(name, v, newToAdd);
                    } else {
                        v.push_back(toAdd + dp->d_name);
                    }
                } else {
                    v.push_back(dp->d_name);
                }
            }
        }
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


std::string getFilePath(std::string path) {
    std::string newPath;
    for (int i = path.length(); i > 0; i--) {
        if ((char)path[i] == '/') {
            for (int e = 0; e < i+1; e++) {
                newPath += path[e];
            }
            break;
        }
    }
    path.clear();
    return newPath;
}
