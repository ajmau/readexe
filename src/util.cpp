#include <iostream>

using namespace std;

void print_help(char* program_name) {
    cout << "Usage: " << program_name << " -p <pid>" << endl;
    cout << "Options: " << endl;
    cout << "\t-h\tshow this help message\n\t-f\tforce file creation\n\t-p <pid>\n\t-o <output file>\n\t-x\tset executable bit on output\n\t-s\ttulosta syöte stdout:iin\n\t-F\tAvaa interaktiivisen valikon avattujen tiedostojen tallentamiseen" << endl;
}
