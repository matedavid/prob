#pragma once

#include "config.h"
#include "extraFuncs.h"
#include "files.h"

void read_directory(const std::string& name, stringvec& v, std::string toAdd);
int createfile(std::string filePath, std::string fileType);
int createFolder(std::string folderPath);
std::string getFilePath(std::string path);