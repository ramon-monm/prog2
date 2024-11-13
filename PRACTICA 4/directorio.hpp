/*-----------------------------------------------------------------------------
  directorio.hpp

  Fichero de definición de la clase Directorio, que permite la gestión de un
  directorio telefónico.

  Autor/a:

  ---------------------------------------------------------------------------*/

#ifndef __DIRECTORIO_HPP__
#define __DIRECTORIO_HPP__

#include "telefonos.hpp"

#include <string>
#include <cassert>

namespace bblProg2
{
	class Directorio
	{
	public:
		// Inicializa la lista a lista vacía.
		Directorio(); // Constructor por defecto
		// -------------------------------------
		// Destruye el objeto, liberando todos los recursos asociados al mismo.
		~Directorio(); // Destructor
		// -------------------------------------
		// Constructor de copia.
		Directorio(const Directorio &otro_directorio);
		// -------------------------------------
		// Inserta un nuevo telefono para un identificador concreto del directorio telefónico.
		// Si el identificador no existe, éste se inserta ORDENADO en la lista enlazada,
		// en orden creciente de identificador, junto con su telefono en su lista de telefonos.
		// Si el identificador ya existe, se añade el telefono a su lista de telefonos.
		// Si la inserción ha sido posible, insertado se pone a true.
		// Si no, insertado se pone a false.
		void insertar(const std::string &identificador, unsigned telefono, bool &insertado);
		// -------------------------------------
		// Se elimina un determinado telefono de la lista de telefonos correspondiente
		// a un determinado identificador. Si el identificador existe en el directorio telefónico y
		// el telefono existe en la lista de telefonos de ese identificador, el telefono se
		// elimina de su lista de telefonos. Si el telefono eliminado es el último de
		// la lista de telefonos para ese identificador, se elimina el nodo completamente de
		// la lista enlazada. Si se consigue elimimar el telefono, eliminado se pone a true.
		// Si no, se pone a false.
		void eliminar(const std::string &identificador, unsigned telefono, bool &eliminado);
		// -------------------------------------
		// Devuelve un string con la lista de telefonos (separados por espacios)
		// para el identificador que se pasa como parámetro.
		// Si el identificador no existe, el vector de telefonos devuelto estará vacío.
		void consultar(const std::string &identificador, std::string &telefonos) const;
		// -------------------------------------
		// Devuelve el número total de contactos (identificadores) que hay en la lista
		unsigned numContactos() const;
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
		void escribir() const;
		// -------------------------------------
		// Inicializa el directorio telefónico a partir de los datos leídos desde fichero.
		// La identificadors se insertan en orden creciente de identificador, es decir, a partir de llamadas
		// al método insertar(...) de la propia clase. El directorio telefónico actual debe
		// eliminarse antes de la lectura (es decir, debe borrarse completamente toda la lista
		// enlazada). El método recibe el nombre de fichero. Si el fichero puede abrirse
		// correctamente, leido se pone a true y se leen los datos desde fichero. Si no,
		// leido se pone a false y el directorio telefónico quedará vacío.
		// El formato de fichero coincide con el de salida por pantalla (véase más arriba).
		void leer(const std::string &nom_fic, bool &leido);
		// -------------------------------------
		// Escribe en fichero el directorio telefónico actual. El método recibe el identificador de fichero.
		// Si el fichero puede abrirse correctamente, escrito se pone a true y se escriben los datos a
		// fichero. Si no, escrito se pone a false. El formato de fichero coincide con el de salida
		// por pantalla (véase más arriba).
		void escribir(const std::string &nom_fic, bool &escrito) const;

		// -------------------------------------
		// Operadores sobrecargados (implementados por el profesor - no modificar!)
		bool operator==(const Directorio &otro_directorio) const
		{
			bool iguales = true;

			PtrNodo ptr1 = directorio, ptr2 = otro_directorio.directorio;

			while (iguales && ptr1 != nullptr && ptr2 != nullptr)
			{
				iguales = ptr1->id == ptr2->id &&
						  ptr1->telefonos == ptr2->telefonos;
				ptr1 = ptr1->sig;
				ptr2 = ptr2->sig;
			}

			return (iguales && ptr1 == nullptr && ptr2 == nullptr);
		}

		// -------------------------------------
		Directorio &operator=(const Directorio &otro_directorio)
		{
			if (this != &otro_directorio)
			{
				PtrNodo ptr1 = otro_directorio.directorio, ptr2;

				while (directorio != nullptr)
				{
					ptr2 = directorio;
					directorio = directorio->sig;
					delete ptr2;
				}

				while (ptr1 != nullptr)
				{
					if (directorio == nullptr)
					{
						directorio = new Nodo;
						ptr2 = directorio;
					}
					else
					{
						ptr2->sig = new Nodo;
						ptr2 = ptr2->sig;
					}
					ptr2->sig = nullptr;
					ptr2->id = ptr1->id;
					ptr2->telefonos = ptr1->telefonos;
					ptr1 = ptr1->sig;
				}
			}
			return *this;
		}

		// -------------------------------------
		// Métodos posicionales (implementados on-line por el profesor)
		std::string getIdPos(unsigned i) const
		{
			assert(i < numContactos());

			unsigned pos = 0;

			PtrNodo ptr = directorio;
			while (pos < i)
			{
				ptr = ptr->sig;
				++pos;
			}

			return ptr->id;
		}

		// -------------------------------------
		Telefonos getTelefonosPos(unsigned i) const
		{
			assert(i < numContactos());

			unsigned pos = 0;

			PtrNodo ptr = directorio;
			while (pos < i)
			{
				ptr = ptr->sig;
				++pos;
			}

			return ptr->telefonos;
		}
		// -------------------------------------
		// -------------------------------------
	private:
		// A COMPLETAR POR EL/LA ALUMNO/A

		struct Nodo {
			std::string id;
			Telefonos telefonos;
			Nodo *sig;
		};
		using PtrNodo=Nodo *;
		PtrNodo directorio;


		// Métodos privados

		// ---------------------------------------------------------------------------
		// Busca un identificador en el directorio telefónico actual.
		// Devuelve un puntero pos apuntando a un nodo con un identificador mayor o igual
		// que el que estamos buscando (o nullo, si todos son menores) y un puntero ant
		// apuntando al nodo anterior al que apunta pos (o a nulo, si pos apunta al
		// primer nodo de la lista). Si encuentra el identificador, esta se pone a true,
		// si no, esta se pone a false.
		void buscar(const std::string &identificador, PtrNodo &pos, PtrNodo &ant, bool &esta) const;
		// ---------------------------------------------------------------------------
		// Devuelve una copia de la lista que cuelga del puntero origen
		PtrNodo copiarLista(PtrNodo origen) const;
		// ---------------------------------------------------------------------------
		// Elimina todos los nodos de la lista que se pasa como parámetro, poniendo
		// lista finalmente a NULL (o nullptr).
		void borrarLista(PtrNodo &lista) const;
	};
} // namespace bblProgII

#endif