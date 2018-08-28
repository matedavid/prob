// File with all the commmand related files

#include "../header/commands.h"

// Init command action
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

// Config command action
void configCommand(const char* inputs[], int num) {
    bool flags = num == 4 ? true : false;

    if (flags) {
        std::fstream config((std::string)directory + "/prob/config");
        if (config.is_open()) {
            if (std::string(inputs[2]).compare("path") == 0) {
                std::string path = inputs[3];
                if (path[path.length() - 1] != '/') {
                    path += '/';
                }
                config << std::string(path);
                std::cout << "[SUCCES]: Path configuration added succesfully" << std::endl;
            } else {
                std::cout << workdir << std::endl;
                showHelp(workdir + "dist/spec/config.txt");
            }
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
                        read_directory(".", allFiles, "");
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
                std::cout << "Temporal file couldn't be found, try running 'prob init' to set up the environment" << std::endl;
            }
        } else {
            showHelp(workdir + "dist/spec/config.txt");
        }
    }
}

// Add command action
void addCommand(const char* inputs[], int num) {
    bool flags = num > 2 ? true : false;

    if (flags) {
        std::fstream temporal(std::string(directory) + "/prob/temporal");
        if (temporal.is_open()) {
            stringvec filesInDirectory, filesToAdd;
            read_directory(std::string(directory), filesInDirectory, " ");

            // Add all files
            if (compareString(inputs[2], ".")) {
                for (int i = 0; i < filesInDirectory.size(); i++) {
                    temporal << filesInDirectory[i] << "\n";
                    std::cout << filesInDirectory[i] << " added succesfully" << std::endl;
                }
                std::cout << "Found files added, if your path is set up, run 'prob backup' to save the files" << std::endl;
            } else if (compareString(inputs[2], "--reset") || compareString(inputs[2], "-r"))  {
                std::string line;
                getline(temporal, line);
                if (!compareString(line, "") && !compareString(line, " ")) {
                    clearFile(temporal, std::string(directory) + "/prob/temporal");
                    std::ofstream clear(std::string(directory) + "/prob/temporal",  std::ofstream::trunc);
                    std::cout << "Files to add reseted" << std::endl;
                } else {
                    std::cout << "[ERROR/s]: no files added, fun 'prob add <files>' to add files" << std::endl;
                }
            
            // To add specific files
        
            } else {
                for (int i = 2; i < num; i++) {
                    std::string line;
                    stringvec filesAdded;
                    while (getline(temporal, line)) {
                        filesAdded.push_back(line);
                    }
                    if (seeIfInList(inputs[i], filesInDirectory)) {
                        clearFile(temporal, std::string(directory) + "/prob/temporal");
                        std::ofstream temporal(std::string(directory) + "/prob/temporal");
                        if (filesAdded.size() > 0) {
                            for (int i = 0; i < filesAdded.size(); i++) {
                                temporal << filesAdded[i] << "\n";
                            }
                        }
                        if (!seeIfInList(inputs[i], filesAdded)) {
                            temporal << inputs[i] << "\n";
                            std::cout << inputs[i] << " added succefully" << std::endl;
                        } else {
                            std::cout << inputs[i] << " has already been added" << std::endl;
                        }
                    } else {
                        std::cout << "[ERROR/s]: " << inputs[i] << " was not found" << std::endl;
                    }
                }
                std::cout << "Found files added, if your path is set up, run 'prob backup' to save the files" << std::endl;
            }
            temporal.close();
        } else {
            std::cout << "Temporal file couldn't be found, try running 'prob init' to set up the environment" << std::endl;
        }
    } else {
        showHelp(workdir + "dist/spec/add.txt");
    }
}

// Backup command action -> where the saving of the files happens
void backupCommand(const char* inputs[], int num) {
    std::ifstream config(std::string(directory) + "/prob/config");
    std::ifstream temporal(std::string(directory) + "/prob/temporal");
    
    if (config.is_open() && temporal.is_open()) {
        std::string path, line;
        getline(config, path);
        if (!compareString(path, "") && !compareString(path, " ")) {
            while(getline(temporal, line)) {
                if (line.find("/") != std::string::npos) {
                    std::string folder = path;
                    int i = 0;
                    while(line[i] != '/') {
                        folder+=line[i];
                        i++;
                    }
                    if (!opendir(folder.c_str())) {
                        createFolder(folder);
                    } 
                }
                copyFile(std::string(directory) + "/" + line, path + line);
            }
            std::cout << "Possible files were saved" << std::endl;
            config.close();
            temporal.close();
        } else {
            std::cout << "Path not configured, run 'prob config path <path>' to configure it" << std::endl;
        }
    } else {
        std::cout << "[ERROR/s]: file couldn't be found, try running 'prob init' set up the environment" << std::endl;
    }
}
