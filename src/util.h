#pragma once
#include <string>

typedef struct {
    bool force;
    bool stdout;
} Settings;

void print_help(char* program_name);