#include "header/config.h"
#include "header/pathFuncs.h"
#include "header/commands.h"

std::string getExePath(std::string path) {
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

void parserCommand(const char* inputs[], int number) {
    if (std::string(inputs[1]).compare("init") == 0) {
        initCommand(inputs, number);
    } else if (std::string(inputs[1]).compare("config") == 0) {
        configCommand(inputs, number);
    }  
    else {
        showHelp(workdir + "dist/help.txt");
    }
}

int main(int argc, const char* argv[]) {
    getcwd(directory, MAX_INPUT);
    workdir = getExePath(argv[0]);
    if (argc > 1) {
        parserCommand(argv, argc);
    } else {
        showHelp(workdir + "dist/help.txt");
    }
    
    return 0;
}