#include "alojamiento.hpp"
#include <string>
#include <fstream>
#include <iomanip>
#include <cassert>

using namespace std;

namespace bblProg2
{
    // Lee desde fichero los datos de un alojamiento.
    // FORMATO DEL FICHERO:
    //  - Los datos están separados por comas
    //  - Si el nombre del alojamiento incluye comas, aparecerá en el fichero entre comillas dobles.
    //    Por ejemplo: "Design, style & vintage by Odenplan"
    // PARÁMETROS:
    //  - fic (ES): flujo de fichero de entrada asociado a un fichero
    //      de lectura (abierto)
    //  - aloja (S): un alojamiento
    // PRECONDICIÓN: el flujo 'fic' está correctamente asociado a
    // un fichero de entrada que contiene datos de alojamientos
    // turísticos en el formato correcto (véase el fichero
    // "alojamientos.csv")
    void leer_alojamiento(std::ifstream &fic, Alojamiento &alojamiento)
    {
        char ch_aux;
        string str_aux;
        fic >> alojamiento.id_alojamiento;
        fic.ignore(); //  Ignoramos la coma con entrada natural.
        fic >> ch_aux;
        if (ch_aux == '"')
        {
            getline(fic, alojamiento.nombre, '"');
            fic.ignore();
        }
        else
        {
            getline(fic, str_aux, ',');
            alojamiento.nombre = ch_aux + str_aux;
        } // Si el primer caracter es ", lo ignoramos. Luego se lee la cadena de texto hasta ". Se ignora la ,.
        fic >> alojamiento.id_anfitrion;
        fic.ignore();
        getline(fic, alojamiento.nombre_anfitrion, ',');
        getline(fic, alojamiento.barrio, ',');
        fic >> alojamiento.latitud;
        fic.ignore();
        fic >> alojamiento.longitud;
        fic.ignore();
        getline(fic, alojamiento.tipo_alojamiento, ',');
        fic >> alojamiento.precio;
        fic.ignore();
        fic >> alojamiento.minimo_noches;
        fic.ignore();
        fic >> alojamiento.disponibilidad_365;
        fic.ignore();
    }

    // Escribe en fichero los datos de un alojamiento (veáse
    // el fichero "alojamientos.csv" para comprobar el
    // formato en el que deben escribirse los datos).
    // FORMATO DEL FICHERO:
    //  - Los datos deben separarse con comas
    //  - Si el nombre del alojamiento incluye comas, debe guardarse en el fichero entre comillas dobles.
    //    Por ejemplo: "Design, style & vintage by Odenplan"
    // PARÁMETROS:
    //  - fic (ES): flujo de fichero de salida asociado a un fichero
    //      de escritura (abierto)
    //  - aloja (E): un alojamiento
    // PRECONDICIÓN: el flujo 'fic' está correctamente asociado a
    // un fichero de salida
    void escribir_alojamiento(std::ofstream &fic, const Alojamiento &alojamiento)
    {
        unsigned pos;
        fic << alojamiento.id_alojamiento << ",";
        pos = alojamiento.nombre.find(',');
        if (pos != string::npos)
        {
            fic << '"' << alojamiento.nombre << '"';
        }
        else
        {
            fic << alojamiento.nombre;
        }
        fic << ",";
        fic << alojamiento.id_anfitrion << ",";
        fic << alojamiento.nombre_anfitrion << ",";
        fic << alojamiento.barrio << ",";
        fic << setprecision(15) << alojamiento.latitud << ",";
        fic << setprecision(15) << alojamiento.longitud << ",";
        fic << alojamiento.tipo_alojamiento << ",";
        fic << alojamiento.precio << ",";
        fic << alojamiento.minimo_noches << ",";
        fic << alojamiento.disponibilidad_365 << endl;
    }
}