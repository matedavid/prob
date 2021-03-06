#pragma once

#include "config.h"
#include "extraFuncs.h"
#include "pathFuncs.h"
#include "files.h"

void initCommand();
void configCommand(const char* inputs[], int num);
void addCommand(const char* inputs[], int num);
void backupCommand();
void singleBackup(const char* inputs[], int num);
