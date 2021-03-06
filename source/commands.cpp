// File with all the commmand related files

#include "../header/commands.h"

// Init command action
void initCommand() {
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
    bool flags = num > 2 ? true : false;

    std::fstream file;

    if (flags) {
        std::string line;
        if (compareString(inputs[2], "path")) {
            file.open(std::string(directory) + "/prob/config");
            if (inputs[3]) {
                std::string fakePath = inputs[3], path;
                path = fakePath[fakePath.length()] == '/' ? fakePath : fakePath+ "/";
                file << path;
                std::cout << "Path configured succesfully" << std::endl;
            } else {
                if (getline(file, line)) {
                    std::cout << line << std::endl;
                } else {
                    std::cout << "[ERROR/s]: Path not configured, run 'prob config path <path>' to configure it" << std::endl;
                }
            }
            file.close();
        } else if (compareString(inputs[2], "logs")) {
            file.open(std::string(directory) + "/prob/logs");
            if (getline(file, line)) {
                std::cout << line << std::endl;
                while (getline(file, line)) {
                    std::cout << line << std::endl;
                }
            } else {
                std::cout << "[ERROR/s]: No backups found" << std::endl;
            }
            file.close();
        } else if (compareString(inputs[2], "added")) {
            file.open(std::string(directory) + "/prob/temporal");
            if (getline(file, line)) {
                std::cout << line << std::endl;
                while(getline(file, line)) {
                    std::cout << line << std::endl;
                }
            } else {
                std::cout << "[ERROR/s]: No files added, run 'prob add [files]' to add them" << std::endl;
            }
            file.close();
        } else {
            showHelp(workdir + "dist/spec/config.txt");   
        }
    } else {
        showHelp(workdir + "dist/spec/config.txt");
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
                for (int i = 0; i < int(filesInDirectory.size()); i++) {
                    temporal << filesInDirectory[i] << "\n";
                    std::cout << filesInDirectory[i] << " added succesfully" << std::endl;
                }
                std::cout << "Found files added, if your path is set up, run 'prob backup' to save the files" << std::endl;
            } else if (compareString(inputs[2], "--reset") || compareString(inputs[2], "-r"))  {
                std::string line;
                getline(temporal, line);
                if (!compareString(line, "") && !compareString(line, " ")) {
                    clearFile(temporal, std::string(directory) + "/prob/temporal");
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
                            for (int i = 0; i < int(filesAdded.size()); i++) {
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
void backupCommand() {
    std::ifstream config(std::string(directory) + "/prob/config");
    std::ifstream temporal(std::string(directory) + "/prob/temporal");
    std::fstream logs(std::string(directory) + "/prob/logs", std::ios::in | std::ios::out | std::ios::ate);
    int filesSaved = 0;
    
    if (config.is_open() && temporal.is_open() && logs.is_open()) {
        std::string path, line;
        getline(config, path);
        if (!compareString(path, "") && !compareString(path, " ")) {
            while(getline(temporal, line)) {
                if (line.find("/") != std::string::npos) {
                    std::string folder = path, toAddLine;
                    int i = 0;
                    while(line[i] != line[line.length()]) {
                        if (line[i] == '/') {
                            folder+= toAddLine + "/";
                            toAddLine.clear();
                            i++;
                            if (!opendir(folder.c_str())) {
                                createFolder(folder);
                            } 
                        } else {
                            toAddLine += line[i];
                            i++;
                        }
                    }
                }
                copyFile(std::string(directory) + "/" + line, path + line);
                filesSaved++;
            }
            std::cout << "Possible files were saved" << std::endl;
            // Saving the backup history on logs folder
            time_t now = std::time(0);
            char* time_string = std::ctime(&now);
            logs << filesSaved << " files saved on " << std::string(time_string);

            // Closing opened files
            config.close();
            temporal.close();
            logs.close();
        } else {
            std::cout << "Path not configured, run 'prob config path <path>' to configure it" << std::endl;
        }
    } else {
        std::cout << "[ERROR/s]: file couldn't be found, try running 'prob init' set up the environment" << std::endl;
    }
}

// Not yet implemented, makes a segmentation fault 11
void singleBackup(const char* inputs[], int num) {
    std::cout << "Single backup" << std::endl;
    if (inputs[3] != NULL) {
        if (opendir(inputs[3])) {
            std::string inputPath = inputs[3];
            std::string path = inputPath[inputPath.length()] == '/' ? inputPath : inputPath + '/';
            if (compareString(inputs[4], "-f") || compareString(inputs[4], "--file")) {
                for (int fileInput = 5; fileInput < num; fileInput++) {
                    copyFile(std::string(directory)+ "/" + inputs[fileInput], path + inputs[fileInput]);
                }
            } else {
                stringvec filesToCopy;
                std::cout << "Single all" << std::endl;
                read_directory(std::string(directory), filesToCopy, "");
                for (int i = 0; i < int(filesToCopy.size()); i++) {
                    copyFile(std::string(directory)+ "/" + filesToCopy[i], path + filesToCopy[i]);
                }
            }
        } else {
            std::cout << "Path specified is not a directory" << std::endl;
        }
    } else {
        std::cout << "[ERROR/s]: No path specified" << std::endl;
    }
}
