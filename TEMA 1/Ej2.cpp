#include <iostream>
#include <fstream>
#include <string>
using namespace std;

typedef struct {
    unsigned may;
    unsigned min;
    unsigned esp;
} Estadisticas;

void estadisticas_texto(const string &fichero, Estadisticas &est);

int main() {
    const string fichero="texto.txt";
    Estadisticas stats;
    estadisticas_texto(fichero, stats);
    cout<<stats.may<<" "<<stats.min<<" "<<stats.esp<<endl;
}

void estadisticas_texto(const string &fichero, Estadisticas &est) {
    char ch;
    ifstream fi;
    fi.open(fichero);
    if(!fi.fail()) {
        est.may=0; est.min=0; est.esp=0;
        fi.get(ch);
        while(!fi.eof()) {
            if(ch>='A' && ch<='Z') {++est.may;}
            else if(ch>='a' && ch<='z') {++est.min;}
            else if(ch==' ') {++est.esp;}
            fi.get(ch);
        }
    }
}