#pragma once

#include <iostream>
#include <string>
#include <fstream>
#include <limits.h>
#include <vector>
#include <dirent.h>
#include <unistd.h>
#include <sys/stat.h>

typedef std::vector<std::string> stringvec;

extern char directory[MAX_INPUT];
extern std::string workdir;
extern std::string notWantedFiles[5];
