#include "header/config.h"
#include "header/pathFuncs.h"
#include "header/codification.h"
#include "header/extraFuncs.h"
#include "header/files.h"
#include "header/commands.h"

// Parses the input from the terminal and does the input action
void parserCommand(const char* inputs[], int number) {
     // Check if prob folder is created by looking if a file included exists
    std::ifstream file(std::string(directory) + "/prob/config");  
    if (file.is_open() || compareString(std::string(inputs[1]), "init")) {
        if (compareString(inputs[1], "init")) {
            initCommand(inputs, number);
            file.close();
        } else if (compareString(inputs[1], "config")) {
            configCommand(inputs, number);
            file.close();
        } else if (compareString(inputs[1], "add")) {
            addCommand(inputs, number);
            file.close();
        } else if (compareString(inputs[1], "backup")) {
            backupCommand(inputs, number);
            file.close();
        } else {
            showHelp(workdir + "dist/help.txt");
            file.close();
        }
    } else {
        std::cout << "[ERROR/s]: couldn't find prob folder, run 'prob init' to set up the environment" << std::endl;
        file.close();
    }
}

int main(int argc, const char* argv[]) {
    getcwd(directory, MAX_INPUT); // Gets the directory where the program is beeing executed
    workdir = getFilePath(argv[0]); // Gets the directory where the program is localted
    if (argc > 1) {
        parserCommand(argv, argc);
    } else {
        showHelp(workdir + "dist/help.txt");
    }
    
    return 0;
}