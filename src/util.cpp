#include <iostream>

using namespace std;

void print_help(char* program_name) {
    cout << "Usage: " << program_name << " -p <pid>" << endl;
    cout << "Options: " << endl;
    cout << "\t-f = force\n\t-p <pid>\n\t-o <output file>" << endl;
}
