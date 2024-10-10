#ifndef __UTILIDADES_HPP__
#define __UTILIDADES_HPP__

namespace bblProg2
{
    //-------------------- DEFINICIÓN DE TIPOS Y CONSTANTES AUXILIARES

    // Resultado de las operaciones
    // (los valores de las constantes simbólicas son
    //  arbitrarios).
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
    // (IMPLEMENTADA POR EL PROFESOR)
    // Parámetros:
    // 		- res (E): código de error
    void escribir_resultado(const Resultado &res);

}

#endif