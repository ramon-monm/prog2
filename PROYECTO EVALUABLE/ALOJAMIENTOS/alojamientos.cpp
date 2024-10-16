/***********************************************************************************
 * Fichero alojamientos.cpp para la implementación de atributos y métodos de la clase
 * Alojamientos para la gestión de la información correspondiente a una lista de
 * alojamientos turísticos.
 *
 * Alumno/a:
 * Fecha:
 * *********************************************************************************/

#include "utilidades.hpp"
#include "alojamiento.hpp"
#include "alojamientos.hpp"
#include <cmath>
#include <array>
#include <string>
#include <fstream>
#include <cassert>
#include <iomanip>
#include <iostream>

using namespace std;

// ---------- Funciones auxiliares para la implementación de algunos métodos
// ---------- de la clase Alojamientos
// (IMPLEMENTADAS POR EL PROFESORADO)
namespace
{
    const double PI = 4.0 * atan(1.0);
    double gradosARadianes(double grados)
    {
        // return grados * M_PI / 180.0;
        return grados * PI / 180.0;
    }

    // Devuelve la distancia en kilómetros entre dos puntos
    // cuya latitud y longitud se indica.
    // PARÁMETROS:
    //  - latitud1 (E): latitud del punto uno
    //  - longitud1 (E): longitud del punto uno
    //  - latitud2 (E): latitud del punto dos
    //  - longitud2 (E): longitud del punto dos
    double distanciaHaversine(double latitud1, double longitud1, double latitud2, double longitud2)
    {
        const double RADIO_TERRESTRE = 6378.0; // Radio terrestre en el ecuador

        latitud1 = gradosARadianes(latitud1);
        longitud1 = gradosARadianes(longitud1);
        latitud2 = gradosARadianes(latitud2);
        longitud2 = gradosARadianes(longitud2);

        double dif_lat = latitud2 - latitud1;
        double dif_lon = longitud2 - longitud1;

        double a = pow(sin(dif_lat / 2.0), 2.0) + cos(latitud1) * cos(latitud2) * pow(sin(dif_lon / 2.0), 2.0);

        double c = 2.0 * atan2(sqrt(a), sqrt(1.0 - a));

        return RADIO_TERRESTRE * c;
    }
} // namespace

namespace bblProg2
{
    // ------------------------ OPERADORES SOBRECARGADOS (IMPLEMENTADOS POR EL PROFESORADO)

    // Operador de comparación de Alojamientos
    bool Alojamientos::operator==(const Alojamientos &otro_objeto) const
    {
        bool iguales = num_alojamientos == otro_objeto.num_alojamientos;

        unsigned i = 0;

        while (i < num_alojamientos && iguales)
        {
            iguales = alojamientos[i] == otro_objeto.alojamientos[i];
            i++;
        }

        return iguales;
    }

    // Operador [] de acceso mediante índice
    Alojamiento Alojamientos::operator[](unsigned indice) const
    {
        assert(indice < num_alojamientos);

        return alojamientos[indice];
    }

    // -----------------------------------------------------------------

    // -------------- IMPLEMENTACIÓN DE LOS MÉTODOS PRIVADOS Y PÚBLICOS

        // Constructor por defecto.
        // Inicializa la lista de alojamientos a una lista vacía
        Alojamientos::Alojamientos(): alojamientos{}, num_alojamientos{} {}

        // Constructor de copia
        Alojamientos::Alojamientos(const Alojamientos &otro_objeto): alojamientos{otro_objeto.alojamientos}, num_alojamientos{otro_objeto.num_alojamientos} {}

        // Destructor de la clase
        Alojamientos::~Alojamientos() {}

        // ------------------ MÉTODOS DE CONSULTA

        // Devuelve el alojamiento cuyo id se pasa como parámetro.
        // Si el alojamiento existe en la lista, se devuelve OK
        // a través del parámetro 'res'. Si no, se devuelve NO_EXISTE
        // PARÁMETROS:
        //  - id_alojamiento (E): id del alojamiento a consultar
        //  - alojamiento (S): el alojamiento consultado
        //  - res (S): resultado de la operación de consulta
        void Alojamientos::consultarAlojamiento(unsigned id_alojamiento, Alojamiento &alojamiento, Resultado &res) const {
            unsigned pos;
            bool encontrado;
            buscarAlojamiento(id_alojamiento, pos, encontrado);
            if(encontrado) {
                alojamiento=alojamientos[pos];
                res=OK;
            }
            else {
                res=NO_EXISTE;
            }
        }

        // Devuelve el número de alojamientos turísticos almacenados en la lista
        unsigned Alojamientos::numeroAlojamientos() const {
            return num_alojamientos;
        }

        // Devuelve los identificadores de todos los alojamientos
        // PARÁMETROS:
        //  - ids_alojamientos (S): lista de ids de todos los alojamientos
        void Alojamientos::listaAlojamientos(Ids &ids_alojamientos) const {
            for(unsigned i=0; i<num_alojamientos; ++i) {
                ids_alojamientos.ids[i]=alojamientos[i].consultarIdAlojamiento();
                ++ids_alojamientos.num_ids;
            }
        }

        // Devuelve la lista de los identificadores de alojamientos de un
        // determinado anfitrión cuyo identificador se pasa como parámetro.
        // Los identificadores deben devolverse en orden creciente.
        // PARÁMETROS:
        //  - id_anfitrion (E): identificador del anfitrión
        //  - ids_alojamientos (S): lista (array incompleto) con los identificadores
        //                          de los alojamientos pertenecientes a ese anfitrion
        //                          (en orden creciente).
        void Alojamientos::alojamientosAnfitrion(unsigned id_anfitrion, Ids &ids_alojamientos) const {
            for(unsigned i=0, j=0; i<num_alojamientos && alojamientos[i].consultarIdAnfitrion()==id_anfitrion; ++i) {
                ids_alojamientos.ids[j]=alojamientos[i].consultarIdAlojamiento();
                ++j;
                ++ids_alojamientos.num_ids;    
            }
            for(unsigned i=0; ids_alojamientos.num_ids>1 && i<ids_alojamientos.num_ids; ++i) {
                unsigned aux;
                for(unsigned j=i+1; i<ids_alojamientos.num_ids && ids_alojamientos.ids[j]<ids_alojamientos.ids[i]; ++j) {
                    aux=ids_alojamientos.ids[i];
                    ids_alojamientos.ids[i]=ids_alojamientos.ids[j];
                    ids_alojamientos.ids[j]=aux;
                }     
            }
        }
        
        // Dada la latitud y la longitud de un punto y una distancia en kilómetros,
        // devuelve la lista con los ids de los alojamientos que están, como máximo
        // a esa distancia del punto dado.
        // PARÁMETROS:
        //  - latitud (E): latitud de un punto dado en el plano
        //  - longitud (E): longitud de un punto dado en el plano
        //  - kms (E): distancia máxima en kilómetros
        //  - ids_alojamientos (S): identificadores de los alojamientos
        //                          que están, como mucho, a esa distancia
        //                          del punto dado.
        void Alojamientos::alojamientosAlrededor(double latitud, double longitud, double kms, Ids &ids_alojamientos) const {
            for(unsigned i=0, j=0; i<num_alojamientos && distanciaHaversine(latitud, longitud, alojamientos[i].consultarLatitud(), alojamientos[i].consultarLongitud()<=kms); ++i) {
                ids_alojamientos.ids[j]=alojamientos[i].consultarIdAlojamiento();
                ++j;
                ++ids_alojamientos.num_ids;
            }
        }

        // Devuelve la lista con los identificadores de alojamientos de un
        // determinado barrio.
        // PARÁMETROS:
        //   - barrio (E): un barrio de la ciudad
        //   - ids_alojamientos (S): lista de los alojamientos de ese barrio
        void Alojamientos::alojamientosBarrio(const std::string &barrio, Ids &ids_alojamientos) const {
            for(unsigned i=0, j=0; i<num_alojamientos && alojamientos[i].consultar_barrio()==barrio; ++i) {
                ids_alojamientos.ids[j]=alojamientos[i].consultarIdAlojamiento();
                ++j;
                ++ids_alojamientos.num_ids;
            }
        }

        // Devuelve la lista con los identificadores de todos los
        // alojamientos de un tipo concreto de alojamiento.
        // PARÁMETROS:
        //  - tipo_alojamiento (E): tipo de alojamiento
        //  - ids_alojamientos (S): lista de alojamientos de ese tipo
        void Alojamientos::alojamientosTipo(const std::string &tipo_alojamiento, Ids &ids_alojamientos) const {
            for(unsigned i=0, j=0; i<num_alojamientos && alojamientos[i].consultarTipoAlojamiento()==tipo_alojamiento; ++i) {
                ids_alojamientos.ids[j]=alojamientos[i].consultarIdAlojamiento();
                ++j;
                ++ids_alojamientos.num_ids;
            }
        }

        // Dado un precio en euros, devuelve la lista de alojamientos cuyo precio
        // por noche es inferior o igual a ese precio.
        // PARÁMETROS:
        //  - precio (E): máximo precio por noche
        //  - ids_alojamientos (S): lista de alojamientos con precio igual o inferior
        //                          al precio dado
        void Alojamientos::alojamientosPrecio(double precio, Ids &ids_alojamientos) const {
            for(unsigned i=0, j=0; i<num_alojamientos && alojamientos[i].consultarPrecio()<=precio; ++i) {
                ids_alojamientos.ids[j]=alojamientos[i].consultarIdAlojamiento();
                ++j;
                ++ids_alojamientos.num_ids;
            }
        }

        // Dado un número de noches, devuelve la lista con los identificadores
        // de los alojamientos cuyo mínimo número de noches de alquiler es menor
        // o igual que el número de noches dado.
        // PARÁMETROS:
        //  - num_noches (E): número de noches
        //  - ids_alojamientos (S): lista de alojamientos con mínimo número de noches
        //                          de alquiler menor o igual que el número de noches
        //                          dado.
        void Alojamientos::alojamientosNoches(unsigned num_noches, Ids &ids_alojamientos) const {
            for(unsigned i=0, j=0; i<num_alojamientos && alojamientos[i].consultarMinimoNoches()<=num_noches; ++i) {
                ids_alojamientos.ids[j]=alojamientos[i].consultarIdAlojamiento();
                ++j;
                ++ids_alojamientos.num_ids;
            }
        }

        // Devuelve la lista de ids de los alojamientos que cumplen con TODOS los
        // criterios de filtrado siguientes:
        //  - Si 'barrio' no es una cadena vacía, devuelve solo los alojamientos de ese barrio.
        //    Si es una cadena vacía, no tiene en cuenta el barrio como criterio de filtrado.
        //  - Y, además, si 'tipo_alojamiento' no es una cadena vacía, devuelve solo los alojamientos de ese
        //    tipo. Si es una cadena vacía, no tienen en cuenta el tipo de alojamiento como
        //    criterio de filtrado.
        //  - Y, además, si 'precio' > 0, devuelve solo los alojamientos de ese precio como máximo. Si
        //    'precio' es cero, no tiene en cuenta el precio como criterio de filtrado.
        //  - Y, además, si 'num_noches' > 0, devuelve solo los alojamientos cuyo mínimo número de noches
        //    de alquiler es menor o igual que 'num_noches'. Si 'num_noches' es cero, no se tiene
        //    en cuenta como criterio de filtrado.
        // PARÁMETROS:
        //  - barrio (E): barrio donde deben estar los alojamientos
        //  - tipo_alojamiento (E): tipo de alojamiento
        //  - precio (E): precio máximo por noche que se desea
        //  - num_noches (E): número mínimo de noches que exige el alojamiento
        //  - ids_alojamientos (S): lista de los ids de los alojamientos que
        //                          cumplen con todos los criterios.
        void Alojamientos::alojamientosFiltros(const std::string &barrio,
                                 const std::string &tipo_alojamiento,
                                 double precio,
                                 unsigned num_noches,
                                 Ids &ids_alojamientos) const {
                                    Ids aux_barrio={}, aux_tipo={}, aux_precio={}, aux_num_noches={};
                                    if(!barrio.empty()) {
                                        alojamientosBarrio(barrio, aux_barrio);
                                    }
                                    else {listaAlojamientos(aux_barrio);}
                                    if(!tipo_alojamiento.empty()) {
                                        alojamientosTipo(tipo_alojamiento, aux_tipo);
                                    }
                                    else {listaAlojamientos(aux_tipo);}
                                    if(precio>0) {
                                        alojamientosPrecio(precio, aux_precio);
                                    }
                                    else {listaAlojamientos(aux_precio);}
                                    if(num_noches>0) {
                                        alojamientosNoches(num_noches, aux_num_noches);
                                    }
                                    else {listaAlojamientos(aux_num_noches);}
                                    for(unsigned i=0, j=0; i<aux_barrio.num_ids; ++i) {
                                        for(unsigned k=0; k<aux_tipo.num_ids && aux_tipo.ids[k]==aux_barrio.ids[i]; ++k) {
                                            for(unsigned l=0; k<aux_precio.num_ids && aux_precio.ids[l]==aux_barrio.ids[i]; ++l) {
                                                for(unsigned m=0; k<aux_num_noches.num_ids && aux_num_noches.ids[m]==aux_barrio.ids[i]; ++m) {
                                                   ids_alojamientos.ids[j]=aux_barrio.ids[i];
                                                    ++j;
                                                    ++ids_alojamientos.num_ids; 
                                                }
                                            }
                                        }
                                    }
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
        // PARÁMETROS:
        //  - nombre_fichero (E): nombre del fichero de datos de alojamientos
        //  - res (S): resultado de la operación.
        void Alojamientos::escribirEnFichero(const std::string &nombre_fichero, Resultado &res) const {
            ofstream fic;
            fic.open(nombre_fichero);
            if (!fic.fail()){
                fic<<"id_alojamiento,nombre,id_anfitrion,nombre_anfitrion,barrio,latitud,longitud,tipo_alojamiento,precio,minimo_noches,disponibilidad_365" << endl;
                for(unsigned i=0; i<num_alojamientos; ++i) {
                    alojamientos[i].escribir(fic);
                }
                res = OK;
            }
            else
            {
                res = FIC_ERROR;
            }
        }

        // Escribe por pantalla los datos de todos los alojamientos,
        // en el siguiente formato para cada alojamiento (nótese que se
        // usan tabuladores para formatear la salida):
        //  --- ID alojamiento:  <id_alojamiento>
        //  Nombre alojamiento:  <nombre>
        //  ID anfitrión:        <id_anfitrion>
        //  Nombre anfitrión:    <nombre_anfitrion>
        //  Barrio (área):       <barrio>
        //  Localización:        <latitud>, <longitud>
        //  Tipo de alojamiento: <tipo_alojamiento>
        //  Precio por noche:    <precio>
        //  Mínimo de noches:    <minimo_noches>
        //  Disponibilidad/año:  <disponibilidad_365>
        void Alojamientos::escribir() const {
            for(unsigned i=0; i<num_alojamientos; ++i) {
                alojamientos[i].escribir();
                cout<<endl;
            }

        }

        // ----------------- MÉTODOS DE MODIFICACIÓN

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
        //  - res (S): resultado de la operación
        void Alojamientos::insertarAlojamiento(const Alojamiento &alojamiento, Resultado &res) {
            unsigned pos; bool encontrado;
            buscarAlojamiento(alojamiento.consultarIdAlojamiento(), pos, encontrado);
            if(encontrado) {
                res=YA_EXISTE;
            }
            else {
                if(num_alojamientos==MAX_ALOJAMIENTOS) {
                    res=LISTA_LLENA;
                }
                else {
                    if(num_alojamientos!=0) {
                        unsigned i=0;
                        while(i<num_alojamientos) {
                            if(alojamiento.consultarIdAlojamiento()<alojamientos[i].consultarIdAlojamiento()) {
                                break;
                            }
                            else {
                                ++i;
                            }
                        }
                        abrirHueco(i);
                        alojamientos[i]=alojamiento;
                    }
                    else {
                        alojamientos[0]=alojamiento;
                        ++num_alojamientos;
                    }
                    res=OK;
                }
            }
        }

        // Modifica los datos de un alojamiento de la lista de alojamientos
        // Si no existe un alojamiento con ese identificador,
        // se devuelve NO_EXISTE a través de 'res'. Si existe,
        // se modifican todos los datos del alojamiento y se devuelve OK
        // a través de 'res'.
        // PARÁMETROS:
        //  - alojamiento (E): alojamiento a modificar
        //  - res (S): resultado de la operación
        void Alojamientos::modificarAlojamiento(const Alojamiento &alojamiento, Resultado &res) {
            unsigned i;
            bool encontrado;
            buscarAlojamiento(alojamiento.consultarIdAlojamiento(), i, encontrado);
            if(encontrado) {
                alojamientos[i]=alojamiento;
                res=OK;
            }
            else {
                res=NO_EXISTE;
            }
        }

        // Elimina de la lista de alojamientos el alojamiento cuyo id
        // se pasa como parámetro. Si no existe un alojamiento con ese id,
        // se devuelve NO_EXISTE a través de 'res'. Si existe un alojamiento
        // con ese id, se elimina de la lista y se devuelve OK a través de
        // 'res'.
        // PARÁMETROS:
        //  - id_alojamiento (E): id del alojamiento a eliminar
        //  - res (S): resultado de la operación
        void Alojamientos::eliminarAlojamiento(unsigned id_alojamiento, Resultado &res) {
            unsigned i;
            bool encontrado;
            buscarAlojamiento(id_alojamiento, i, encontrado);
            if(encontrado) {
                cerrarHueco(i);
                --num_alojamientos;
                res=OK;
            }
            else {
                res=NO_EXISTE;
            }
        }

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
        //  - res (S): resultado de la operación.
        void Alojamientos::leerAlojamientos(const std::string &nombre_fichero, Resultado &res) {
            ifstream fic;
            fic.open(nombre_fichero);
            if(!fic.fail()) {
                Alojamiento aux;
                unsigned pos;
                bool encontrado;
                fic.ignore(300, '\n');
                for(unsigned i=num_alojamientos; !fic.eof(); ++i) {
                    aux.leer(fic);
                    buscarAlojamiento(aux.consultarIdAlojamiento(), pos, encontrado);
                    if(!encontrado) {
                        alojamientos[i]=aux;
                        ++num_alojamientos;
                    }
                    else {
                        --i;
                    }
                }
                res=OK;
            }
            else {
                res=FIC_ERROR;
            }
        }

        // -------------------------- MÉTODOS PRIVADOS

        // Busca un alojamiento por su identificador.
        // Devuelve la posición del array donde hay un alojamiento
        // cuyo identificador es mayor o igual que el que se está
        // buscando. Devuelve verdadero a través de 'encontrado' si
        // encuentra el alojamiento; devuelve falso en otro caso.
        // PARÁMETROS:
        //  - id_alojamiento (E): id del alojamiento a buscar
        //  - posicion (S): posición en el array donde hay un alojamiento
        //                  con identificador mayor o igual.
        //  - encontrado (S): indica si se ha encontrado el id buscado
        void Alojamientos::buscarAlojamiento(unsigned id_alojamiento, unsigned &posicion, bool &encontrado) const {
            encontrado=false;
            unsigned i=0;
            while(i<num_alojamientos) {
                if(alojamientos[i].consultarIdAlojamiento()>=id_alojamiento) {
                    encontrado=alojamientos[i].consultarIdAlojamiento()==id_alojamiento;
                    posicion=i;
                    break;
                }
                else {
                    ++i;
                }
            }
        }

        // Abre hueco en el array, desplazando "a la derecha" todos
        // los alojamientos a partir de la posición que se pasa
        // como parámetro (incluida esta).
        // PARÁMETROS:
        //  - posicion (E): posición a partir de cual se abre hueco
        // PRECONDICIÓN: posicion <= num_alojamientos
        void Alojamientos::abrirHueco(unsigned posicion) {
            for(unsigned i=num_alojamientos; i>posicion; --i) {
                alojamientos[i]=alojamientos[i-1];
            }
            alojamientos[posicion]={};
            ++num_alojamientos;
        }

        // Cierra hueco en el array, desplazando "a la izquierda" todos
        // los alojamientos a partir de la posición + 1 que se pasa
        // como parámetro, eliminando, por tanto, el alojamiento de la
        // posición dada.
        // PARÁMETROS:
        //  - posicion (E): posición a partir de cual se cierra hueco
        // PRECONDICIÓN: posicion < num_alojamientos
        void Alojamientos::cerrarHueco(unsigned posicion) {
            for(unsigned i=posicion; i<num_alojamientos; ++i) {
                alojamientos[i]=alojamientos[i+1];
            }
            alojamientos[num_alojamientos-1]={};
            --num_alojamientos;
        }
} // namespace bblProg2