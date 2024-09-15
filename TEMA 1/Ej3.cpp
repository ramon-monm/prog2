#include <iostream>
#include <fstream>
#include <string>
using namespace std;

void cambiar_may_min(const string &fichero_i, const string &fichero_o);

int main() {
    const string fichero_ent="texto.txt", fichero_sal="texto_may_min.txt";
    cambiar_may_min(fichero_ent, fichero_sal);
}

void cambiar_may_min(const string &fichero_i, const string &fichero_o) {
    ifstream fi; ofstream fo;
    char ch;
    fi.open(fichero_i);
    if(!fi.fail()) {
        fi.get(ch);
        while(!fi.eof()) {
            if(ch>='A' && ch<='Z') {ch+=32;}
            // Flujo de salida
            fi.get(ch);
        }
    }
}