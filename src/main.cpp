#include <iostream>
#include <getopt.h>
#include<bits/stdc++.h> 
#include "file.h"
#include "util.h"

using namespace std;

int main(int argc, char **argv) {

    string pid = "";
    string output_file;
    // asetukset voisivat olla globaaleja, varsinkin näin pienessä ohjelmassa
    Settings settings;

    settings.force = false;
    settings.exec = false;
    settings.stdout = false;
    settings.recover_files = false;

    // luetaan ohjelman argumentit
    int opt;
    while ((opt = getopt(argc, argv, "hp:fo:xsF")) != EOF) {
        switch (opt) {
            // jos ohjelmalle on annettu -h parametri, printataan esimerkki ohjelman käytöstä
            case 'h': print_help(argv[0]); exit(0);
            case 'p': pid = optarg; break;
            case 'f': settings.force = true; break;
    	    case 'x': settings.exec = true; break;
    	    case 's': settings.stdout = true; break;
            case 'o': output_file = optarg; break;
            case 'F': settings.recover_files = true; break;
        }
    }

    // tarkistetaan, syöttikö käyttäjä ohjelman PID:n
    if (pid == "") {
        // jos ei ole, printataan ohjelman ohjeet
        print_help(argv[0]);
        exit(0);
    // tarkista jokaisen stringin kirjaimen kohdalta, onko se numero
    } else if (!all_of(pid.begin(), pid.end(), ::isdigit)) {
        cout << "ei ole numero" << endl;
        exit(0);
    }

    read_proc(pid, output_file, &settings);
}
