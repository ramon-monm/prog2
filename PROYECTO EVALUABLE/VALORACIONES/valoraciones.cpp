/***********************************************************************************
 * Fichero valoraciones.cpp para la implementación de los métodos de la clase
 * Valoraciones para la gestión de la información correspondiente a una lista de 
 * valoraciones de alojamientos turísticos.
 *
 * Alumno/a: 
 * Fecha: 
 * *********************************************************************************/
#include "valoracion.hpp"
#include "valoraciones.hpp"
#include "palabras.hpp"
#include "utilidades.hpp"
#include <string>
#include <fstream>
#include <cassert>
#include <cctype>
#include <sstream>

using namespace std;

namespace bblProg2
{
    // --------------------- MÉTODOS PÚBLICOS IMPLEMENTADOS POR EL PROFESORADO (NO MODIFICAR)

    // Operador de asignación de la clase Valoraciones
    Valoraciones &Valoraciones::operator=(const Valoraciones &otro_objeto)
    {
        if (this != &otro_objeto)
        {
            borrarValoraciones(valoraciones);
            valoraciones = copiarValoraciones(otro_objeto.valoraciones);
            num_valoraciones = otro_objeto.num_valoraciones;
            pal_pos = otro_objeto.pal_pos;
            pal_neg = otro_objeto.pal_neg;
        }

        return *this;
    }

    // Operador de comparación de igualdad de Valoraciones
    // (SOLO NECESARIO PARA LAS PRUEBAS UNITARIAS.)
    // (IMPLEMENTADO POR EL PROFESORADO. NO MODIFICAR.)
    bool Valoraciones::operator==(const Valoraciones &otro_objeto) const
    {
        bool iguales = (num_valoraciones == otro_objeto.num_valoraciones &&
                        pal_pos == otro_objeto.pal_pos &&
                        pal_neg == otro_objeto.pal_neg);

        PtrValoracion ptr1 = valoraciones, ptr2 = otro_objeto.valoraciones;

        while (iguales && ptr1 != nullptr)
        {
            iguales = ptr1->valoracion == ptr2->valoracion;
            ptr1 = ptr1->sig;
            ptr2 = ptr2->sig;
        }

        return iguales;
    }

    // Función auxiliar
    // (SOLO NECESARIA PARA LAS PRUEBAS UNITARIAS.)
    // (IMPLEMENTADA POR EL PROFESORADO.)
    void Valoraciones::__consultar_elemento_pos(unsigned pos, bool val_pal, bool pos_neg, Valoracion &valoracion, std::string &palabra) const
    {
        assert((val_pal && pos < num_valoraciones) ||
               (!val_pal && pos_neg && pos < pal_pos.numPalabras()) ||
               (!val_pal && !pos_neg && pos < pal_neg.numPalabras()));

        if (val_pal) // Consulto valoración
        {
            PtrValoracion ptr = valoraciones;
            unsigned i = 0;
            while (i < pos)
            {
                ++i;
                ptr = ptr->sig;
            }
            valoracion = ptr->valoracion;
        }
        else // Consulto palabra
        {
            if (pos_neg) // Consulto palabra positiva
            {
                palabra = pal_pos[pos];
            }
            else // Consulto palabra negativa
            {
                palabra = pal_neg[pos];
            }
        }
    }
    // -----------------------------------------------------------------

    // IMPLEMENTACIÓN DE LOS MÉTODOS PÚBLICOS Y PRIVADOS

} // namespace bblProg2