#include "header/config.h"
#include "header/pathFuncs.h"
#include "header/extraFuncs.h"
#include "header/files.h"
#include "header/commands.h"

// Parses the input from the terminal and does the input action
void parserCommand(const char* inputs[], int number) {
     // Check if prob folder is created
    if (opendir(directory)) {
        if (compareString(inputs[1], "init")) {
            initCommand();
        } else if (compareString(inputs[1], "config")) {
            configCommand(inputs, number);
        } else if (compareString(inputs[1], "add")) {
            addCommand(inputs, number);
        } else if (compareString(inputs[1], "backup")) {
            int single = (inputs[2] != NULL) ? (compareString(inputs[2], "-s") || compareString(inputs[2], "--single")) ? 1 : 0 : 0;
            if (single) {
                singleBackup(inputs, number);
            } else {
                backupCommand();
            }
        } else {
            showHelp(workdir + "dist/help.txt");
        }
    } else {
        std::cout << "[ERROR/s]: Couldn't find prob folder, run 'prob init' to create the environment" << std::endl;
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
