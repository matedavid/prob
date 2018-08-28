#include "header/config.h"
#include "header/pathFuncs.h"
#include "header/codification.h"
#include "header/extraFuncs.h"
#include "header/files.h"
#include "header/commands.h"

void parserCommand(const char* inputs[], int number) {
    if (std::string(inputs[1]).compare("init") == 0) {
        initCommand(inputs, number);
    } else if (std::string(inputs[1]).compare("config") == 0) {
        configCommand(inputs, number);
    } else if (std::string(inputs[1]).compare("add") == 0) {
        addCommand(inputs, number);
    } else if (std::string(inputs[1]).compare("backup") == 0) {
        backupCommand(inputs, number);
    }
    else {
        showHelp(workdir + "dist/help.txt");
    }
}

int main(int argc, const char* argv[]) {
    getcwd(directory, MAX_INPUT);
    workdir = getFilePath(argv[0]);
    if (argc > 1) {
        parserCommand(argv, argc);
    } else {
        showHelp(workdir + "dist/help.txt");
    }
    
    return 0;
}