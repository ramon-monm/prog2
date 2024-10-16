/***********************************************************************************
 * Fichero alojamiento.cpp para la implementación de atributos y métodos de la clase
 * Alojamiento para la gestión de la información correspondiente con un alojamiento
 * turístico.
 *
 * Alumno/a:
 * Fecha:
 * *********************************************************************************/

#include "alojamiento.hpp"
#include <string>
#include <cassert>
#include <iostream>
#include <iomanip>

using namespace std;

namespace bblProg2
{
    // Operador de comparación de igualdad (IMPLEMENTADO POR EL PROFESORADO)
    bool Alojamiento::operator==(const Alojamiento &otro_alojamiento) const
    {
        bool iguales = false;
        if (id_alojamiento == otro_alojamiento.id_alojamiento &&
            nombre == otro_alojamiento.nombre &&
            id_anfitrion == otro_alojamiento.id_anfitrion &&
            nombre_anfitrion == otro_alojamiento.nombre_anfitrion &&
            barrio == otro_alojamiento.barrio &&
            latitud == otro_alojamiento.latitud &&
            longitud == otro_alojamiento.longitud &&
            tipo_alojamiento == otro_alojamiento.tipo_alojamiento &&
            precio == otro_alojamiento.precio &&
            minimo_noches == otro_alojamiento.minimo_noches &&
            disponibilidad_365 == otro_alojamiento.disponibilidad_365)
        {
            iguales = true;
        }

        return iguales;
    }

    // ---------------------------------------------------------------------

    // -------------- IMPLEMENTACIÓN DE LOS MÉTODOS PRIVADOS Y PÚBLICOS
    // Constructor por defecto
    Alojamiento::Alojamiento(): id_alojamiento{}, nombre{}, id_anfitrion{}, nombre_anfitrion{}, barrio{}, latitud{}, longitud{}, tipo_alojamiento{}, precio{}, minimo_noches{}, disponibilidad_365{} {}

    // Constructor de copia
    Alojamiento::Alojamiento(const Alojamiento &otro_alojamiento): id_alojamiento{otro_alojamiento.id_alojamiento}, nombre{otro_alojamiento.nombre}, id_anfitrion{otro_alojamiento.id_anfitrion}, nombre_anfitrion{otro_alojamiento.nombre_anfitrion}, barrio{otro_alojamiento.barrio}, latitud{otro_alojamiento.latitud}, longitud{otro_alojamiento.longitud}, tipo_alojamiento{otro_alojamiento.tipo_alojamiento}, precio{otro_alojamiento.precio}, minimo_noches{otro_alojamiento.minimo_noches}, disponibilidad_365{otro_alojamiento.disponibilidad_365} {}

    // Constructor específico
    Alojamiento::Alojamiento(unsigned id_alo,
                    const std::string &nom,
                    unsigned id_anf,
                    const std::string &nom_anf,
                    const std::string &barr,
                    double lat,
                    double lon,
                    const std::string &tipo_alo,
                    double prec,
                    unsigned min_noch,
                    unsigned dis_365): id_alojamiento{id_alo}, nombre{nom}, id_anfitrion{id_anf}, nombre_anfitrion{nom_anf}, barrio{barr}, latitud{lat}, longitud{lon}, tipo_alojamiento{tipo_alo}, precio{prec}, minimo_noches{min_noch}, disponibilidad_365{dis_365} {assert(prec>=0 && dis_365<=365 && !nom.empty() && !nom_anf.empty() && !barr.empty() && !tipo_alo.empty());}

    // Destructor
    Alojamiento::~Alojamiento() {}

    // Métodos de asignación
    
    // Asigna el identificador del alojamiento
    // Parámetros:
    //  - id_alo (E): identificador del alojamiento
    void Alojamiento::asignarIdAlojamiento(unsigned id_alo) {
        id_alojamiento=id_alo;
    }

    // Asigna el nombre del alojamiento
    // Parámetros:
    //  - nom (E): nombre del alojamiento
    // PRECONDICIÓN:
    //  - 'nom' no es cadena vacía
    void Alojamiento::asignarNombre(const std::string &nom) {
        assert(!nom.empty());
        nombre=nom;
    }

    // Asigna el identificador del anfitrion
    // Parámetros:
    //  - id_anf (E): identificador del anfitrión
    void Alojamiento::asignarIdAnfitrion(unsigned id_anf) {
        id_anfitrion=id_anf;
    }

    // Asigna el nombre del anfitrión
    // Parámetros:
    //  - nom_anf (E): nombre del anfitrión
    // PRECONDICIÓN:
    //  - 'nom_anf' no es cadena vacía
    void Alojamiento::asignarNombreAnfitrion(const std::string &nom_anf) {
        assert(!nom_anf.empty());
        nombre_anfitrion=nom_anf;
    }

    // Asigna el barrio (zona) donde se ubica el alojamiento
    // Parámetros:
    //  - barr (E): nombre del barrio
    // PRECONDICIÓN:
    //  - 'barr' no es cadena vacía
    void Alojamiento::asignarBarrio(const std::string &barr) {
        assert(!barr.empty());
        barrio=barr;
    }

    // Asigna la latitud de la ubicación del alojamiento
    // Parámetros:
    //  - lat (E): latitud de la ubicación
    void Alojamiento::asignarLatitud(double lat) {
        latitud=lat;
    }

    // Asigna la longitud de la ubicación del alojamiento
    // Parámetros:
    //  - lon (E): longitud de la ubicación
    void Alojamiento::asignarLongitud(double lon) {
        longitud=lon;
    }

    // Asigna el tipo de alojamiento
    // Parámetros:
    //  - tipo_alo (E): tipo de alojamiento
    // PRECONDICIÓN:
    //  - 'tipo_alo' no es cadena vacía
    void Alojamiento::asignarTipoAlojamiento(const std::string &tipo_alo) {
        assert(!tipo_alo.empty());
        tipo_alojamiento=tipo_alo;
    }

    // Asigna el precio del alojamiento
    // Parámetros:
    //  - prec (E): precio del alojamiento
    // PRECONDICIÓN: precio >= 0
    void Alojamiento::asignarPrecio(double prec) {
        assert(precio>=0);
        precio=prec;
    }

    // Asigna el mínimo número de noches que puede alquilarse el alojamiento
    // Parámetros:
    //  - min_noch (E): mínimo número de noches
    void Alojamiento::asignarMinimoNoches(unsigned min_noch) {
        minimo_noches=min_noch;
    }

    // Asignar el número de días al año de disponibilidad del alojamiento
    // Parámetros:
    //  - dis_365 (E): número de días al año disponible
    // PRECONDICIÓN: dis_365 <= 365
    void Alojamiento::asignarDisponibilidad365(unsigned dis_365) {
        assert(dis_365<=365);
        disponibilidad_365=dis_365;
    }

    // ----------------- MÉTODOS DE CONSULTA

    // Consulta el id del alojamiento
    unsigned Alojamiento::consultarIdAlojamiento() const {
        return id_alojamiento;
    }

    // Consulta el nombre del alojamiento
    std::string Alojamiento::consultarNombre() const {
        return nombre;
    }

    // Consulta el id del anfitrión del alojamiento
    unsigned Alojamiento::consultarIdAnfitrion() const {
        return id_anfitrion;
    }

    // Consulta el nombre del anfitrión del alojamiento
    std::string Alojamiento::consultarNombreAnfitrion() const {
        return nombre_anfitrion;
    }

    // Consulta el barrio (zona) donde se ubica el alojamiento
    std::string Alojamiento::consultar_barrio() const {
        return barrio;
    }

    // Consulta la latitud de la localización del alojamiento
    double Alojamiento::consultarLatitud() const {
        return latitud;
    }

    // Consulta la longitud de la localización del alojamiento
    double Alojamiento::consultarLongitud() const {
        return longitud;
    }

    // Consulta el tipo de alojamiento
    std::string Alojamiento::consultarTipoAlojamiento() const {
        return tipo_alojamiento;
    }

    // Consulta el precio del alojamiento
    double Alojamiento::consultarPrecio() const {
        return precio;
    }

    // Consulta el mínimo número de noches que puede alquilarse
    unsigned Alojamiento::consultarMinimoNoches() const {
        return minimo_noches;
    }

    // Consulta el número de días al año que está disponible
    unsigned Alojamiento::consultarDisponibilidad365() const {
        return disponibilidad_365;
    }

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
    void Alojamiento::escribir() const {
        cout<<"ID alojamiento"<<id_alojamiento<<endl;
        cout<<"Nombre alojamiento"<<nombre<<endl;
        cout<<"ID anfitrión"<<id_anfitrion<<endl;
        cout<<"Nombre anfitrión"<<nombre_anfitrion<<endl;
        cout<<"Barrio (área)"<<barrio<<endl;
        cout<<"Localización"<<latitud<<" "<<longitud<<endl;
        cout<<"Tipo de alojamiento"<<tipo_alojamiento<<endl;
        cout<<"Precio por noche"<<precio<<endl;
        cout<<"Mínimo de noches"<<minimo_noches<<endl;
        cout<<"Disponibilidad/año"<<disponibilidad_365<<endl;
    }

    // Lee de fichero los datos correspondientes a un alojamiento.
    // (VÉASE EL FORMATO DEL FICHERO EN escribir).
    // PARÁMETROS:
    //  - fic (ES): flujo de entrada desde fichero
    // PRECONDICIÓN: el fichero está correctamente abierto para lectura
    void Alojamiento::leer(std::ifstream &fic) {
        assert(fic.is_open());
        char ch_aux;
        string str_aux;
        fic >> id_alojamiento;
        fic.ignore(); //  Ignoramos la coma con entrada natural.
        fic >> ch_aux;
        if (ch_aux == '"')
        {
            getline(fic, nombre, '"');
            fic.ignore();
        }
        else
        {
            getline(fic, str_aux, ',');
            nombre = ch_aux + str_aux;
        } // Si el primer caracter es ", lo ignoramos. Luego se lee la cadena de texto hasta ". Se ignora la ,.
        fic >> id_anfitrion;
        fic.ignore();
        getline(fic, nombre_anfitrion, ',');
        getline(fic, barrio, ',');
        fic >> latitud;
        fic.ignore();
        fic >> longitud;
        fic.ignore();
        getline(fic, tipo_alojamiento, ',');
        fic >> precio;
        fic.ignore();
        fic >> minimo_noches;
        fic.ignore();
        fic >> disponibilidad_365;
        fic.ignore();
    }

    // Escribe en fichero los datos correspondientes a un alojamiento.
    // (Véase alojamientos.csv como ejemplo de formato de salida.)
    // FORMATO DEL FICHERO:
    //  - Los datos deben separarse con comas
    //  - Si el nombre del alojamiento incluye comas, debe guardarse en el fichero entre comillas dobles.
    //    Por ejemplo: "Design, style & vintage by Odenplan"
    // PARÁMETROS:
    //  - fic (ES): flujo de salida hacia fichero
    // PRECONDICIÓN: el fichero está correctamente abierto para escritura
    void Alojamiento::escribir(std::ofstream &fic) const {
        assert(fic.is_open());
        unsigned pos;
        fic << id_alojamiento << ",";
        pos = nombre.find(',');
        if (pos != string::npos)
        {
            fic << '"' << nombre << '"';
        }
        else
        {
            fic << nombre;
        }
        fic << ",";
        fic << id_anfitrion << ",";
        fic << nombre_anfitrion << ",";
        fic << barrio << ",";
        fic << setprecision(15) << latitud << ",";
        fic << setprecision(15) << longitud << ",";
        fic << tipo_alojamiento << ",";
        fic << precio << ",";
        fic << minimo_noches << ",";
        fic << disponibilidad_365 << endl;
    }
} // namespace bblProg2