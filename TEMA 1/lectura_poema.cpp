// Se trata de leer un fichero de texto, DE LÍNEA EN LÍNEA.

#include <iostream>
#include <fstream>
#include <string>
using namespace std;

void leerTexto(ifstream &f, string &texto);

int main() {
    string texto;
    ifstream fi;
    fi.open("poema.txt");
    if(!fi.fail()) {
        leerTexto(fi,texto);
        cout<<texto;
        fi.close();
    }
}

void leerTexto(ifstream &f, string &texto) {
    string linea;
    getline(f, linea); // Se lee la primera línea del fichero y se almacena en la variable.
    while(!f.eof()) { 
        texto+=linea+'\n'; // A la variable en conjunto, se le suma la variable que almacena la lectura de la línea y se hace un salto de línea para luego empezar un renglón más abajo.
        getline(f, linea); // Se lee la siguiente línea del fichero y se almacena.
        // La lectura ignorará la última línea del fichero. Para leerlo correctamente se haría:
        /*
        while(!f.eof()) {
            getline(f, linea);
            texto+=linea*'\n';
            }
        */
    }
}