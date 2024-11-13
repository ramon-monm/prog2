//--------------------------------------------------------------------------
// Programa principal de prueba de Directorio
//--------------------------------------------------------------------------
#include <iostream>
#include <cassert>
#include <fstream>

#include "directorio.hpp"

using namespace std;
using namespace bblProg2;


//--------------------------------------------------------------------------
void test_insertar()
{
	Directorio directorio;
	Telefonos telefonos1, telefonos2, telefonos3;
	bool ok;

	directorio.insertar("Pepe", 213, ok);
	assert(ok);
	telefonos1.insertarTelefono(213, ok);
	directorio.insertar("Pepe", 123, ok);
	assert(ok);
	telefonos1.insertarTelefono(123, ok);
	directorio.insertar("Pepe", 321, ok);
	assert(ok);
	telefonos1.insertarTelefono(321, ok);
	assert(directorio.numContactos() == 1);
	assert(directorio.getIdPos(0) == "Pepe");
	assert(directorio.getTelefonosPos(0) == telefonos1);

	directorio.insertar("Ana", 213, ok);
	assert(ok);
	telefonos2.insertarTelefono(213, ok);
	directorio.insertar("Ana", 123, ok);
	assert(ok);
	telefonos2.insertarTelefono(123, ok);
	directorio.insertar("Ana", 321, ok);
	assert(ok);
	telefonos2.insertarTelefono(321, ok);
	assert(directorio.numContactos() == 2);
	assert(directorio.getIdPos(0) == "Ana");
	assert(directorio.getTelefonosPos(0) == telefonos2);
	assert(directorio.getIdPos(1) == "Pepe");
	assert(directorio.getTelefonosPos(1) == telefonos1);


	directorio.insertar("Sandra", 213, ok);
	assert(ok);
	telefonos3.insertarTelefono(213, ok);
	directorio.insertar("Sandra", 123, ok);
	assert(ok);
	telefonos3.insertarTelefono(123, ok);
	directorio.insertar("Sandra", 321, ok);
	assert(ok);
	telefonos3.insertarTelefono(321, ok);
	assert(directorio.numContactos() == 3);
	assert(directorio.getIdPos(2) == "Sandra");
	assert(directorio.getTelefonosPos(2) == telefonos3);
	assert(directorio.getIdPos(0) == "Ana");
	assert(directorio.getTelefonosPos(0) == telefonos2);
	assert(directorio.getIdPos(1) == "Pepe");
	assert(directorio.getTelefonosPos(1) == telefonos1);

}
//-----------------------------------------------------------
void test_eliminar()
{
	Directorio directorio;
	Telefonos telefonos1, telefonos2, telefonos3;
	bool ok;

	// Primero insertamos varios contactos  con sus teléfonos
	directorio.insertar("Pepe", 213, ok);
	telefonos1.insertarTelefono(213, ok);
	directorio.insertar("Pepe", 123, ok);
	telefonos1.insertarTelefono(123, ok);
	directorio.insertar("Pepe", 321, ok);
	telefonos1.insertarTelefono(321, ok);

	directorio.insertar("Ana", 213, ok);
	telefonos2.insertarTelefono(213, ok);
	directorio.insertar("Ana", 123, ok);
	telefonos2.insertarTelefono(123, ok);
	directorio.insertar("Ana", 321, ok);
	telefonos2.insertarTelefono(321, ok);

	directorio.insertar("Sandra", 213, ok);
	telefonos3.insertarTelefono(213, ok);
	directorio.insertar("Sandra", 123, ok);
	telefonos3.insertarTelefono(123, ok);
	directorio.insertar("Sandra", 321, ok);
	telefonos3.insertarTelefono(321, ok);

	// Ahora eliminamos
	directorio.eliminar("Pepe", 123, ok);
	assert(ok);
	telefonos1.eliminarTelefono(123, ok);
	assert(directorio.getTelefonosPos(1) == telefonos1);
	directorio.eliminar("Pepe", 213, ok);
	assert(ok);
	telefonos1.eliminarTelefono(213, ok);
	assert(directorio.getTelefonosPos(1) == telefonos1);
	directorio.eliminar("Pepe", 321, ok);
	assert(ok);
	assert(directorio.getTelefonosPos(1) == telefonos3);
	assert(directorio.numContactos() == 2);

	directorio.eliminar("Ana", 123, ok);
	assert(ok);
	telefonos2.eliminarTelefono(123, ok);
	assert(directorio.getTelefonosPos(0) == telefonos2);
	directorio.eliminar("Ana", 213, ok);
	assert(ok);
	telefonos2.eliminarTelefono(213, ok);
	assert(directorio.getTelefonosPos(0) == telefonos2);
	directorio.eliminar("Ana", 321, ok);
	assert(ok);
	assert(directorio.getTelefonosPos(0) == telefonos3);
	assert(directorio.numContactos() == 1);

	directorio.eliminar("Sandra", 123, ok);
	assert(ok);
	telefonos3.eliminarTelefono(123, ok);
	assert(directorio.getTelefonosPos(0) == telefonos3);
	directorio.eliminar("Sandra", 213, ok);
	assert(ok);
	telefonos3.eliminarTelefono(213, ok);
	assert(directorio.getTelefonosPos(0) == telefonos3);
	directorio.eliminar("Sandra", 321, ok);
	assert(ok);
	assert(directorio.numContactos() == 0);

	assert(directorio == Directorio());
}
//--------------------------------------------------------------------------
void test_consultar()
{
	Directorio directorio;
	bool ok;
	string tlfns;

	directorio.consultar("Pepe", tlfns); assert(tlfns.empty());
	directorio.insertar("Pepe", 213, ok);
	directorio.consultar("Pepe", tlfns); assert(tlfns == "213 ");	
	directorio.insertar("Pepe", 123, ok);
	directorio.consultar("Pepe", tlfns); assert(tlfns == "123 213 ");		
	directorio.insertar("Pepe", 321, ok);
	directorio.consultar("Pepe", tlfns); assert(tlfns == "123 213 321 ");		

	directorio.consultar("Ana", tlfns); assert(tlfns.empty());	
	directorio.insertar("Ana", 213, ok);
	directorio.consultar("Ana", tlfns); assert(tlfns == "213 ");	
	directorio.insertar("Ana", 123, ok);
	directorio.consultar("Ana", tlfns); assert(tlfns == "123 213 ");		
	directorio.insertar("Ana", 321, ok);
	directorio.consultar("Ana", tlfns); assert(tlfns == "123 213 321 ");		

	directorio.consultar("Sandra", tlfns); assert(tlfns.empty());	
	directorio.insertar("Sandra", 213, ok);
	directorio.consultar("Sandra", tlfns); assert(tlfns == "213 ");	
	directorio.insertar("Sandra", 123, ok);
	directorio.consultar("Sandra", tlfns); assert(tlfns == "123 213 ");		
	directorio.insertar("Sandra", 321, ok);
	directorio.consultar("Sandra", tlfns); assert(tlfns == "123 213 321 ");		
}
//--------------------------------------------------------------------------
void test_num_contactos() {
	Directorio directorio;
	bool ok;

	assert(directorio.numContactos() == 0);
	directorio.insertar("Pepe", 213, ok);
	directorio.insertar("Pepe", 123, ok);
	directorio.insertar("Pepe", 321, ok);
	assert(directorio.numContactos() == 1);	

	directorio.insertar("Ana", 213, ok);
	directorio.insertar("Ana", 123, ok);
	directorio.insertar("Ana", 321, ok);
	assert(directorio.numContactos() == 2);

	directorio.insertar("Sandra", 213, ok);
	directorio.insertar("Sandra", 123, ok);
	directorio.insertar("Sandra", 321, ok);
	assert(directorio.numContactos() == 3);

	assert(Directorio().numContactos() == 0);
}
//--------------------------------------------------------------------------
void test_leer_de_fichero()
{
	Directorio directorio;
	bool ok;

	directorio.insertar("Pepe", 213, ok);
	directorio.insertar("Pepe", 123, ok);
	directorio.insertar("Pepe", 321, ok);
	directorio.insertar("Ana", 213, ok);
	directorio.insertar("Ana", 123, ok);
	directorio.insertar("Ana", 321, ok);
	directorio.insertar("Sandra", 213, ok);
	directorio.insertar("Sandra", 123, ok);
	directorio.insertar("Sandra", 321, ok);

	ofstream out;

	out.open("_fic_temp_.txt");
	out << "Ana" << endl
	    << "3"   << endl 
	    << "123" << endl
	    << "213" << endl
	    << "321" << endl;
	out << "Pepe" << endl
	    << "3"   << endl 
	    << "123" << endl
	    << "213" << endl
	    << "321" << endl;
	out << "Sandra" << endl
	    << "3"   << endl 
	    << "123" << endl
	    << "213" << endl
	    << "321" << endl;
	out.close();

	Directorio leido;

	leido.leer("_fic_temp_.txt", ok);
	assert(ok);
	assert(leido == directorio);
}
//--------------------------------------------------------------------------
void test_escribir_a_fichero()
{
	Directorio directorio, copia;
	bool ok;

	directorio.insertar("Pepe", 213, ok);
	directorio.insertar("Pepe", 123, ok);
	directorio.insertar("Pepe", 321, ok);
	directorio.insertar("Ana", 213, ok);
	directorio.insertar("Ana", 123, ok);
	directorio.insertar("Ana", 321, ok);
	directorio.insertar("Sandra", 213, ok);
	directorio.insertar("Sandra", 123, ok);
	directorio.insertar("Sandra", 321, ok);

	directorio.escribir("_fic_temp_.txt", ok);
	assert(ok);
	copia.leer("_fic_temp_.txt", ok);
	assert(directorio == copia);
}
//--------------------------------------------------------------------------
void test_copiar()
{
	Directorio directorio;
	bool ok;

	directorio.insertar("Pepe", 213, ok);
	directorio.insertar("Pepe", 123, ok);
	directorio.insertar("Pepe", 321, ok);
	directorio.insertar("Ana", 213, ok);
	directorio.insertar("Ana", 123, ok);
	directorio.insertar("Ana", 321, ok);
	directorio.insertar("Sandra", 213, ok);
	directorio.insertar("Sandra", 123, ok);
	directorio.insertar("Sandra", 321, ok);

	assert(directorio == Directorio(directorio));
}

//--------------------------------------------------------------------------
int main()
{
	cout << "Test insertar...";
	test_insertar();
	cout << "... OK" << endl;
	cout << "Test eliminar...";
	test_eliminar();
	cout << "... OK" << endl;
	cout << "Test consultar...";
	test_consultar();
	cout << "... OK" << endl;
	cout << "Test numContactos...";
	test_num_contactos();
	cout << "... OK" << endl;
	cout << "Test leer...";
	test_leer_de_fichero();
	cout << "... OK" << endl;
	cout << "Test escribir...";
	test_escribir_a_fichero();
	cout << "... OK" << endl;
	cout << "Test copiar...";
	test_copiar();
	cout << "... OK" << endl;

	cout << "--- OK." << endl;
}
//--------------------------------------------------------------------------
