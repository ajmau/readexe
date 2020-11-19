#include <iostream>

using namespace std;

/*
    Tiedosto sekalaisia funktioita varten. print_help() voisi tällä hetkellä olla main.cpp:ssä,
    mutta järjestelyä ja esimerkkiä varten se on laitettu tänne.
*/

void print_help(char* program_name) {
    cout << "Usage: " << program_name << " -p <pid>" << endl;
    cout << "Options: " << endl;
    cout << "\t-h\tnäytä tämä viesti\n\t-f\tylikirjoita output-tiedosto\n\t-p <pid>\n\t-o <output>\n\t-x\ttee tiedostosta suoritettava\n\t-s\ttulosta syöte stdout:iin\n\t-F\tAvaa interaktiivisen valikon avattujen tiedostojen tallentamiseen" << endl;
}
