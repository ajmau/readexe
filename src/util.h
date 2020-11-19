#pragma once
#include <string>

typedef struct {
    bool force;
    bool exec;
    bool stdout;
    bool recover_files;
} Settings;

void print_help(char* program_name);
