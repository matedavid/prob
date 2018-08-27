#pragma once

#include "config.h"
#include "pathFuncs.h"
#include "codification.h"

void showHelp(std::string path);
void initCommand(const char* inputs[], int num);
void configCommand(const char* inputs[], int num);
void addCommand(const char* inputs[], int num);
void backupCommand(const char* inputs[], int num);