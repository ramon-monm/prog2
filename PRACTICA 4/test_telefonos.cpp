//--------------------------------------------------------------------------
// Programa principal de prueba de Telefonos
//--------------------------------------------------------------------------
#include <iostream>
#include <string>
#include <cassert>

#include "telefonos.hpp"

using namespace std;
using namespace bblProg2;


//--------------------------------------------------------------------------
void test_insertar_telefono()
{
	Telefonos telefonos;
	bool insertado;

	telefonos.insertarTelefono(231, insertado);
	assert(insertado);
	assert(telefonos.estaEnLista(231));
	telefonos.insertarTelefono(123, insertado);
	assert(insertado);
	assert(telefonos.estaEnLista(123));	
	telefonos.insertarTelefono(321, insertado);
	assert(insertado);
	assert(telefonos.estaEnLista(321));	
	telefonos.insertarTelefono(231, insertado);
	assert(!insertado);

	assert(telefonos.numTelefonos() == 3);

	assert(telefonos[0] == 123 && telefonos[1] == 231 && telefonos[2] == 321 );
}
//-----------------------------------------------------------
void test_eliminar_telefono()
{
	Telefonos telefonos;
	bool insertado, eliminado;

	// Pimero insertamos
	telefonos.insertarTelefono(231, insertado);
	telefonos.insertarTelefono(123, insertado);
	telefonos.insertarTelefono(321, insertado);

	// Luego eliminamos
	telefonos.eliminarTelefono(231, eliminado);
	assert(eliminado);
	assert(!telefonos.estaEnLista(231));
	assert(telefonos[0] == 123 && telefonos[1] == 321 );
	telefonos.eliminarTelefono(123, eliminado);
	assert(eliminado);
	assert(!telefonos.estaEnLista(123));	
	assert(telefonos[0] == 321 );
	telefonos.eliminarTelefono(321, eliminado);
	assert(eliminado);
	assert(!telefonos.estaEnLista(321));	
	telefonos.eliminarTelefono(231, eliminado);
	assert(!eliminado);

	assert(telefonos.numTelefonos() == 0);

	assert(telefonos == Telefonos());
}
//--------------------------------------------------------------------------
void test_consultar_telefonos()
{
	Telefonos telefonos;
	bool insertado;
	string tlfns;

	telefonos.consultarTelefonos(tlfns);
	assert(tlfns == "");
	telefonos.insertarTelefono(231, insertado);
	telefonos.consultarTelefonos(tlfns);
	assert(tlfns == "231 ");
	telefonos.insertarTelefono(123, insertado);
	telefonos.consultarTelefonos(tlfns);
	assert(tlfns == "123 231 ");	
	telefonos.insertarTelefono(321, insertado);
	telefonos.consultarTelefonos(tlfns);
	assert(tlfns == "123 231 321 ");
}
//--------------------------------------------------------------------------
void test_esta_en_lista()
{
	Telefonos telefonos;
	bool insertado;
	string tlfns;

	telefonos.insertarTelefono(231, insertado);
	assert(telefonos.estaEnLista(231));
	telefonos.insertarTelefono(123, insertado);
	assert(telefonos.estaEnLista(123));	
	telefonos.insertarTelefono(321, insertado);
	assert(telefonos.estaEnLista(321));	
}
//--------------------------------------------------------------------------
void test_num_telefonos()
{
	Telefonos telefonos;
	bool insertado;
	string tlfns;

	assert(telefonos.numTelefonos() == 0);
	telefonos.insertarTelefono(231, insertado);
	assert(telefonos.numTelefonos() == 1);
	telefonos.insertarTelefono(123, insertado);
	assert(telefonos.numTelefonos() == 2);	
	telefonos.insertarTelefono(321, insertado);
	assert(telefonos.numTelefonos() == 3);	
	telefonos.eliminarTelefono(231, insertado);
	assert(telefonos.numTelefonos() == 2);	
}
//--------------------------------------------------------------------------
//--------------------------------------------------------------------------
void test_copiar()
{
	Telefonos telefonos;
	bool insertado;

	telefonos.insertarTelefono(231, insertado);
	telefonos.insertarTelefono(123, insertado);
	telefonos.insertarTelefono(321, insertado);

	assert(telefonos == Telefonos(telefonos));
}
//--------------------------------------------------------------------------
int main()
{

	cout <<"Test insertarTelefono...";
	test_insertar_telefono();
	cout << "... OK" << endl; 
	cout <<"Test elimnar_telefono...";	
	test_eliminar_telefono();
	cout << "... OK" << endl; 
	cout <<"Test consultar_telefono...";	
	test_consultar_telefonos();
	cout << "... OK" << endl; 
	cout <<"Test estaEnLista...";		
	test_esta_en_lista();
	cout << "... OK" << endl; 
	cout <<"Test numTelefonos...";			
	test_num_telefonos();
	cout << "... OK" << endl; 
	cout <<"Test copiar...";			
	test_copiar();
	cout << "... OK" << endl; 

	cout << "--- OK." << endl;

	return 0;
}
//--------------------------------------------------------------------------
