/*-----------------------------------------------------------------------------
  telefonos.hpp

  Fichero de definición de la clase Telefonos, que permite la gestión de una
  lista de teléfonos (números de tipo unsigned).

  Autor/a:
  ---------------------------------------------------------------------------*/

#ifndef __TELEFONOS_HPP__
#define __TELEFONOS_HPP__

#include <array>
#include <string>
#include <cassert>

namespace bblProg2
{
	class Telefonos
	{
	public:
		// Inicializa la lista de teléfonos a lista vacía.
		Telefonos(); // Constructor por defecto
		//-------------------------------------
		// Destruye el objeto, liberando todos los recursos asociados al mismo.
		~Telefonos(); // Destructor
		//-------------------------------------
		// Constructor de copia.
		Telefonos(const Telefonos &otra_lista) = default;
		//-------------------------------------
		// Inserta un telefono en la lista de teléfonos, en orden creciente
		// de su valor numérico. Si la lista de teléfonos no está llena y
		// telefono no existe en la lista, el teléfono se inserta de manera
		// ORDENADA en la lista e insertado se pone a true. Si no, insertado
		// se pone a false. Nota importante: NO puede haber teléfonos repetidos.
		void insertarTelefono(unsigned telefono, bool &insertado);
		//-------------------------------------
		// Elimina un teléfono de la lista de teléfonos. Si el telefono existe
		//  en la lista de teléfonos, se elimina de la lista y eliminado se pone
		// a true. Si no, eliminado se pone a false.
		void eliminarTelefono(unsigned telefono, bool &eliminado);
		//-------------------------------------
		// Devuelve un string con la lista de todos los teléfonos separados por
		// un carácter espacio. Por ej.: "952555555 670330033 910550055"
		void consultarTelefonos(std::string &tlfns) const;
		//-------------------------------------
		// Indica si el telefono está en la lista de teléfonos.
		bool estaEnLista(unsigned telefono) const;
		//-------------------------------------
		// Devuelve el número de teléfonos de la lista.
		unsigned numTelefonos() const;
		//-------------------------------------
		// Devuelve el número de máximo teléfonos de la lista.
		unsigned maxTelefonos() const;
		//-------------------------------------
		
		// Operdores sobrecargados (implementados por el profesor)
		bool operator==(const Telefonos &otra_lista) const;
		//-------------------------------------
		unsigned operator[](unsigned i) const;
		//-------------------------------------
		Telefonos &operator=(const Telefonos &otra_lista) = default;

	private:
		std::array<unsigned, 10> telefonos;
		unsigned n_telefonos;

		// Métodos privados
		// Busca un teléfono en la lista de teléfonos. Si lo encuentra,
		// devuelve su posición en la lista. Si no lo encuentra, devuelve
		// la posición en la que debería estar en la lista, teniendo en cuenta
		// que ésta está ordenada en orden creciente. (Por ejemplo, si la
		// lista contiene los elementos {2, 4, 6, 8} y buscamos el teléfono 5,
		// debería devolver la posición 3, que es la posición en la que le
		// correspondería estar al 5 si estuviera en la lista.)
		void buscarTelefono(unsigned telefono, unsigned &pos, bool &encontrado) const;
	};
} // namespace bblProg2

#endif