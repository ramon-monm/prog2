/***********************************************************************************
 * Fichero alojamiento.hpp para la definición de atributos y métodos de la clase
 * Alojamiento para la gestión de la información correspondiente con un alojamiento
 * turístico.
 *
 * Alumno/a:
 * Fecha: 
 * *********************************************************************************/

/// ¡¡¡COMPLETAR TODO LO QUE FALTA!!!

#ifndef __CLASE_ALOJAMIENTO__
#define __CLASE_ALOJAMIENTO__

// Incluir todas las bibliotecas necesarias
#include <string>
#include <fstream>

/// Definir la clase Alojamiento dentro del namespace bblProg2

namespace bblProg2 {

    class Alojamiento {
// ----- MÉTODOS PÚBLICOS DE LA CLASE Alojamiento
        public:
        // Constructor por defecto.
        // Inicializa todos los atributos que son cadenas de caracteres con
        // la cadena vacía y los atributos que son números con cero
        Alojamiento();

        // Constructor de copia
        Alojamiento(const Alojamiento &otro_alojamiento);

        // Constructor específico.
        // Inicializa los atributos según los parámetros correspondientes.
        // Parámetros:
        //  - id_alo (E): identificador del alojamiento
        //  - nom (E): nombre del alojamiento
        //  - id_anf (E): identificador del anfitrión
        //  - nom_anf (E): nombre del anfitrión
        //  - barr (E): barrio del alojamiento
        //  - lat (E): latitud de la ubicación del alojamiento
        //  - lon (E): longitud de la ubicación del alojamiento
        //  - tipo_alo (E): tipo del alojamiento
        //  - prec (E): precio del alojamiento
        //  - min_noch (E): mínimo de noches
        //  - dis_365 (E): número de días al año disponible
        // PRECONDICIÓN:
        //  - prec >= 0
        //  - dis_365 <= 365
        //  - las cadenas de caracteres no son vacías
        Alojamiento(unsigned id_alo,
                    const std::string &nom,
                    unsigned id_anf,
                    const std::string &nom_anf,
                    const std::string &barr,
                    double lat,
                    double lon,
                    const std::string &tipo_alo,
                    double prec,
                    unsigned min_noch,
                    unsigned dis_365);

        // Destructor
        ~Alojamiento();

        // ----------------- MÉTODOS DE ASIGNACIÓN

        // Asigna el identificador del alojamiento
        // Parámetros:
        //  - id_alo (E): identificador del alojamiento
        void asignarIdAlojamiento(unsigned id_alo);

        // Asigna el nombre del alojamiento
        // Parámetros:
        //  - nom (E): nombre del alojamiento
        // PRECONDICIÓN:
        //  - 'nom' no es cadena vacía
        void asignarNombre(const std::string &nom);

        // Asigna el identificador del anfitrion
        // Parámetros:
        //  - id_anf (E): identificador del anfitrión
        void asignarIdAnfitrion(unsigned id_anf);

        // Asigna el nombre del anfitrión
        // Parámetros:
        //  - nom_anf (E): nombre del anfitrión
        // PRECONDICIÓN:
        //  - 'nom_anf' no es cadena vacía
        void asignarNombreAnfitrion(const std::string &nom_anf);

        // Asigna el barrio (zona) donde se ubica el alojamiento
        // Parámetros:
        //  - barr (E): nombre del barrio
        // PRECONDICIÓN:
        //  - 'barr' no es cadena vacía
        void asignarBarrio(const std::string &barr);

        // Asigna la latitud de la ubicación del alojamiento
        // Parámetros:
        //  - lat (E): latitud de la ubicación
        void asignarLatitud(double lat);

        // Asigna la longitud de la ubicación del alojamiento
        // Parámetros:
        //  - lon (E): longitud de la ubicación
        void asignarLongitud(double lon);

        // Asigna el tipo de alojamiento
        // Parámetros:
        //  - tipo_alo (E): tipo de alojamiento
        // PRECONDICIÓN:
        //  - 'tipo_alo' no es cadena vacía
        void asignarTipoAlojamiento(const std::string &tipo_alo);

        // Asigna el precio del alojamiento
        // Parámetros:
        //  - prec (E): precio del alojamiento
        // PRECONDICIÓN: precio >= 0
        void asignarPrecio(double prec);

        // Asigna el mínimo número de noches que puede alquilarse el alojamiento
        // Parámetros:
        //  - min_noch (E): mínimo número de noches
        void asignarMinimoNoches(unsigned min_noch);

        // Asignar el número de días al año de disponibilidad del alojamiento
        // Parámetros:
        //  - dis_365 (E): número de días al año disponible
        // PRECONDICIÓN: dis_365 <= 365
        void asignarDisponibilidad365(unsigned dis_365);

        // ----------------- MÉTODOS DE CONSULTA

        // Consulta el id del alojamiento
        unsigned consultarIdAlojamiento() const;

        // Consulta el nombre del alojamiento
        std::string consultarNombre() const;

        // Consulta el id del anfitrión del alojamiento
        unsigned consultarIdAnfitrion() const;

        // Consulta el nombre del anfitrión del alojamiento
        std::string consultarNombreAnfitrion() const;

        // Consulta el barrio (zona) donde se ubica el alojamiento
        std::string consultar_barrio() const;

        // Consulta la latitud de la localización del alojamiento
        double consultarLatitud() const;

        // Consulta la longitud de la localización del alojamiento
        double consultarLongitud() const;

        // Consulta el tipo de alojamiento
        std::string consultarTipoAlojamiento() const;

        // Consulta el precio del alojamiento
        double consultarPrecio() const;

        // Consulta el mínimo número de noches que puede alquilarse
        unsigned consultarMinimoNoches() const;

        // Consulta el número de días al año que está disponible
        unsigned consultarDisponibilidad365() const;

        // ----------------- MÉTODOS DE ENTRADA/SALIDA

        // Escribe por pantalla los datos del alojamiento,
        // en el siguiente formato (nótese que se
        // usan tabuladores para formatear la salida):
        //  ID alojamiento:      <id_alojamiento>
        //  Nombre alojamiento:  <nombre>
        //  ID anfitrión:        <id_anfitrion>
        //  Nombre anfitrión:    <nombre_anfitrion>
        //  Barrio (área):       <barrio>
        //  Localización:        <latitud>, <longitud>
        //  Tipo de alojamiento: <tipo_alojamiento>
        //  Precio por noche:    <precio>
        //  Mínimo de noches:    <minimo_noches>
        //  Disponibilidad/año:  <disponibilidad_365>
        void escribir() const;

        // Lee de fichero los datos correspondientes a un alojamiento.
        // (VÉASE EL FORMATO DEL FICHERO EN escribir).
        // PARÁMETROS:
        //  - fic (ES): flujo de entrada desde fichero
        // PRECONDICIÓN: el fichero está correctamente abierto para lectura
        void leer(std::ifstream &fic);

        // Escribe en fichero los datos correspondientes a un alojamiento.
        // (Véase alojamientos.csv como ejemplo de formato de salida.)
        // FORMATO DEL FICHERO:
        //  - Los datos deben separarse con comas
        //  - Si el nombre del alojamiento incluye comas, debe guardarse en el fichero entre comillas dobles.
        //    Por ejemplo: "Design, style & vintage by Odenplan"
        // PARÁMETROS:
        //  - fic (ES): flujo de salida hacia fichero
        // PRECONDICIÓN: el fichero está correctamente abierto para escritura
        void escribir(std::ofstream &fic) const;

        // --------- OPERADORES SOBRECARGADOS (IMPLEMENTADOS POR EL PROFESORADO)

        // Operador de asignación de Alojamiento
        // (IMPLEMENTADO POR EL PROFESORADO)
        Alojamiento &operator=(const Alojamiento &otro_alojamiento) = default;

        // Operador de comparación de igualdad
        // (NECESARIO PARA LAS PRUEBAS UNITARIAS)
        // (IMPLEMENTADO POR EL PROFESORADO)
        bool operator==(const Alojamiento &otro_alojamiento) const;

    // ----- PARTE PRIVADA DE LA CLASE Alojamiento
        private:
        unsigned id_alojamiento;
        std::string nombre;
        unsigned id_anfitrion;
        std::string nombre_anfitrion;
        std::string barrio;
        double latitud, longitud;
        std::string tipo_alojamiento;
        double precio;
        unsigned minimo_noches;
        unsigned disponibilidad_365;

        // ATRIBUTOS
        // ... id_alojamiento;      // Identificador (único) del alojamiento
        // ... nombre;              // Nombre del alojamiento
        // ... id_anfitrion;        // Identificador (único) del anfitrión/a
        // ... nombre_anfitrion;    // Nombre del anfitrión/a
        // ... barrio;              // Barrio (zona) donde se ubica el apartamento
        // ... latitud, longitud;   // Latitud y longitud de la ubicación del apartamento
        // ... tipo_alojamiento;    // Tipo de alojamiento
        // ... precio;              // Precio del alojamiento por cada día de estancia
        // ... minimo_noches;       // Mínimo número de noches que se puede alquilar
        // ... disponibilidad_365;  // Número de días al año que está disponible
    };
}

#endif