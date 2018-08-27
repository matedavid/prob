// File with all the commmand related files

#include "../header/commands.h"

void showHelp(std::string path) {
    std::ifstream helpFile(path, std::ios::in);
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

void initCommand(const char* inputs[], int num) {
    int success = createFolder((std::string)directory + "/prob");
    if (success == 0) {
        std::cout << "Folder created succesfully on " + (std::string)directory + "/prob" << std::endl;

        int config = createfile((std::string)directory + "/prob/config", "Config");
        int logs = createfile((std::string)directory + "/prob/logs", "Logs");
        int source = createfile((std::string)directory + "/prob/source", "Source");
        int temporal = createfile((std::string)directory + "/prob/temporal", "Temporal");
        if (config && logs && source && temporal) {
            std::cout << "[SUCCESS]: Prob environment created succesfully" << std::endl;
        } else {
            std::cout << "[ERROR/s]: Some files may not be created" << std::endl;
        }
    } else {
        std::cout << "prob folder already created" << std::endl;
    }
}

void configCommand(const char* inputs[], int num) {
    bool flags = num == 4 ? true : false;

    if (flags) {
        std::fstream config((std::string)directory + "/prob/config");
        if (config.is_open()) {
            if (std::string(inputs[2]).compare("path") == 0) {
                config << std::string(inputs[3]);
            }
            std::cout << "[SUCCES]: Configuration added succesfully" << std::endl;
        } else {
            std::cout << "[ERROR/s]: Config file not found, try running 'prob init' again" << std::endl;
        }
        config.close();
    } else {
        if (std::string(inputs[2]).compare("path") == 0) {
            std::ifstream file(std::string(directory) + "/prob/config");
            if (file.is_open()) {
                std::string path;
                getline(file, path);
                if (path.compare("") == 0 || path.compare(" ") == 0) {
                    std::cout << "Path not configured, run 'prob config path <path>' to configure it" << std::endl;
                } else {
                    std::cout << path << std::endl;
                }
            } else {
                std::cout << "Configure file not found, try running 'prob init'" << std::endl;
            }
        } else if (std::string(inputs[2]).compare("added") == 0) {
            std::ifstream file(std::string(directory) +  "/prob/temporal");
            if (file.is_open()) {
                std::string line; 
                bool noFile = true;
                while(getline(file, line)) {
                    if (line.compare(".") == 0) {
                        stringvec allFiles;
                        read_directory(".", allFiles);
                        for (int i = 0; i < allFiles.size(); i++) {
                            std::cout << allFiles[i] << std::endl;
                            noFile = false;
                        }
                        break;
                    }
                    std::cout << line << std::endl;
                    noFile = false;
                }
                if (noFile) {
                    std::cout << "No added files, run 'prob add <files>' to add files" << std::endl;
                }
            } else {
                std::cout << "Temoral file not found, try running 'prob init'" << std::endl;
            }
        } else {
            showHelp(workdir + "dist/spec/config.txt");
        }
    }
}

bool seeIfInList(std::string thing, stringvec array) {
    for (int i = 0; i < array.size(); i++) {
        if (array[i].compare(thing) == 0) {
            return true;
        }
    }
    return false;
}

void addCommand(const char* inputs[], int num) {
    bool flags = num > 2 ? true : false;

    if (flags) {
        std::ofstream temporal(std::string(directory) + "/prob/temporal");
        stringvec filesInDirecory, filesToAdd;
        read_directory(std::string(directory), filesInDirecory);
        if (std::string(inputs[2]).compare(".") == 0) {
            temporal << ".";
            std::cout << "All files added" << std::endl;
        } else {
            for (int i = 2; i < num; i++) {
                filesToAdd.push_back(inputs[i]);
            }

            for (int i = 0; i < filesToAdd.size(); i++) {
                bool found = seeIfInList(filesToAdd[i], filesInDirecory);
                if (found) {
                    temporal << filesToAdd[i] << "\n";
                    std::cout << filesToAdd[i] << " added succesfully" << std::endl;
                } else {
                    std::cout << filesToAdd[i] << " couldn't be found" << std::endl;
                }
            }
            std::cout << "Found files added" << std::endl;
        }
        temporal.close();
    } else {
        showHelp(workdir + "dist/spec/add.txt");
    }
}

void backupCommand(const char* inputs[], int num) {
    std::ifstream config(std::string(directory) + "/prob/config");
    std::ifstream temporal(std::string(directory) + "/prob/temporal");
    
    if (config.is_open() && temporal.is_open()) {
        std::string path, line;
        config >> path;
    
        while(getline(temporal, line)) {
            if (line.compare(".") == 0) {
                stringvec filesToCopy;
                read_directory(".", filesToCopy);
                for (int i = 0; i < filesToCopy.size(); i++) {
                    std::string command = "cp " + (std::string)directory + "/" + filesToCopy[i] + " " + path + filesToCopy[i];
                    system(command.c_str());
                }
                break;
                
            } else {
                std::string command = "cp " + (std::string)directory + "/" + line + " " + path + line;
                system(command.c_str());
                while(getline(temporal, line)) {
                    std::string command = "cp " + (std::string)directory + "/" + line + " " + path + line;
                    system(command.c_str());
                }
            }
        }
        std::cout << "Possible files were saved" << std::endl;
        config.close();
        temporal.close();
    } else {
        std::cout << "[ERROR/s]: files couldn't be found, try running 'prob init'" << std::endl;
    }
}
