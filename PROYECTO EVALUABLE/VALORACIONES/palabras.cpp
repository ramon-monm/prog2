/***********************************************************************************
 * Fichero palabras.cpp para la implementación de los métodos de la clase
 * Palabras para la gestión de una lista de palabras (lista de string).
 *
 * Alumno/a:
 * Fecha:
 * *********************************************************************************/

#include "utilidades.hpp"
#include "palabras.hpp"
#include <string>
#include <fstream>
#include <cassert>

using namespace std;

namespace bblProg2
{
    // Operadorores sobrecargados IMPLEMENTADOS POR EL PROFESORADO (NO CAMBIAR)
    string Palabras::operator[](size_t i) const
    {
        assert(i < size);

        return lista[i];
    }

    Palabras &Palabras::operator=(const Palabras &l)
    {
        if (this != &l)
        {
            delete[] lista;
            lista = new string[l.capacity];
            size = l.size;
            capacity = l.capacity;

            for (size_t i = 0; i < l.size; ++i)
            {
                lista[i] = l.lista[i];
            }
        }

        return *this;
    }

    bool Palabras::operator==(const Palabras &l) const
    {
        bool equal = numPalabras() == l.numPalabras();

        size_t i = 0;
        while (equal && i < size)
        {
            equal = buscar(l.lista[i]);
            ++i;
        }

        return equal;
    }

    // -------------------------------------------------------------------

    // IMPLEMENTACIÓN DE LOS MÉTODOS PÚBLICOS DE LA CLASE Palabras (completar):
    
    // Constructor por defecto.
    // Inicializa a una lista de palabras vacía.
    Palabras::Palabras(): lista{}, size{}, capacity{} {}

    // Constructor de copia
    // PARÁMETROS:
    //  - o (E): otro objeto de la misma clase
    Palabras::Palabras(const Palabras &o): lista{o.lista}, size{o.size}, capacity{o.capacity} {}

    // Destructor
    Palabras::~Palabras() {}

    // Devuelve el número de palabras de la lista
    std::size_t Palabras::numPalabras() const {
        return size;
    }

    // Añade una palabra al final de la lista.
    // Si la palabra no existe en la lista, la añade al
    // final de la misma y devuelve OK a través de 'res'.
    // Si la palabra ya existe, devuelve YA_EXISTE a
    // través de `res` (no se insertan palabras duplicadas).
    // PARÁMETROS:
    //  - pal (E): cadena de caracteres con la palabra a insertar
    //  - res (S): resultado de la operación de inserción
    void Palabras::insertar(const std::string &pal, Resultado &res) {
        if(buscar(pal)) {
            res=YA_EXISTE;
        }
        else{
            bool copy=false;
            if(capacity==0) {
            ++capacity; // Si se hace la inserción en una lista vacía, se debe incrementar la capacidad a 1.
            copy=true;
            }
            if(size==capacity) {
                capacity*=2; // Si no caben más elementos en la lista (hay tantos elementos como capacidad), duplicamos la capacidad de la lista.
                copy=true;
            }
            if(copy) { // Deberemos copiar el array al que apunta lista solo si modificamos su capacidad para trabajar sobre él globalmente
                string *aux=new string[capacity];
                for(unsigned i=0; i<size; ++i) {
                    aux[i]=lista[i];
                }
                delete[] lista;
                lista=aux;
            }
            lista[size]=pal;
            ++size;
            res=OK;
        }
    }

    // Indica si la palabra que se pasa como parámetro
    // está o no en la lista de palabras.
    // PARÁMETROS:
    //  - pal (E): cadena de caracteres con la palabra a buscar
    bool Palabras::buscar(const std::string &pal) const {
        bool encontrada=false;
        for(unsigned i=0; !encontrada && i<size; ++i) {
            encontrada=lista[i]==pal;
        }
        return encontrada;
    }

    // Elimina una palabra de la lista de palabras.
    // Si la palabra está en la lista, se elimina
    // de la misma y se devuelve OK a través de 'res'.
    // Si no, se devuelve NO_EXISTE a través de 'res'.
    // PARÁMETROS:
    //  - pal (E): cadena de caracteres con la palabra a eliminar
    //  - res (S): resultado de la operación de eliminación
    void Palabras::eliminar(const std::string &pal, Resultado &res) {
        if(!buscar(pal)) {
            res=NO_EXISTE;
        }
        else {
            bool encontrada=false;
            string *aux=new string[capacity];
            for(unsigned i=0; i+1<size; ++i) {
                if(!encontrada) {
                    encontrada=lista[i]==pal;
                    if(!encontrada) {
                        aux[i]=lista[i];
                    }
                }
                if(encontrada) {
                    aux[i]=lista[i+1];
                }
            }
            delete[] lista;
            lista=aux;
            --size;
            res=OK;
        }
    }

    // Lee desde fichero una lista de palabras
    // y la almacena en el objeto. Si el fichero ha podido abrirse
    // correctamente para lectura, devuelve OK a través de 'res'. Si no,
    // devuelve FIC_ERROR.
    // NOT: El fichero puede empezar por un número variables de líneas que comienzan
    // por punto y coma (";") y que deben ignorarse, dado que se trata
    // de comentarios previos (cabecera). (Véase, por ejemplo,
    // el fichero "positive-words.txt".)
    // PARÁMETROS:
    //  - nombre_fic (E): nombre del fichero
    //  - res (S): resultado de la operación de lectura de fichero
    void Palabras::leerPalabras(const std::string &nombre_fic, Resultado &res) {
        ifstream f;
        f.open(nombre_fic);
        if(f.fail()) {
            res=FIC_ERROR;
        }
        else {
            string aux;
            getline(f, aux);
            while(!f.eof() && aux[0]==';') {
                getline(f, aux);
            }
            unsigned i;
            for(i=0; i<size && !f.eof(); ++i) {
                lista[i]=aux;
                f>>aux;
            }
            lista[i]=aux;
            f.close();
            res=OK;
        }
    }

    // Escribe en un fichero la lista de palabras actual.
    // Si el fichero ha podido abrirse correctamente para escritura,
    // devuelve OK a través de 'res'. Si no, devuelve FIC_ERROR.
    // PARÁMETROS:
    //  - nombre_fic (E): nombre del fichero
    //  - res (S): resultado de la operación de escritura en fichero
    void Palabras::escribirPalabras(const std::string &nombre_fic, Resultado &res) const {
        ofstream f;
        f.open(nombre_fic);
        if(f.fail()) {
            res=FIC_ERROR;
        }
        else {
            for(unsigned i=0; i<size; ++i) {
                f<<lista[i]<<endl;
            }
            f.close();
            res=OK;
        }
    }

}
