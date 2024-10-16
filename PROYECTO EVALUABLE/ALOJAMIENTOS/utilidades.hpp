/***********************************************************************************
 * Fichero utilidades.hpp para la definición de tipos y funciones auxiliares para
 * el proyecto evaluable.
 *
 * Alumno/a:
 * Fecha:
 * *********************************************************************************/

#ifndef __UTILIDADES__
#define __UTILIDADES__

#include <array>
#include <iostream>

namespace bblProg2
{
    // Resultado de las operaciones
    enum Resultado
    {
        OK,         // Okey
        VAL_ERROR,  // Error en los valores de los parámetros
        FIC_ERROR,  // Error en la apertura de fichero
        NO_EXISTE,  // El dato a consultar no existe
        YA_EXISTE,  // El dato a insertar ya existe
        LISTA_LLENA // El dato no puede insertarse: lista llena
    };

    // Escribe por pantalla la cadena de caracteres
    // correspondiente al error.
    // Parámetros:
    // 		- res (E): código de error
    void escribirResultado(const Resultado &res);

    // Array incompleto de identificadores de alojamientos
    // (necesario para alguno de los métodos de la clase Alojamientos)
    const unsigned MAX_NUM_IDS = 3000;
    struct Ids
    {
        std::array<unsigned, MAX_NUM_IDS> ids;
        unsigned num_ids;
    };
} // namespace bblProg2
#endif