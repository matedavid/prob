#pragma once

#include "config.h"

void read_directory(const std::string& name, stringvec& v);
int createfile(std::string filePath, std::string fileType);
int createFolder(std::string folderPath);