#include <iostream>
#include <fstream>
#include <string>
#include <array>
using namespace std;

const int N=50;
typedef array <string, N> Poema;

void leer_poema(const string &fichero, Poema &poema);

int main() {
    const string fichero="poema.txt";
    Poema poema={""};
    leer_poema(fichero, poema);
    for(unsigned i=0; i<N; ++i) {cout<<poema[i]<<endl;}
}

void leer_poema(const string &fichero, Poema &poema) {
    ifstream fi;
    string linea;
    fi.open(fichero);
    if(!fi.fail()) {
        for(unsigned i=0; !fi.eof() && i<N; ++i) {
            getline(fi, linea);
            poema[i]=linea;
        } // Se podría hacer con while(!fi.eof()) a sabiendas de que hay menos líneas que índices del array.
    }
}