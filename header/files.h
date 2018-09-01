#pragma once

#include "config.h"
#include "pathFuncs.h"

void copyFile(std::string pathFile, std::string pahToCopy);
bool seeIfInList(std::string thing, stringvec array);
void clearFile(std::fstream& fileToClear, std::string path);
//void readFile(std::fstream& file, std::string& toCopy);
