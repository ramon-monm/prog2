/***********************************************************************************
 * Fichero alojamientos.cpp para la implementación las funciones para la lectura
 * y escritura de ficheros con información de alojamientos turísticos.
 *
 * Alumno/a: Ramón Montoro Mazuela
 * Fecha: 19/09/2024
 * *********************************************************************************/

#include "alojamiento.hpp"
#include "alojamientos.hpp"
#include "utilidades.hpp"
#include <array>
#include <string>
#include <fstream>
#include <cassert>
#include <iostream>

using namespace std;

namespace
{
    //------------------------ DEFINICIÓN DE FUNCIONES AUXILIARES

    // Busca un alojamiento por su identificador.
    // Devuelve la posición del array donde hay un alojamiento
    // cuyo identificador es mayor o igual que el que se está
    // buscando. Devuelve verdadero a través de 'encontrado' si
    // encuentra el alojamiento; devuelve falso en otro caso.
    // PARÁMETROS:
    //  - id_alojamiento (E): id del alojamiento a buscar
    //  - alojas (E): lista de alojamientos
    //  - posicion (S): posición en el array donde hay un alojamiento
    //                  con identificador mayor o igual.
    //  - encontrado (S): indica si se ha encontrado el id buscado
    void buscar_alojamiento(unsigned id_alojamiento, const bblProg2::Alojamientos &alojas, unsigned &posicion, bool &encontrado);

    // Abre hueco en el array, desplazando "a la derecha" todos
    // los alojamientos a partir de la posición que se pasa
    // como parámetro (incluida esta).
    // PARÁMETROS:
    //  - posicion (E): posición a partir de cual se abre hueco
    //  - alojas (ES): lista de alojamientos
    // PRECONDICIÓN: posicion <= num_alojamientos
    void abrir_hueco(unsigned posicion, bblProg2::Alojamientos &alojas);
}

//----------------------------------- IMPLEMENTACIÓN DE FUNCIONES DE ALOJAMIENTOS

namespace bblProg2
{

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
    void leer_alojamientos(const string &nombre_fichero, Alojamientos &alojas, Resultado &res)
    {
        Resultado res1;
        ifstream fic;
        fic.open(nombre_fichero);
        if (!fic.fail())
        {
            Alojamiento aux;
            fic.ignore(300, '\n');
            leer_alojamiento(fic, aux);
            while(!fic.eof()) {
                insertar_alojamiento(aux, alojas, res1);
                leer_alojamiento(fic, aux);
            }
            res = OK;
        }
        else
        {
            res = FIC_ERROR;
        }
    }

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
    void insertar_alojamiento(const Alojamiento &alojamiento, Alojamientos &alojas, Resultado &res)
    {
        unsigned posicion;
        bool encontrado;
        buscar_alojamiento(alojamiento.id_alojamiento, alojas, posicion, encontrado);
        if (!encontrado)
        {
            if (alojas.num_alojamientos < alojas.alojamientos.size())
            {
                if (posicion < alojas.num_alojamientos)
                {
                    abrir_hueco(posicion, alojas);
                }
                alojas.alojamientos[posicion] = alojamiento;
                ++alojas.num_alojamientos;
                res = OK;
            }
            else
            {
                res = LISTA_LLENA;
            }
        }
        else
        {
            res = YA_EXISTE;
        }

        /*ifstream fic;
        fic.open(nombre_fichero);
        if(!fic.fail()) {
            Alojamiento aux; unsigned pos; bool encontrado;
            while(alojas.num_alojamientos<alojas.alojamientos.size() && !fic.eof()) {
                leer_alojamiento(fic, aux);
                buscar_alojamiento(aux.id_alojamiento, alojas, pos, encontrado);
                if(!encontrado) {
                    if(pos!=alojas.num_alojamientos) {abrir_hueco(pos, alojas);}
                    alojas.alojamientos[pos]=aux; ++alojas.num_alojamientos;
                }
            }
            res=OK;
        }
        else {res=FIC_ERROR;}
        */
    }

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
    //  - La latitud y la longitud deben escribirse con una precisión de 15 dígitos (setprecision(15))
    // PARÁMETROS:
    //  - nombre_fichero (E): nombre del fichero de datos de alojamientos
    //  - alojas (E): lista de alojamientos
    //  - res (S): resultado de la operación.
    void escribir_alojamientos(const string &nombre_fichero, const Alojamientos &alojas, Resultado &res)
    {
        ofstream fic;
        fic.open(nombre_fichero);
        if (!fic.fail())
        {
            fic << "id_alojamiento,nombre,id_anfitrion,nombre_anfitrion,barrio,latitud,longitud,tipo_alojamiento,precio,minimo_noches,disponibilidad_365" << endl;
            for (unsigned i = 0; i < alojas.num_alojamientos; ++i)
            {
                escribir_alojamiento(fic, alojas.alojamientos[i]);
            }
            res = OK;
        }
        else
        {
            res = FIC_ERROR;
        }
    }
} // namespace bblProg2

// --------------------- IMPLEMENTACIÓN DE FUNCIONES AUXILIARES

namespace
{
    // Busca un alojamiento por su identificador.
    // Devuelve la posición del array donde hay un alojamiento
    // cuyo identificador es mayor o igual que el que se está
    // buscando. Devuelve verdadero a través de 'encontrado' si
    // encuentra el alojamiento; devuelve falso en otro caso.
    // PARÁMETROS:
    //  - id_alojamiento (E): id del alojamiento a buscar
    //  - alojas (E): lista de alojamientos
    //  - posicion (S): posición en el array donde hay un alojamiento
    //                  con identificador mayor o igual.
    //  - encontrado (S): indica si se ha encontrado el id buscado
    void buscar_alojamiento(unsigned id_alojamiento, const bblProg2::Alojamientos &alojas, unsigned &posicion, bool &encontrado)
    {
        posicion = 0;

        while (posicion < alojas.num_alojamientos && alojas.alojamientos[posicion].id_alojamiento < id_alojamiento)
        {
            posicion++;
        }
        encontrado = (posicion < alojas.num_alojamientos && alojas.alojamientos[posicion].id_alojamiento == id_alojamiento);
    }

    // Abre hueco en el array, desplazando "a la derecha" todos
    // los alojamientos a partir de la posición que se pasa
    // como parámetro (incluida esta).
    // PARÁMETROS:
    //  - posicion (E): posición a partir de cual se abre hueco
    //  - alojas (ES): lista de alojamientos
    // PRECONDICIÓN: posicion <= num_alojamientos
    void abrir_hueco(unsigned posicion, bblProg2::Alojamientos &alojas)
    {
        assert(posicion <= alojas.num_alojamientos);

        for (unsigned i = alojas.num_alojamientos; i > posicion; i--)
        {
            alojas.alojamientos[i] = alojas.alojamientos[i - 1];
        }
    }
} // namespace