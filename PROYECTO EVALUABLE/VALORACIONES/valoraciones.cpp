/***********************************************************************************
 * Fichero valoraciones.cpp para la implementación de los métodos de la clase
 * Valoraciones para la gestión de la información correspondiente a una lista de 
 * valoraciones de alojamientos turísticos.
 *
 * Alumno/a: Ramón Montoro Mazuela
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

    // Constructor por defecto.
    // Inicializa todas las listas (valoraciones,
    // palabras positivas y palabras negativas)
    // a listas vacías
    Valoraciones::Valoraciones(): valoraciones{}, num_valoraciones{}, pal_pos{}, pal_neg{} {}

    // Constructor de copia
    Valoraciones::Valoraciones(const Valoraciones &otro_objeto): valoraciones{copiarValoraciones(otro_objeto.valoraciones)}, num_valoraciones{otro_objeto.num_valoraciones}, pal_pos{otro_objeto.pal_pos}, pal_neg{otro_objeto.pal_neg} {}

    // Destructor
    Valoraciones::~Valoraciones() {
        borrarValoraciones(valoraciones);
    }

    // Busca una valoración por su id_valoracion en una lista de valoraciones.
    // Devuelve un puntero 'ptr' apuntando a un nodo que contiene un id de valoración
    // mayor o igual que el que estoy buscando (o a nullptr, si no existe tal nodo),
    // y un puntero 'ant' apuntando al nodo anterior a ese nodo al que apunta 'ptr'
    // (o a nullptr, si 'ptr' apunta al primer nodo de la lista o la lista está vacía).
    // PARÁMETROS:
    //  - id_valoracion (E) : id de la valoración que estoy buscando
    //  - lista (E): lita de valoraciones en la que buscar la valoración
    //  - ptr (S): puntero que apunta a un nodo con id_valoracion mayor o igual que
    //             'id_valoracion'
    //  - ant (S): puntero que apunta al nodo anterior al que apunta 'ptr'
    //  - encontrada (S): indica si ha encontrado ese id de valoración o no
    void Valoraciones::buscarValoracion(unsigned id_valoracion,
                            Valoraciones::PtrValoracion lista,
                            Valoraciones::PtrValoracion &ptr,
                            Valoraciones::PtrValoracion &ant,
                            bool &encontrada) const;

    // Inserta una valoración en la lista de valoraciones que
    // se pasa como parámetro. Si la valoración se ha podido
    // insertar correctamente, se devuelve OK a través de 'res'.
    // Si la valoración ya existía, se devuelve YA_EXISTE a
    // través de 'res'. La valoración debe insertarse en
    // orden creciente de id de valoración.
    // PARÁMETROS:
    //  - valoracion (E): valoración a insertar
    //  - lista (ES): lista de valoraciones donde se inserta
    //  - res (S): resultado de la operación
    void insertarValoracion(const Valoracion &valoracion, PtrValoracion &lista, Resultado &res) const;

    // Elimina una valoración cuyo identificador se pasa como parámetro
    // de la lista de valoraciones que se pasa también como parámetro.
    // Si se encuentra la valoración en la lista, se elimina y se
    // devuelve OK a través de 'res'. Si no, se devuelve NO_EXISTE
    // a través de 'res'.
    // PARÁMETROS:
    //  - id_valoracion (E): id de la valoración a eliminar
    //  - lista (ES): lista de valoraciones
    //  - res (S): resultado de la operación
    void eliminarValoracion(unsigned id_valoracion, PtrValoracion &lista, Resultado &res) const;

    // Borra completamente una lista de valoraciones
    // PARÁMETROS:
    //  - lista (ES): lista de valoraciones a borrar
    void borrarValoraciones(PtrValoracion &lista) const;

    // Devuelve una copia de la lista de valoraciones que se pasa
    // como parámetro.
    // PARÁMETROS:
    //  - lista (E): lista de valoraciones original
    PtrValoracion copiarValoraciones(PtrValoracion lista) const;

    // Lee desde fichero la lista de palabras positivas
    // y la almacena en el objeto. Si el fichero ha podido abrirse
    // correctamente para lectura, devuelve OK a través de 'res'. Si no,
    // devuelve FIC_ERROR.
    // Parámetros:
    //  - nombre_fic (E): nombre del fichero de palabras positivas
    //  - res (S): resultado de la apertura del fichero para lectura
    void cargarPalabrasPositivas(const std::string &nombre_fic, Resultado &res);

    // Lee desde fichero la lista de palabras negativas
    // y la almacena en el objeto. Si el fichero ha podido abrirse
    // correctamente para lectura, devuelve OK a través de 'res'. Si no,
    // devuelve FIC_ERROR.
    // Parámetros:
    //  - nombre_fic (E): nombre del fichero de palabras positivas
    //  - res (S): resultado de la apertura del fichero para lectura
    void cargarPalabrasNegativas(const std::string &nombre_fic, Resultado &res);

    // Lee valoraciones de un fichero de valoraciones y las incorpora
    // (añadiéndolas a las ya existentes) a la lista de valoraciones
    // actual.
    // Antes de insertar la valoración en la lista de valoraciones debe
    // analizarse y actualizarse el sentimiento (positivo, negativo o neutro)
    // del comentario que incluye.
    // La valoraciones deben insertarse en orden creciente de identificador
    // de valoración dentro de la lista de valoraciones.
    // Si el fichero puede abrirse correctamente para lectura, se leen las valoraciones,
    // se incorporan al objeto actual y se devuelve OK a través de 'res'. Si no,
    // se devuelve FIC_ERROR  a través de 'res'.
    // FORMATO DEL FICHERO:
    //  - El fichero debe comenzar con la siguiente cabecera (véase 'valoraciones.csv'):
    //      id_alojamiento,id_valoracion,fecha,id_revisor,nombre_revisor,comentario
    //  - Los datos deben separarse con comas
    //  - Si el nombre del revisor incluye comas, aparecerá en el fichero entre comillas dobles.
    //    Por ejemplo: "Smith, John"
    //  - Si el nombre del revisor NO incluye comas, no aparecerá en el fichero entre comillas dobles.
    //    Por ejemplo: John Smith
    //  - Si el comentario incluye comas, aparecerá en el fichero entre comillas dobles.
    //    Por ejemplo: "Este comentario, como puede verse, incluye comas"
    //  - Si el comentario no incluye comas, no aparecerá entre comillas dobles.
    //    Por ejemplo: Este comentario no necesita comillas porque no incluye comas
    // PARÁMETROS:
    //  - nombre_fic (E): nombre del fichero de valoraciones
    //  - res (S): resultado de la operación
    void cargarValoraciones(const std::string &nombre_fic, Resultado &res);

    // Guarda en el fichero cuyo nombre se pasa como parámetro todas las valoraciones
    // de la lista de valoraciones.
    // El formato del fichero es el mismo que para el método 'cargarValoraciones'
    // (véase el fichero 'valoraciones.csv'). Si el fichero puede abrirse para escritura,
    // se guardan en él las valoraciones y se devuelve OK a través de 'res'. Si no,
    // se devuelve FIC_ERROR a través de 'res'.
    // PARÁMETROS:
    //  - nombre_fic (E): nombre del fichero de escritura
    //  - res (S): resultado de la operación
    void guardarValoraciones(const std::string &nombre_fic, Resultado &res) const;

    // Analiza y actualiza el sentimiento de una valoración cuyo identificador se pasa como parámetro.
    // Si la valoración está en la lista de valoraciones del objeto, se analiza y actualiza
    // su sentimiento en función del umbral que se pasa como parámetro; además, se devuelve
    // OK a través de 'res'. Si no existe la valoración, se devuelve NO_EXISTE a través de 'res'.
    void actualizarSentimiento(unsigned id_valoracion, unsigned umbral, Resultado &res);

    // Analiza y actualiza el sentimiento de todas las valoraciones a partir de las listas de palabras
    // positivas y negativas actuales almacenadas en el objeto y en función del umbral
    // indicado.
    // Parámetros:
    //  - umbral (E): umbral para clasificar la valoración en positiva, negativa o neutra
    void actualizarSentimientos(unsigned umbral);

    // Inserta una nueva palabra en la lista de palabras positivas
    // Parámetros:
    //  - palabra (E): nueva palabra a insertar en la lista de palabras positivas
    //  - res (S): resultado de la operación
    void insertarPalabraPositiva(const std::string &palabra, Resultado &res);

    // Inserta una nueva palabra en la lista de palabras negativas
    // Parámetros:
    //  - palabra (E): nueva palabra a insertar en la lista de palabras negativas
    //  - res (S): resultado de la operación
    void insertarPalabraNegativa(const std::string &palabra, Resultado &res);

    // Elimina una nueva palabra de la lista de palabras positivas
    // Parámetros:
    //  - palabra (E): palabra a eliminar de la lista de palabras positivas
    //  - res (S): resultado de la operación
    void eliminarPalabraPositiva(const std::string &palabra, Resultado &res);

    // Elimina una nueva palabra de la lista de palabras negativas
    // Parámetros:
    //  - palabra (E): palabra a eliminar de la lista de palabras negativas
    //  - res (S): resultado de la operación
    void eliminarPalabraNegativa(const std::string &palabra, Resultado &res);

    // Devuelve el número de valoraciones positivas, negativas y neutras almacenadas.
    // PARÁMETROS:
    //  - positivas (S): número de valoraciones positivas
    //  - negativas (S): número de valoraciones negativas
    //  - neutras (S): número de valoraciones neutras
    void numeroValoraciones(unsigned &positivas, unsigned &negativas, unsigned &neutras) const;

    // Devuelve la lista de los identificadores de todas las valoraciones
    // almacenadas, positivas, negativas y neutras.
    // PARÁMETROS:
    //  - ids_positivas (S): ids de todas las valoraciones positivas
    //  - ids_negativas (S): ids de todas las valoraciones negativas
    //  - ids_neutras (S): ids de todas las valoraciones neutras
    void listaValoraciones(Ids &ids_positivas, Ids &ids_negativas, Ids &ids_neutras) const;

    // Devuelve el número de palabras positivas y negativas almacenadas
    // PARÁMETROS:
    //  - positivas (S): número de palabras positivas
    //  - negativas (S): número de palabras negativas
    void numeroPalabras(unsigned &positivas, unsigned &negativas) const;

    // Indica si una valoración, cuyo id se pasa como parámetro,
    // está en la lista de valoraciones.
    // Si está, se devuelve a través de 'valoracion' y se pone 'encontrada' a true
    // PARAMETROS:
    //  - id_valoracion (E): identificador de la valoración a buscar
    //  - valoracion (S): valoración
    //  - encontrada (S): indica si se ha encontrado (true) o no (false) la valoración
    void buscarValoracion(unsigned id_valoracion, Valoracion &valoracion, bool &encontrada) const;

    // Inserta una valoración en la lista de valoraciones, en orden creciente
    // de identificador de valoración. No puede haber dos valoraciones repetidas
    // (es decir, con el mismo id de valoración) en el objeto. Si la valoración
    // se ha insertado con éxito, se devuelve OK a través de 'res'. Si la valoración
    // ya existía, se devuelve YA_EXISTE.
    // PARÁMETROS:
    //  - valoracion (E): valoración a insertar
    //  - res (S): resultado de la operación
    void insertarValoracion(const Valoracion &valoracion, Resultado &res);

    // Elimina una valoración cuyo id se pasa como parámetro.
    // Si la valoración se encuentra, se devuelve OK a través de
    // res. Si no, se devuelve NO_EXISTE.
    // PARÁMETROS:
    //  - id_valoracion (E): valoración que quiere elminarse
    //  - res (S): resultado de la operación
    void eliminarValoracion(unsigned id_valoracion, Resultado &res);

    // Modificar una valoración existente con los nuevos datos de la misma que se pasan
    // a través del parámetro 'valoracion'. Si la valoración existe
    // (existe ese id de valoración) se modifica (se sustituye por la nueva
    // valoración) y se devuelve OK a través de 'res'.
    // Si no, se devuelve NO_EXISTE.
    // Parámtros:
    //  - valoracion (E): nueva valoración (para sustituir la existente)
    //  - res (S): resultado de la operación
    void modificarValoracion(const Valoracion &valoracion, Resultado &res);

    // Devuelve la lista de identificadores de valoraciones.
    // PARÁMETROS:
    //  - id_alojamiento (E): identificador de un alojamiento
    //  - ids_valoraciones (S): lista de ids de valoraciones del alojamiento
    void valoracionesAlojamiento(unsigned id_alojamiento, Ids &ids_valoraciones) const;

    // Devuelve la lista de valoraciones para un determinado revisor.
    // PARÁMETROS:
    //  - id_revisor (E): identificador de un revisor
    //  - ids_valoraciones (S): lista de ids de valoraciones del revisor
    void valoracionesRevisor(unsigned id_revisor, Ids &ids_valoraciones) const;

    // Escribe por pantalla los datos de todas las valoraciones,
    // en el siguiente formato (nótese que se
    // usan tabuladores para formatear la salida):
    //  --- ID alojamiento:      <id_alojamiento>
    //  ID valoración:       <id_alojamiento>
    //  Fecha:               <fecha>
    //  ID revisor:          <id_revisor>
    //  Nombre revisor:      <nombre_revisor>
    //  --- COMENTARIO:
    //  <comentario>
    //  *** SENTIMIENTO: positivo/negativo/neutro
    //
    // Deben salir primero las valoraciones positivas y luego las negativas.
    void escribir() const;
} // namespace bblProg2