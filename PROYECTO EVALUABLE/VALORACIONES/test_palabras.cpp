/******************************************************************************
 * test_palabras.cpp
 *
 * Programa principal de prueba del TAD Palabras.
 *
 * Alumno/a:
 * Fecha:
 *****************************************************************************/

#include "utilidades.hpp"
#include "palabras.hpp"

#include <iostream>
#include <string>
#include <cassert>
#include <vector>

using namespace std;
using namespace bblProg2;

const string FIC_PALABRAS_POSITIVAS = "positive-words.txt";
const string FIC_PALABRAS_NEGATIVAS = "negative-words.txt";

// Prueba del constructor por defecto
void test_constructor()
{
    Palabras palabras;

    assert(palabras.numPalabras() == 0);
}

// Prueba del constructor de copia
void test_constructor_copia()
{
    Palabras palabras;
    for (size_t i = 1; i <= 100; ++i)
    {
        Resultado res;
        palabras.insertar(string("palabra_") + to_string(i), res);
    }

    Palabras palabras_copia{palabras};

    assert(palabras_copia.numPalabras() == palabras.numPalabras());

    for (size_t i = 0; i < palabras_copia.numPalabras(); ++i)
    {
        assert(palabras_copia[i] == palabras[i]);
    }
}

// Prueba de numPalabras
void test_numPalabras()
{
    Palabras palabras;
    for (size_t i = 1; i <= 100; ++i)
    {
        Resultado res;
        palabras.insertar(string("palabra_") + to_string(i), res);
        assert(res == OK);
        assert(palabras.numPalabras() == i);
    }
}

// Prueba de insertar
void test_insertar()
{
    Palabras palabras;
    vector<string> v_palabras = {"ahora", "barco", "cuerda", "era", "fuego", "hace", "la", "puerta"};

    for (size_t i = 0; i < v_palabras.size(); ++i)
    {
        Resultado res;
        palabras.insertar(v_palabras[i], res);
        assert(res == OK);
        assert(palabras.numPalabras() == i + 1);
        for (size_t j = 0; j <= i; ++j)
        {
            assert(palabras[j] == v_palabras[j]);
        }
    }

    for (size_t i = 0; i < v_palabras.size(); ++i)
    {
        Resultado res;
        palabras.insertar(v_palabras[i], res);
        assert(res == YA_EXISTE);
        assert(palabras.numPalabras() == v_palabras.size());
        for (size_t j = 0; j <= i; ++j)
        {
            assert(palabras[j] == v_palabras[j]);
        }
    }
}

// Prueba para buscar
void test_buscar()
{
    Palabras palabras;
    vector<string> v_palabras = {"que", "por", "mayo", "era", "cuando", "hace", "la", "calor"};

    for (size_t i = 0; i < v_palabras.size(); ++i)
    {
        Resultado res;
        palabras.insertar(v_palabras[i], res);
    }
    for (size_t i = 0; i < v_palabras.size(); ++i)
    {
        assert(palabras.buscar(v_palabras[i]));
        assert(!palabras.buscar(v_palabras[i] + v_palabras[i]));
    }
}

// Prueba de eliminar
void test_eliminar()
{
    Palabras palabras;
    vector<string> v_palabras = {"que", "por", "mayo", "era", "cuando", "hace", "la", "calor"};

    for (size_t i = 0; i < v_palabras.size(); ++i)
    {
        Resultado res;
        palabras.insertar(v_palabras[i], res);
    }

    for (size_t i = 0; i < v_palabras.size(); ++i)
    {
        Resultado res;
        palabras.eliminar(v_palabras[i], res);
        assert(res == OK);
        assert(!palabras.buscar(v_palabras[i]));
        assert(palabras.numPalabras() == v_palabras.size() - i - 1);
        palabras.eliminar(v_palabras[i], res);
        assert(res == NO_EXISTE);
        assert(palabras.numPalabras() == v_palabras.size() - i - 1);
    }
}

// Prueba de leerPalabras
void test_leerPalabras()
{
    Palabras palabras;

    Resultado res;
    palabras.leerPalabras(FIC_PALABRAS_POSITIVAS, res);
    assert(res == OK);

    assert(palabras.numPalabras() == 2006);

    assert(palabras[0] == "a+");
    assert(palabras[186] == "beneficent");
    assert(palabras[611] == "examplary");
    assert(palabras[2005] == "zippy");
}

// Prueba de escribirPalabras
void test_escribirPalabras()
{
    Palabras palabras;

    Resultado res;
    palabras.leerPalabras(FIC_PALABRAS_POSITIVAS, res);
    palabras.escribirPalabras("__positive-words.txt", res);
    palabras = Palabras();
    palabras.leerPalabras("__positive-words.txt", res);
    assert(res == OK);
    assert(palabras.numPalabras() == 2006);

    assert(palabras[0] == "a+");
    assert(palabras[186] == "beneficent");
    assert(palabras[611] == "examplary");
    assert(palabras[2005] == "zippy");
}

//***************************
int main()
{
    // Prueba del constructor por defecto
    cout << "testing... 'Palabras()'" << endl;
    test_constructor();
    cout << "   --- OK." << endl;

    // Prueba del constructor de copia
    cout << "testing... 'Palabras(const Palabras &o)'" << endl;
    test_constructor_copia();
    cout << "   --- OK." << endl;

    // Prueba de numPalabras
    cout << "testing... 'numPalabras()'" << endl;
    test_numPalabras();
    cout << "   --- OK." << endl;

    // Prueba de insertar
    cout << "testing... 'insertar(const std::string &pal, Resultado &res)'" << endl;
    test_insertar();
    cout << "   --- OK." << endl;

    // Prueba de buscar
    cout << "testing... 'buscar(const std::string &pal) const'" << endl;
    test_buscar();
    cout << "   --- OK." << endl;

    // Prueba de eliminar
    cout << "testing... 'eliminar(const std::string &pal, Resultado &res)'" << endl;
    test_eliminar();
    cout << "   --- OK." << endl;

    // Prueba de leerPalabras
    cout << "testing... 'leerPalabras(const std::string &nombre_fic, Resultado &res)'" << endl;
    test_leerPalabras();
    cout << "   --- OK." << endl;

    // Prueba de escribirPalabras
    cout << "testing... 'escribirPalabras(const std::string &nombre_fic, Resultado &res)'" << endl;
    test_escribirPalabras();
    cout << "   --- OK." << endl;

    cout << endl
         << "--- TEST OK." << endl;
}