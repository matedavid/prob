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
    int success = createFolder((std::string)directory + "/gitc");
    if (success == 0) {
        std::cout << "Folder created succesfully on " + (std::string)directory + "/gitc" << std::endl;

        int config = createfile((std::string)directory + "/gitc/config", "Config");
        int logs = createfile((std::string)directory + "/gitc/logs", "Logs");
        int source = createfile((std::string)directory + "/gitc/source", "Source");
        int temporal = createfile((std::string)directory + "/gitc/temporal", "Temporal");
        if (config && logs && source && temporal) {
            std::cout << "[SUCCESS]: Gitc environment created succesfully" << std::endl;
        } else {
            std::cout << "[ERROR/s]: Some files may not be created" << std::endl;
        }
    } else {
        std::cout << "gitc folder already created" << std::endl;
    }
}

void configCommand(const char* inputs[], int num) {
    bool flags = num > 2 ? true : false;

    if (flags) {
        std::fstream config((std::string)directory + "/gitc/config");
        if (config.is_open()) {
            
        } else {
            std::cout << "[ERROR/s]: Config file not found, try running 'gitc init again'" << std::endl;
        }

        config.close();
    } else {
        showHelp(workdir + "dist/spec/");
    }
}

