// Se trata de leer un fichero de texto con separadores (espacios y saltos de línea), CARACTER A CARACTER.

#include <iostream>
#include <fstream>
#include <string>
using namespace std;

void volcarFichero(ifstream &flujo); // Los flujos siempre se pasan al subalgoritmo como parámetro por referencia (&).

int main() {
    const string fichero="datoscar.in";
    char ch;
    ifstream fi;
    fi.open(fichero);
    if(fi.fail()) {
        cout<<"El fichero no se ha podido abrir correctamente"<<endl;
    }
    else {
        
        // fi>>ch no lee los separadores.
        /*
        fi.get(ch);
        while(!fi.eof()) {
            cout<<ch;
            // fi>>ch;
            fi.get(ch);
        }
        */

        // Lectura mediante un subalgoritmo.

        volcarFichero(fi);
        fi.close();
    }
    return 0;
}

void volcarFichero(ifstream &ff) {
    char car;
    ff.get(car);
    while(!ff.eof()) {
        cout<<car;
        ff.get(car);
    }
}