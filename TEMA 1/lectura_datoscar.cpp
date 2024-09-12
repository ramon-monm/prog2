#include <iostream>
#include <fstream>
#include <string>
using namespace std;

int main() {
    const string fichero="datoscar.in";
    char ch;
    string str;
    ifstream fi;
    fi.open(fichero);
    if(fi.fail()) {
        cout<<"El fichero no se ha podido abrir correctamente"<<endl;
    }
    else {
        
        // Lectura de caracteres (caracter a caracter).
    
        // fi>>ch; // fi>>ch no lee los separadores.
        fi.get(ch);
        while(!fi.eof()) {
            cout<<ch;
            // fi>>ch;
            fi.get(ch);
        }
    }
    fi.close();
    return 0;
}