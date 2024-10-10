#include <iostream>
#include <fstream>
#include <array>
#include <string>
#include "alojamiento.hpp"
#include "alojamientos.hpp"
#include "utilidades.hpp"
using namespace std;
using namespace bblProg2;

int main() {
    Alojamientos alojamientos; alojamientos.num_alojamientos=0;
    Resultado resultado;
    leer_alojamientos("alojamientos.csv", alojamientos, resultado);
    cout<<"Resultado de la lectura: "<<endl; escribir_resultado(resultado); cout<<endl;
    cout<<"Número de alojamientos leídos: "<<alojamientos.num_alojamientos<<endl;
    escribir_alojamientos("alojamientos_copia.csv.", alojamientos, resultado);
    cout<<"Resultado de la escritura: "<<endl; escribir_resultado(resultado); cout<<endl;
}