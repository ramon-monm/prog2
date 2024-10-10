#include "utilidades.hpp"
#include <iostream>

using namespace std;

namespace bblProg2
{

    // Escribe por pantalla la cadena de caracteres
    // correspondiente al error.
    // Parámetros:
    // 		- res (E): código de error
    void escribir_resultado(const Resultado &res)
    {
        switch (res)
        {
        case OK:
            cout << " --- OK." << endl;
            break;
        case VAL_ERROR:
            cout << " --- ERROR DE VALOR." << endl;
            break;
        case FIC_ERROR:
            cout << " --- ERROR DE FICHERO. " << endl;
            break;
        case NO_EXISTE:
            cout << " --- NO EXISTE. " << endl;
            break;
        case YA_EXISTE:
            cout << " --- YA EXISTE. " << endl;
            break;
        case LISTA_LLENA:
            cout << " --- LISTA LLENA." << endl;
            break;
        default:
            cout << " --- CÓDIGO DE ERROR DESCONOCIDO." << endl;
        }
    }
}