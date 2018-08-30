#pragma once

#include "config.h"
#include "extraFuncs.h"
#include "pathFuncs.h"
#include "codification.h"
#include "files.h"

void initCommand(const char* inputs[], int num);
void configCommand(const char* inputs[], int num);
void addCommand(const char* inputs[], int num);
void backupCommand(const char* inputs[], int num);
void singleBackup(const char* inputs[], int num);