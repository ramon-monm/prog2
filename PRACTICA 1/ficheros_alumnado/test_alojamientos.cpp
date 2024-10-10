/******************************************************************************
 * test_alojamientos.cpp
 *
 * Programa principal de prueba del módulo Alojamientos.
 *
 * Alumno/a:
 * Fecha:
 *****************************************************************************/

#include "alojamientos.hpp"
#include "utilidades.hpp"

#include <iostream>
#include <string>
#include <cassert>
#include <cmath>
#include <iomanip>

using namespace std;
using namespace bblProg2;

const string FIC_ALOJAMIENTOS = "alojamientos.csv";

// Operador de asignación de Alojamientos
Alojamiento asignar_alojamiento(unsigned id_alo,
                                const string &nom,
                                unsigned id_anf,
                                const string &nom_anf,
                                const string &barr,
                                double lat,
                                double lon,
                                const string &tipo_alo,
                                double prec,
                                unsigned min_noch,
                                unsigned dis_365)
{
    Alojamiento alojamiento;

    alojamiento.id_alojamiento = id_alo;      // Identificador (único) del alojamiento
    alojamiento.nombre = nom;                 // Nombre del alojamiento
    alojamiento.id_anfitrion = id_anf;        // Identificador (único) del anfitrión
    alojamiento.nombre_anfitrion = nom_anf;   // Nombre del anfitrión
    alojamiento.barrio = barr;                // Barrio (zona) donde se ubica el apartamento
    alojamiento.latitud = lat;                // Latitud de la ubicación del apartamento
    alojamiento.longitud = lon;               // Longitud de la ubicación del apartamento
    alojamiento.tipo_alojamiento = tipo_alo;  // Tipo de alojamiento
    alojamiento.precio = prec;                // Precio del alojamiento por cada día de estancia
    alojamiento.minimo_noches = min_noch;     // Mínimo número de noches que se puede alquilar
    alojamiento.disponibilidad_365 = dis_365; // Número de días al año que está disponible

    return alojamiento;
}

// Operador de comparación de igualdad
bool operator==(const Alojamiento &alojamiento, const Alojamiento &otro_alojamiento)
{
    bool iguales = false;
    if (alojamiento.id_alojamiento == otro_alojamiento.id_alojamiento &&
        alojamiento.nombre == otro_alojamiento.nombre &&
        alojamiento.id_anfitrion == otro_alojamiento.id_anfitrion &&
        alojamiento.nombre_anfitrion == otro_alojamiento.nombre_anfitrion &&
        alojamiento.barrio == otro_alojamiento.barrio &&
        alojamiento.latitud == otro_alojamiento.latitud &&
        alojamiento.longitud == otro_alojamiento.longitud &&
        alojamiento.tipo_alojamiento == otro_alojamiento.tipo_alojamiento &&
        alojamiento.precio == otro_alojamiento.precio &&
        alojamiento.minimo_noches == otro_alojamiento.minimo_noches &&
        alojamiento.disponibilidad_365 == otro_alojamiento.disponibilidad_365)
    {
        iguales = true;
    }

    return iguales;
}

// Operador de comparación de Alojamientos
bool operator==(const Alojamientos &alojas, const Alojamientos &otro_alojas)
{
    bool iguales = alojas.num_alojamientos == otro_alojas.num_alojamientos;

    unsigned i = 0;

    while (i < alojas.num_alojamientos && iguales)
    {
        iguales = alojas.alojamientos[i] == otro_alojas.alojamientos[i];
        i++;
    }

    return iguales;
}

// Prueba de void insertar_alojamiento(const Alojamiento &alojamiento, Resultado &res)
void test_insertar_alojamiento()
{
    Alojamientos alojas;
    Resultado res;
    Alojamiento aloja;

    alojas.num_alojamientos = 0;

    aloja = asignar_alojamiento(170651, "Petit Charm Rooftop next to heaven", 814021, "Marie", "Sdermalms", 59.31568, 18.03138, "Entire home/apt", 745, 3, 197);
    insertar_alojamiento(aloja, alojas, res);
    assert(res == OK);
    assert(alojas.num_alojamientos == 1);
    assert(alojas.alojamientos[0] == asignar_alojamiento(170651, "Petit Charm Rooftop next to heaven", 814021, "Marie", "Sdermalms", 59.31568, 18.03138, "Entire home/apt", 745, 3, 197));
    insertar_alojamiento(aloja, alojas, res);
    assert(res == YA_EXISTE);

    aloja = asignar_alojamiento(42808, "Quiet room right DOWNTOWN Stockholm", 186922, "Nina", "Norrmalms", 59.34342, 18.05298, "Private room", 853, 1, 272);
    insertar_alojamiento(aloja, alojas, res);
    assert(res == OK);
    assert(alojas.num_alojamientos == 2);
    assert(alojas.alojamientos[1] == asignar_alojamiento(170651, "Petit Charm Rooftop next to heaven", 814021, "Marie", "Sdermalms", 59.31568, 18.03138, "Entire home/apt", 745, 3, 197));
    assert(alojas.alojamientos[0] == asignar_alojamiento(42808, "Quiet room right DOWNTOWN Stockholm", 186922, "Nina", "Norrmalms", 59.34342, 18.05298, "Private room", 853, 1, 272));
    insertar_alojamiento(aloja, alojas, res);
    assert(res == YA_EXISTE);

    aloja = asignar_alojamiento(155685, "Hornstull with water view!", 748592, "Robert", "Sdermalms", 59.31535, 18.03277, "Entire home/apt", 3247, 4, 0);
    insertar_alojamiento(aloja, alojas, res);
    assert(res == OK);
    assert(alojas.num_alojamientos == 3);
    assert(alojas.alojamientos[2] == asignar_alojamiento(170651, "Petit Charm Rooftop next to heaven", 814021, "Marie", "Sdermalms", 59.31568, 18.03138, "Entire home/apt", 745, 3, 197));
    assert(alojas.alojamientos[1] == asignar_alojamiento(155685, "Hornstull with water view!", 748592, "Robert", "Sdermalms", 59.31535, 18.03277, "Entire home/apt", 3247, 4, 0));
    assert(alojas.alojamientos[0] == asignar_alojamiento(42808, "Quiet room right DOWNTOWN Stockholm", 186922, "Nina", "Norrmalms", 59.34342, 18.05298, "Private room", 853, 1, 272));
    insertar_alojamiento(aloja, alojas, res);
    assert(res == YA_EXISTE);

    aloja = asignar_alojamiento(145320, "In the middle of it all - with a view!", 703851, "Kim", "Sdermalms", 59.31364, 18.05256, "Private room", 1285, 2, 0);
    insertar_alojamiento(aloja, alojas, res);
    assert(res == OK);
    assert(alojas.num_alojamientos == 4);
    assert(alojas.alojamientos[3] == asignar_alojamiento(170651, "Petit Charm Rooftop next to heaven", 814021, "Marie", "Sdermalms", 59.31568, 18.03138, "Entire home/apt", 745, 3, 197));
    assert(alojas.alojamientos[2] == asignar_alojamiento(155685, "Hornstull with water view!", 748592, "Robert", "Sdermalms", 59.31535, 18.03277, "Entire home/apt", 3247, 4, 0));
    assert(alojas.alojamientos[1] == asignar_alojamiento(145320, "In the middle of it all - with a view!", 703851, "Kim", "Sdermalms", 59.31364, 18.05256, "Private room", 1285, 2, 0));
    assert(alojas.alojamientos[0] == asignar_alojamiento(42808, "Quiet room right DOWNTOWN Stockholm", 186922, "Nina", "Norrmalms", 59.34342, 18.05298, "Private room", 853, 1, 272));
    insertar_alojamiento(aloja, alojas, res);
    assert(res == YA_EXISTE);

    // Borro todo
    alojas.num_alojamientos = 0;
    // Inserto 3000 alojamientos
    for (unsigned i = 0; i < 3000; i++)
    {
        aloja = asignar_alojamiento(i, "Quiet room right DOWNTOWN Stockholm", 186922, "Nina", "Norrmalms", 59.34342, 18.05298, "Private room", 853, 1, 272);
        insertar_alojamiento(aloja, alojas, res);
        assert(res == OK);
    }
    // Pero ya no caben más
    aloja = asignar_alojamiento(3000, "Quiet room right DOWNTOWN Stockholm", 186922, "Nina", "Norrmalms", 59.34342, 18.05298, "Private room", 853, 1, 272);
    insertar_alojamiento(aloja, alojas, res);
    assert(res == LISTA_LLENA);
}

void test_leer_alojamientos()
{
    Alojamientos alojas;
    Alojamiento aloja;
    Resultado res;

    alojas.num_alojamientos = 0;

    leer_alojamientos(FIC_ALOJAMIENTOS, alojas, res);

    assert(res == OK);
    assert(alojas.num_alojamientos == 1997);

    assert(alojas.alojamientos[0] == asignar_alojamiento(42808, "Quiet room right DOWNTOWN Stockholm", 186922, "Nina", "Norrmalms", 59.34342, 18.05298, "Private room", 853, 1, 272));
    assert(alojas.alojamientos[224] == asignar_alojamiento(2960624, "Seaview from a flat close to city", 5872968, "Caroline", "Bromma", 59.34141, 17.87939, "Entire home/apt", 402, 4, 125));
    assert(alojas.alojamientos[1000] == asignar_alojamiento(14601613, "Cute apartment in central Stockholm", 13266721, "Valerie", "Norrmalms", 59.34635, 18.05744, "Entire home/apt", 1501, 3, 314));
    assert(alojas.alojamientos[1996] == asignar_alojamiento(37012919, "Neat Apartment with Great Communications", 15086527, "Daniel", "stermalms", 59.34725, 18.06933, "Entire home/apt", 1001, 3, 11));

    leer_alojamientos(FIC_ALOJAMIENTOS, alojas, res);
    assert(res == OK);
    assert(alojas.num_alojamientos == 1997); // No debería haber incluido ninguno más

    leer_alojamientos("este_fichero_fake_no_existe.csv", alojas, res);
    assert(res == FIC_ERROR);
    assert(alojas.num_alojamientos == 1997); // Se mantiene el número de alojamientos
}

void test_escribir_fichero()
{
    Alojamientos alojas, _alojas;
    Resultado res;

    alojas.num_alojamientos = 0;
    _alojas.num_alojamientos = 0;

    leer_alojamientos(FIC_ALOJAMIENTOS, alojas, res);

    escribir_alojamientos("_" + FIC_ALOJAMIENTOS, alojas, res);
    assert(res == OK);

    leer_alojamientos("_" + FIC_ALOJAMIENTOS, _alojas, res);
    assert(res == OK);

    assert(alojas == _alojas);
}

//**********************
int main()
{
    // Prueba de insertar_alojamiento
    cout << "testing... 'void insertar_alojamiento(const Alojamiento &, const Alojamientos &, Resultado &)'" << endl;
    test_insertar_alojamiento();
    cout << "   --- OK." << endl;

    // Prueba de leer_alojamientos
    cout << "testing... 'void leer_alojamientos(const std::string &, Alojamientos &, , Resultado &)'" << endl;
    test_leer_alojamientos();
    cout << "   --- OK." << endl;

    // Prueba de escribir_alojamientos
    cout << "testing... 'void escribir_alojamientos(const std::string &, const Alojamientos &, Resultado &)'" << endl;
    test_escribir_fichero();
    cout << "   --- OK." << endl;

    cout << endl
         << "--- TEST OK." << endl;

    return 0;
}
