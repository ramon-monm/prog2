/***********************************************************************************
 * Fichero alojamiento.hpp para la definición del tipo Alojamiento.
 *
 * Alumno/a: Ramón Montoro Mazuela
 * Fecha: 19/09/2024
 * *********************************************************************************/

#ifndef __ALOJAMIENTO_HPP__
#define __ALOJAMIENTO_HPP__


#include <string>
#include <array>
#include <fstream>

namespace bblProg2
{
    struct Alojamiento
    {
        unsigned id_alojamiento;      // Identificador (único) del alojamiento
        std::string nombre;           // Nombre del alojamiento
        unsigned id_anfitrion;        // Identificador (único) del anfitrión
        std::string nombre_anfitrion; // Nombre del anfitrión
        std::string barrio;           // Barrio (zona) donde se ubica el apartamento
        double latitud, longitud;     // Latitud y longitud de la ubicación del apartamento
        std::string tipo_alojamiento; // Tipo de alojamiento
        double precio;                // Precio del alojamiento por cada día de estancia
        unsigned minimo_noches;       // Mínimo número de noches que se puede alquilar
        unsigned disponibilidad_365;  // Número de días al año que está disponible
    };

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
    void leer_alojamiento(std::ifstream &fic, Alojamiento &alojamiento);


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
    void escribir_alojamiento(std::ofstream &fic, const Alojamiento &alojamiento);
}

#endif