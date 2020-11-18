#include <iostream>
#include <fstream>
#include <string.h>
#include <errno.h>
#include <sys/stat.h>
#include <unistd.h>
#include "file.h"
#include "util.h"

using namespace std;

void write_exe_stdout(string file) {
    string path = "/proc/" + file + "/exe";
    ifstream source(path, ios::binary);

    if (!source) {
        cerr << "Tiedostoa ei voitu avata: ";
        cerr << strerror(errno) << endl;
    }

    cout << source.rdbuf();
    source.close();
}

void read_exe_file(string file, string output, Settings *settings) {
    string path = "/proc/" + file + "/exe";
    fstream fs;

    if (!(settings->force)) {
        // tarkistetaan, onko tiedostoa olemassa
        if (access(output.c_str(), F_OK) == 0) {
            cout << "Tiedosto on jo olemassa. Käytä -f parametria, ylikirjottamiseen." << endl;
            return;
        }
    }

    ifstream source(path, ios::binary);

    if (!source) {
        cerr << "Tiedostoa ei voitu avata: ";
        cerr << strerror(errno) << endl;
    }

    ofstream dest(output, ios::binary);
    if (!dest) {
        cerr << "Tiedostoa ei voitu tallentaa: ";
        cerr << strerror(errno) << endl;
    } else {
        dest << source.rdbuf();
    }

    source.close();
    dest.close();

}