#include <iostream>
#include <fstream>
#include <string.h>
#include <errno.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <unistd.h>
#include <dirent.h>
#include "file.h"
#include "util.h"

using namespace std;

void recover_files(string path);
void copy_file(string input, string output);
void print_to_stdout(string file);

void read_proc(string file, string output, Settings *settings) {
    string path = "/proc/" + file + "/exe";

    // jos -f parametria ei käytetä, tarkistetaan onko saman nimistä tiedostoa olemassa 
    if (!(settings->force)) {
        if (access(output.c_str(), F_OK) == 0) {
            cout << "Tiedosto on jo olemassa. Käytä -f parametria, ylikirjottamiseen." << endl;
            return;
        }
    }

    // palautetaan tiedostoja, jos -F parametri valittiin
    if (settings->recover_files) {
        recover_files(file);
    }

    // kopioidaan exe-tiedosto, jos output tiedosto on määritetty
    if (output != "") {
	    copy_file(path, output);
    }

    // tulostetaan exe-tiedosto stdouttiin, jos -s parametri valittiin
    if (settings->stdout) {
        print_to_stdout(path);
    } 

    // asetetaan executable-bitti, jos -x parametri valittiin
    if (settings->exec) {
	    chmod(output.c_str(), S_IXUSR | S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
    }

}

void recover_files(string pid)
{
    string path = "/proc/" + pid + "/fd";
    string valinta;


    // loopataan /proc/pid/fd hakemisto ja tulostetaan tiedostot
    DIR *dir;
    struct dirent *en;
    dir = opendir(path.c_str());
    if (dir){
        while ((en = readdir(dir)) != NULL) {
            cout << en->d_name << endl;
        }
        closedir(dir);
    }

    // valinta täytyy lukea kerran ennen looppia, ettei yritetä kopioida tyhjää valintaa
    cout << "Valitse tiedosto jonka haluat palauttaa: ";
    cin >> valinta;

    // tulostetaan ja tallennetaan käyttäjän valitsemia tiedostoja kunnes käyttäjä syöttään q:n
    while (valinta != "q") {
        copy_file(path+"/"+valinta, valinta);
        print_to_stdout(path+"/"+valinta);
        cout << "Valitse tiedosto jonka haluat palauttaa (paina 'q' lopettaaksesi): ";
        cin >> valinta;
    }
}

void print_to_stdout(string file) {
        ifstream source(file, ios::binary);
	    cout << source.rdbuf();
        source.close();
}

void copy_file(string input, string output) {
    ifstream source(input, ios::binary);

    if (!source) {
        // ENOENT = tiedostoa ei löytynyt
    	if (errno == ENOENT) {
    		cerr << "Tiedostoa " << input << " ei löydy" << endl;
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


