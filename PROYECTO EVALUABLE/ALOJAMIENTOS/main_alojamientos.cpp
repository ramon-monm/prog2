#include "utilidades.hpp"
#include "alojamiento.hpp"
#include "alojamientos.hpp"

#include <iostream>
#include <fstream>
#include <array>

using namespace std;
using namespace bblProg2;

int main() {
    Alojamientos alojamientos, alojamientos_anfitrion;
    Resultado resultado;
    alojamientos.leerAlojamientos("alojamientos.csv", resultado);
    cout<<endl<<alojamientos.numeroAlojamientos()<<endl;
    Alojamientos alojamientos_copia(alojamientos);
    
    Alojamiento alojamiento;
    alojamientos.consultarAlojamiento(3582817, alojamiento, resultado);
    cout<<endl;
    alojamiento.escribir();
    escribirResultado(resultado);
    
    Ids identificadores;
    alojamientos.alojamientosAnfitrion(784312, identificadores);
    for(unsigned i=0; i<identificadores.num_ids; ++i) {
        alojamientos.consultarAlojamiento(identificadores.ids[i], alojamiento, resultado);
        alojamientos_anfitrion.insertarAlojamiento(alojamiento, resultado);
    }
    cout<<endl;
    alojamientos_anfitrion.escribir();

    alojamientos_copia.consultarAlojamiento(42808, alojamiento, resultado);
    alojamiento.asignarNombre("Habitacion tranquila en el centro de Estocolmo");
    alojamiento.asignarNombreAnfitrion("Antonia");
    alojamientos_copia.modificarAlojamiento(alojamiento, resultado);
    alojamientos_copia.escribirEnFichero("alojamientos_copia.csv", resultado);
}