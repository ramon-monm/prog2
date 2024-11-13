/*-----------------------------------------------------------------------------
  telefonos.cpp

  Fichero de implementación de la clase Telefonos, que permite la gestión de una
  lista de teléfonos (números de tipo unsigned).

  Autor/a:
  ---------------------------------------------------------------------------*/

#include "telefonos.hpp"

#include <array>
#include <iostream>
#include <string>

using namespace std;

namespace bblProg2
{
	Telefonos::Telefonos() : telefonos{}, n_telefonos{} {} // Constructor por defecto
	//-------------------------------------
	Telefonos::~Telefonos() {} // Destructor
	//-------------------------------------
	void Telefonos::insertarTelefono(unsigned telefono, bool &insertado)
	{
		unsigned pos;
		bool encontrado;
		buscarTelefono(telefono, pos, encontrado);

		if (encontrado)
		{
			insertado = false;
		}
		else if (n_telefonos < telefonos.size())
		{ // Lista no llena
			insertado = true;
			// Abrir hueco
			for (unsigned i = n_telefonos; i > pos; --i)
			{
				telefonos[i] = telefonos[i - 1];
			}
			telefonos[pos] = telefono;
			++n_telefonos;
		}
	}
	//-------------------------------------
	void Telefonos::eliminarTelefono(unsigned telefono, bool &eliminado)
	{
		unsigned pos;
		buscarTelefono(telefono, pos, eliminado);

		if (eliminado)
		{
			// Cerrar hueco
			for (unsigned i = pos; i < n_telefonos - 1; ++i)
			{
				telefonos[i] = telefonos[i + 1];
			}
			--n_telefonos;
		}
		else
		{
			eliminado = false;
		}
	}
	//-------------------------------------
	void Telefonos::consultarTelefonos(string &tlfns) const
	{
		tlfns.clear();

		for (unsigned i = 0; i < n_telefonos; ++i)
		{
			tlfns += to_string(telefonos[i]) + ' ';
		}
	}
	//-------------------------------------
	bool Telefonos::estaEnLista(unsigned telefono) const
	{
		unsigned pos;
		bool encontrado;
		buscarTelefono(telefono, pos, encontrado);

		return encontrado;
	}
	//-------------------------------------
	unsigned Telefonos::numTelefonos() const
	{
		return n_telefonos;
	}
	// Devuelve el número de teléfonos de la lista.

	// Métodos privados
	void Telefonos::buscarTelefono(unsigned telefono, unsigned &pos, bool &encontrado) const
	{
		pos = 0;

		while (pos < n_telefonos && telefono > telefonos[pos])
		{
			++pos;
		}

		encontrado = (pos < n_telefonos && telefono == telefonos[pos]);
	}

	// Operdores sobrecargados (implementados on-line por el profesor)
	bool Telefonos::operator==(const Telefonos &otra_lista) const
	{
		bool iguales = true;
		iguales = n_telefonos == otra_lista.n_telefonos;

		unsigned i = 0;
		while (iguales && i < n_telefonos)
		{
			iguales = telefonos[i] == otra_lista.telefonos[i];
			++i;
		}
		return iguales;
	}
	//-------------------------------------
	unsigned Telefonos::operator[](unsigned i) const
	{
		assert(i < n_telefonos);

		return telefonos[i];
	}
} // namespace bblProg2
