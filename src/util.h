#pragma once

/*
    Taulukko tässä tilanteessa on turha, mutta käytän sitä harjoituksen vuoksi.
*/
typedef struct {
    bool force;
    bool exec;
    bool stdout;
    bool recover_files;
} Settings;

void print_help(char* program_name);
