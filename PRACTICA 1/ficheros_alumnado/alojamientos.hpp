/***********************************************************************************
 * Fichero alojamientos.hpp para la definición de tipos y funciones para la lectura
 * y escritura de ficheros de alojamientos turísticos.
 *
 * Alumno/a: Ramón Montoro Mazuela
 * Fecha: 19/09/2024
 * *********************************************************************************/

#ifndef __ALOJAMIENTOS_HPP__
#define __ALOJAMIENTOS_HPP__

#include "alojamiento.hpp"
#include "utilidades.hpp"

#include <string>
#include <array>

namespace bblProg2
{
    //---------- DEFINICIÓN DE LOS TIPOS Y CONSTANTES PRINCIPALES

    const unsigned MAX_ALOJAMIENTOS = 3000;

    struct Alojamientos
    {
        std::array<Alojamiento, MAX_ALOJAMIENTOS> alojamientos; // array de alojamientos
        unsigned num_alojamientos;                              // Número de alojamientos almacenados en la lista
    };

    //-------------------- DEFINICIÓN DE FUNCIONES PRINCIPALES

    // Lee de fichero los datos correspondientes a una serie de alojamientos y los
    // incorpora a los alojamientos existentes en la lista actual de alojamientos.
    // No puede haber alojamientos repetidos, esto es, alojamientos con el mismo
    // identificador de alojamiento. Si el fichero existe, se abre y se leen todos
    // los alojamientos almacenados en él, incorporándose a la lista de alojamientos
    // actual y devolviéndose OK a través de 'res'. Si el fichero no existe o no
    // puede abrirse para lectura, se devuelve FIC_ERROR a través de 'res'.
    // (VÉASE EL FORMATO DEL FICHERO EN escribir_alojamientos).
    // PARÁMETROS:
    //  - nombre_fichero (E): nombre del fichero de datos de alojamientos
    //  - alojas (ES): lista de alojamientos
    //  - res (S): resultado de la operación.
    void leer_alojamientos(const std::string &nombre_fichero, Alojamientos &alojas, Resultado &res);

    // Escribe en fichero los datos correspondientes a los
    // alojamientos existentes en la lista actual de alojamientos.
    // Si el fichero puede abrirse para escritura con éxito, se guardan en él
    // todos los alojamientos actuales y se devuelve OK a través de 'res'.
    // Si el fichero no puede abrirse para escritura, se devuelve FIC_ERROR
    // a través de 'res'.
    // FORMATO DEL FICHERO:
    //  - El fichero debe comenzar con la siguiente cabecera (véase 'alojamientos.csv'):
    //      id_alojamiento,nombre,id_anfitrion,nombre_anfitrion,barrio,latitud,longitud,tipo_alojamiento,precio,minimo_noches,disponibilidad_365
    //  - Los datos deben separarse con comas
    //  - Si el nombre del alojamiento incluye comas, debe guardarse en el fichero entre comillas dobles.
    //    Por ejemplo: "Design, style & vintage by Odenplan"
    // PARÁMETROS:
    //  - nombre_fichero (E): nombre del fichero de datos de alojamientos
    //  - alojas (E): lista de alojamientos
    //  - res (S): resultado de la operación.
    void escribir_alojamientos(const std::string &nombre_fichero, const Alojamientos &alojas, Resultado &res);

    // Inserta un alojamiento en la lista de alojamientos, en
    // ORDEN CRECIENTE de identificador del alojamiento. Si ya
    // existía un alojamiento con ese identificador, no se inserta
    // y se devuelve YA_EXISTE a través de 'res' (no puede haber
    // alojamientos con identificadores repetidos). Si no, si el
    // array está lleno, se devuelve LISTA_LLENA a través de 'res'.
    // Si no, se inserta el alojamiento en orden y se devuelve OK
    // a través de 'res'.
    // PARÁMETROS:
    //  - alojamiento (E): alojamiento a insertar
    //  - alojas (ES): lista de alojamientos
    //  - res (S): resultado de la operación
    void insertar_alojamiento(const Alojamiento &alojamiento, Alojamientos &alojas, Resultado &res);

} // namespace bblProg2

#endif