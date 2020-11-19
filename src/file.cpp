#include <iostream>
#include <fstream>
#include <string.h>
#include <errno.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <unistd.h>
#include <dirent.h>
#include <experimental/filesystem>
#include "file.h"
#include "util.h"

using namespace std;

void recover_files(string path);
void copy_file(string input, string output);

void read_proc(string file, string output, Settings *settings) {
    string path = "/proc/" + file + "/exe";

    // jos force parametria ei käytetä, tarkistetaan onko saman nimistä tiedostoa olemassa 
    if (!(settings->force)) {
        if (access(output.c_str(), F_OK) == 0) {
            cout << "Tiedosto on jo olemassa. Käytä -f parametria, ylikirjottamiseen." << endl;
            return;
        }
    }

    if (settings->recover_files) {
        recover_files(file);
    }

    // kopioidaan exe-tiedosto, jos output tiedosto on määritetty
    if (output != "") {
	    copy_file(path, output);
    }

    // tulostetaan exe-tiedosto stdouttiin, jos käyttäjä niin haluaa
    if (settings->stdout) {
	    cout << "printing to stdout" << endl;
	    ifstream source(path, ios::binary);
	    cout << source.rdbuf();
    }


    if (settings->exec) {
	    chmod(output.c_str(), S_IXUSR | S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
    }

}

void recover_files(string pid)
{
    string path = "/proc/" + pid + "/fd";
    string valinta;

    cout << path << endl;
    DIR *dir;
    struct dirent *en;
    dir = opendir(path.c_str());
    if (dir){
        while ((en = readdir(dir)) != NULL) {
            cout << en->d_name << endl;
        }
        closedir(dir);
    }

    cout << "Valitse file descriptorcriptor haluat palauttaa: ";
    cin >> valinta;

    while (valinta != "q") {
        copy_file(path+"/"+valinta, valinta);
        cout << "Valitse file descriptorcriptor haluat palauttaa: ";
        cin >> valinta;
    }
}

void copy_file(string input, string output) {
    ifstream source(input, ios::binary);

    if (!source) {
    	if (errno == ENOENT) {
    		cout << "Tiedostoa " << input << " ei löydy" << endl;
    		return;
	    }
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


