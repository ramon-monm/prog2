/***********************************************************************************
 * Fichero utilidades.cpp para la implementación de funciones auxiliares para
 * el proyecto evaluable.
 *
 * Alumno/a:
 * Fecha:
 * *********************************************************************************/

#include "utilidades.hpp"

namespace bblProg2
{
    // Escribe por pantalla la cadena de caracteres
    // correspondiente al error.
    // Parámetros:
    // 		- res (E): código de error
    void escribirResultado(const Resultado &res)
    {
        switch (res)
        {
        case OK:
            std::cout << " --- OK." << std::endl;
            break;
        case VAL_ERROR:
            std::cout << " --- ERROR DE VALOR." << std::endl;
            break;
        case FIC_ERROR:
            std::cout << " --- ERROR DE FICHERO. " << std::endl;
            break;
        case NO_EXISTE:
            std::cout << " --- NO EXISTE. " << std::endl;
            break;
        case YA_EXISTE:
            std::cout << " --- YA EXISTE. " << std::endl;
            break;
        case LISTA_LLENA:
            std::cout << " --- LISTA LLENA." << std::endl;
            break;
        default:
            std::cout << " --- CÓDIGO DE ERROR DESCONOCIDO." << std::endl;
        }
    }
}