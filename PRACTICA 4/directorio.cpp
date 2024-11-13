#include "telefonos.hpp"
#include "directorio.hpp"

#include <array>
#include <string>
#include <iostream>
#include <fstream>

using namespace std;

namespace bblProg2 {
    
    Directorio::Directorio(): directorio{} {} // Constructor por defecto
    
    Directorio::~Directorio() {
        borrarLista(directorio);
    } 

    Directorio::Directorio(const Directorio &otro_directorio): directorio{copiarLista(otro_directorio.directorio)} {}

    // Métodos privados

    // Busca un identificador en el directorio telefónico actual.
    // Devuelve un puntero pos apuntando a un nodo con un identificador mayor o igual
    // que el que estamos buscando (o nulo, si todos son menores) y un puntero ant
    // apuntando al nodo anterior al que apunta pos (o a nulo, si pos apunta al
    // primer nodo de la lista). Si encuentra el identificador, esta se pone a true,
    // si no, esta se pone a false.
    void Directorio::buscar(const std::string &identificador, PtrNodo &pos, PtrNodo &ant, bool &esta) const {
        ant=nullptr; pos=directorio;
        while(pos!=nullptr && pos->id<identificador) {
            ant=pos;
            pos=pos->sig;
        }
        esta=pos!=nullptr && pos->id==identificador;
    }

    // Devuelve una copia de la lista que cuelga del puntero origen
    Directorio::PtrNodo Directorio::copiarLista(PtrNodo origen) const {
        PtrNodo rec=origen, copia=nullptr, ptri;
        while(rec!=nullptr) { // Mientras que rec apunte a un nodo no vacío de la lista original
            if(copia==nullptr) { // Si de copia no cuelga ninguna lista enlazada, debemos crear una y redirigir ptri a ella
                copia=new Nodo;
                ptri=copia;
            }
            else { // Si ya cuelga una lista enlazada de copia, creamos un nuevo nodo y redirigimos ptri a él
                ptri->sig=new Nodo;
                ptri=ptri->sig;
            }
            ptri->id=rec->id;
            ptri->telefonos=rec->telefonos;
            ptri->sig=nullptr;
            rec=rec->sig;
        }
        return copia;
    }

    // Elimina todos los nodos de la lista que se pasa como parámetro, poniendo
    // lista finalmente a NULL (o nullptr).
    void Directorio::borrarLista(PtrNodo &lista) const {
        while(lista!=nullptr) {
            PtrNodo ptr=lista;
            lista=lista->sig;
            delete[] ptr;
        }
    }

    // Métodos públicos

    // Inserta un nuevo telefono para un identificador concreto del directorio telefónico.
    // Si el identificador no existe, éste se inserta ORDENADO en la lista enlazada,
    // en orden creciente de identificador, junto con su telefono en su lista de telefonos.
    // Si el identificador ya existe, se añade el telefono a su lista de telefonos.
    // Si la inserción ha sido posible, insertado se pone a true.
    // Si no, insertado se pone a false.
    void Directorio::insertar(const std::string &identificador, unsigned telefono, bool &insertado) {
        PtrNodo pos, ant;
        bool encontrado;
        buscar(identificador, pos, ant, encontrado);
        if(encontrado) {
            pos->telefonos.insertarTelefono(telefono, insertado);
        }
        else {
            if(pos!=nullptr) { // Se inserta un nuevo nodo entre dos, o al prinipio de un directorio de un único nodo
                if(ant==nullptr) {
                    ant=new Nodo;
                }
                else {
                    ant->sig=new Nodo;
                    ant=ant->sig;
                }
                ant->id=identificador;
                ant->telefonos.insertarTelefono(telefono, insertado);
                ant->sig=pos;
                pos=ant;
            }
            else { // Se inserta un identificador al final de un directorio, o en un directorio vacío
                pos=new Nodo;
                pos->id=identificador;
                pos->telefonos.insertarTelefono(telefono, insertado);
                pos->sig=nullptr;
                if(ant!=nullptr) {
                    ant->sig=pos;
                }
            }
        }
    }
    // -------------------------------------
    // Se elimina un determinado telefono de la lista de telefonos correspondiente
    // a un determinado identificador. Si el identificador existe en el directorio telefónico y
    // el telefono existe en la lista de telefonos de ese identificador, el telefono se
    // elimina de su lista de telefonos. Si el telefono eliminado es el último de
    // la lista de telefonos para ese identificador, se elimina el nodo completamente de
    // la lista enlazada. Si se consigue elimimar el telefono, eliminado se pone a true.
    // Si no, se pone a false.
    void Directorio::eliminar(const std::string &identificador, unsigned telefono, bool &eliminado) {
        PtrNodo pos, ant;
        bool encontrado;
        buscar(identificador, pos, ant, encontrado);
        if(encontrado) {
            if(pos->telefonos.numTelefonos()>1) {
                pos->telefonos.eliminarTelefono(telefono, eliminado);
            }
            else {
                delete(pos);
                pos=ant->sig;
                eliminado=true;
            }
        }
        else {
            eliminado=false;
        }
    }
    // -------------------------------------
    // Devuelve un string con la lista de telefonos (separados por espacios)
    // para el identificador que se pasa como parámetro.
    // Si el identificador no existe, el vector de telefonos devuelto estará vacío.
    void Directorio::consultar(const std::string &identificador, std::string &telefonos) const {
        PtrNodo pos, ant;
        bool encontrado;
        buscar(identificador, pos, ant, encontrado);
        if(encontrado) {
            telefonos="";
            for(unsigned i=0; i<pos->telefonos.numTelefonos(); ++i) {
                telefonos+=pos->telefonos[i]+" ";
            }
        }
    }
    // -------------------------------------
    // Devuelve el número total de contactos (identificadores) que hay en la lista
    unsigned Directorio::numContactos() const {
        PtrNodo pos=directorio;
        unsigned num=0;
        if(pos!=nullptr) {
            while(pos!=nullptr) {
                ++num;
                pos=pos->sig;
            }
        }
        
        return num;
    }
    // -------------------------------------
    // Escribe por pantalla el directorio telefónico, sacando, para cada identificador almacenado
    // en la lista, el número de teléfonos en su lista de telefonos y, a continuación,
    // la lista de telefonos. Por ejemplo, la salida por pantalla podría ser:
    // Ana Gutierrez
    // 2
    // 670112233
    // 910000000
    // Monica Sanchez
    // 3
    // 610222222
    // 952010101
    // 952111111
    // Pepe Gomez
    // 4
    // 610001100
    // 610001111
    // 670555555
    // 958991100
    // ...
    void Directorio::escribir() const {
        PtrNodo pos=directorio;
        while(pos!=nullptr) {
            cout<<pos->id<<endl<<pos->telefonos.numTelefonos()<<endl;
            for(unsigned i=0; i<pos->telefonos.numTelefonos(); ++i) {
                cout<<pos->telefonos[i]<<endl;
            }
        }
    }
    // -------------------------------------
    // Inicializa el directorio telefónico a partir de los datos leídos desde fichero.
    // La identificadors se insertan en orden creciente de identificador, es decir, a partir de llamadas
    // al método insertar(...) de la propia clase. El directorio telefónico actual debe
    // eliminarse antes de la lectura (es decir, debe borrarse completamente toda la lista
    // enlazada). El método recibe el nombre de fichero. Si el fichero puede abrirse
    // correctamente, leido se pone a true y se leen los datos desde fichero. Si no,
    // leido se pone a false y el directorio telefónico quedará vacío.
    // El formato de fichero coincide con el de salida por pantalla (véase más arriba).
    void Directorio::leer(const std::string &nom_fic, bool &leido) {
        borrarLista(directorio);
        ifstream f;
        f.open(nom_fic);
        leido=false;
        if(!f.fail()) {
            unsigned n, tel;
            string identificador;
            bool insertado;
            directorio=new Nodo;
            while(!f.eof()) {
                f>>identificador;
                f>>n;
                for(unsigned i=0; i<n; ++i) {
                    f>>tel;
                    insertar(identificador, tel, insertado);
                }
            }
            leido=true;
            f.close();
        }
    }
    // -------------------------------------
    // Escribe en fichero el directorio telefónico actual. El método recibe el identificador de fichero.
    // Si el fichero puede abrirse correctamente, escrito se pone a true y se escriben los datos a
    // fichero. Si no, escrito se pone a false. El formato de fichero coincide con el de salida
    // por pantalla (véase más arriba).
    void Directorio::escribir(const std::string &nom_fic, bool &escrito) const {
        ofstream f;
        f.open(nom_fic);
        escrito=false;
        if(!f.fail()) {
            escrito=true;
            PtrNodo ptr=directorio;
            while(ptr!=nullptr) {
                f<<ptr->id<<endl;
                f<<ptr->telefonos.numTelefonos()<<endl;
                for(unsigned i=0; i<ptr->telefonos.numTelefonos(); ++i) {
                    f<<ptr->telefonos[i]<<endl;
                }
                ptr=ptr->sig;
            }
            f.close();
        }
    }
}