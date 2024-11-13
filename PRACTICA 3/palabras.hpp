/***********************************************************************************
 * Fichero palabras.hpp para la definición de atributos y métodos de la clase
 * Palabras para la gestión de una lista de palabras (lista de string).
 *
 * Alumno/a:
 * Fecha:
 * *********************************************************************************/
//// ¡¡¡¡COMPLETAR TODO LO NECESARIO!!!!!

#ifndef __CLASE_PALABRAS__
#define __CLASE_PALABRAS__

#include <string>


// DEFINIR LA CLASE Palabras DENTRO DEL NAMESPACE bblProg2
namespace bblProg2 {
        class Palabras {

        public:
        // ------- MÉTODOS PÚBLICOS DE LA CLASE Palabras

        // Constructor por defecto.
        // Inicializa a una lista de palabras vacía.
        Palabras();

        // Constructor de copia
        // PARÁMETROS:
        //  - o (E): otro objeto de la misma clase
        Palabras(const Palabras &o);

        // Destructor
        ~Palabras();

        // Devuelve el número de palabras de la lista
        std::size_t numPalabras() const;

        // Añade una palabra al final de la lista.
        // Si la palabra no existe en la lista, la añade al
        // final de la misma y devuelve OK a través de 'res'.
        // Si la palabra ya existe, devuelve YA_EXISTE a
        // través de `res` (no se insertan palabras duplicadas).
        // PARÁMETROS:
        //  - pal (E): cadena de caracteres con la palabra a insertar
        //  - res (S): resultado de la operación de inserción
        void insertar(const std::string &pal, Resultado &res);

        // Indica si la palabra que se pasa como parámetro
        // está o no en la lista de palabras.
        // PARÁMETROS:
        //  - pal (E): cadena de caracteres con la palabra a buscar
        bool buscar(const std::string &pal) const;

        // Elimina una palabra de la lista de palabras.
        // Si la palabra está en la lista, se elimina
        // de la misma y se devuelve OK a través de 'res'.
        // Si no, se devuelve NO_EXISTE a través de 'res'.
        // PARÁMETROS:
        //  - pal (E): cadena de caracteres con la palabra a eliminar
        //  - res (S): resultado de la operación de eliminación
        void eliminar(const std::string &pal, Resultado &res);

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
        void leerPalabras(const std::string &nombre_fic, Resultado &res);

        // Escribe en un fichero la lista de palabras actual.
        // Si el fichero ha podido abrirse correctamente para escritura,
        // devuelve OK a través de 'res'. Si no, devuelve FIC_ERROR.
        // PARÁMETROS:
        //  - nombre_fic (E): nombre del fichero
        //  - res (S): resultado de la operación de escritura en fichero
        void escribirPalabras(const std::string &nombre_fic, Resultado &res) const;

        // Operadorores sobrecargados (IMPLEMENTADOS POR EL PROFESORADO, NO CAMBIAR NADA)
        std::string operator[](std::size_t i) const;

        Palabras &operator=(const Palabras &l);

        bool operator==(const Palabras &l) const;

        private:
        // -------- PARTE PRIVADA DE LA CLASE:    

        std::string *lista;
        std::size_t size, capacity;
        };
}
#endif