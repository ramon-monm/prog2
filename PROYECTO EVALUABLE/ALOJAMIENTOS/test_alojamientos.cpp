/******************************************************************************
 * test_alojamientos.cpp
 *
 * Programa principal de prueba del módulo Alojamientos.
 *
 * Alumno/a:
 * Fecha:
 *****************************************************************************/

#include "utilidades.hpp"
#include "alojamiento.hpp"
#include "alojamientos.hpp"

#include <iostream>
#include <string>
#include <cassert>
#include <cmath>
#include <iomanip>

using namespace std;
using namespace bblProg2;

const string FIC_ALOJAMIENTOS = "alojamientos.csv";

// Prueba del constructor por defecto
void testConstructor()
{
    Alojamientos alojas;

    assert(alojas.numeroAlojamientos() == 0);
}

// Prueba de void insertarAlojamiento(const Alojamiento &alojamiento, Resultado &res)
void testInsertarAlojamiento()
{
    Alojamientos alojas;
    Resultado res;
    Alojamiento aloja;

    aloja = Alojamiento{170651, "Petit Charm Rooftop next to heaven", 814021, "Marie", "Sdermalms", 59.31568, 18.03138, "Entire home/apt", 745, 3, 197};
    alojas.insertarAlojamiento(aloja, res);
    assert(res == OK);
    assert(alojas.numeroAlojamientos() == 1);
    assert((alojas[0] == Alojamiento{170651, "Petit Charm Rooftop next to heaven", 814021, "Marie", "Sdermalms", 59.31568, 18.03138, "Entire home/apt", 745, 3, 197}));
    alojas.insertarAlojamiento(aloja, res);
    assert(res == YA_EXISTE);

    aloja = Alojamiento{42808, "Quiet room right DOWNTOWN Stockholm", 186922, "Nina", "Norrmalms", 59.34342, 18.05298, "Private room", 853, 1, 272};
    alojas.insertarAlojamiento(aloja, res);
    assert(res == OK);
    assert(alojas.numeroAlojamientos() == 2);
    assert((alojas[1] == Alojamiento{170651, "Petit Charm Rooftop next to heaven", 814021, "Marie", "Sdermalms", 59.31568, 18.03138, "Entire home/apt", 745, 3, 197}));
    assert((alojas[0] == Alojamiento{42808, "Quiet room right DOWNTOWN Stockholm", 186922, "Nina", "Norrmalms", 59.34342, 18.05298, "Private room", 853, 1, 272}));
    alojas.insertarAlojamiento(aloja, res);
    assert(res == YA_EXISTE);

    aloja = Alojamiento{155685, "Hornstull with water view!", 748592, "Robert", "Sdermalms", 59.31535, 18.03277, "Entire home/apt", 3247, 4, 0};
    alojas.insertarAlojamiento(aloja, res);
    assert(res == OK);
    assert(alojas.numeroAlojamientos() == 3);
    assert((alojas[2] == Alojamiento{170651, "Petit Charm Rooftop next to heaven", 814021, "Marie", "Sdermalms", 59.31568, 18.03138, "Entire home/apt", 745, 3, 197}));
    assert((alojas[1] == Alojamiento{155685, "Hornstull with water view!", 748592, "Robert", "Sdermalms", 59.31535, 18.03277, "Entire home/apt", 3247, 4, 0}));
    assert((alojas[0] == Alojamiento{42808, "Quiet room right DOWNTOWN Stockholm", 186922, "Nina", "Norrmalms", 59.34342, 18.05298, "Private room", 853, 1, 272}));
    alojas.insertarAlojamiento(aloja, res);
    assert(res == YA_EXISTE);

    aloja = Alojamiento{145320, "In the middle of it all - with a view!", 703851, "Kim", "Sdermalms", 59.31364, 18.05256, "Private room", 1285, 2, 0};
    alojas.insertarAlojamiento(aloja, res);
    assert(res == OK);
    assert(alojas.numeroAlojamientos() == 4);
    assert((alojas[3] == Alojamiento{170651, "Petit Charm Rooftop next to heaven", 814021, "Marie", "Sdermalms", 59.31568, 18.03138, "Entire home/apt", 745, 3, 197}));
    assert((alojas[2] == Alojamiento{155685, "Hornstull with water view!", 748592, "Robert", "Sdermalms", 59.31535, 18.03277, "Entire home/apt", 3247, 4, 0}));
    assert((alojas[1] == Alojamiento{145320, "In the middle of it all - with a view!", 703851, "Kim", "Sdermalms", 59.31364, 18.05256, "Private room", 1285, 2, 0}));
    assert((alojas[0] == Alojamiento{42808, "Quiet room right DOWNTOWN Stockholm", 186922, "Nina", "Norrmalms", 59.34342, 18.05298, "Private room", 853, 1, 272}));
    alojas.insertarAlojamiento(aloja, res);
    assert(res == YA_EXISTE);

    // Borro todo
    alojas = Alojamientos{};
    // Inserto 3000 alojamientos
    for (unsigned i = 0; i < 3000; i++)
    {
        aloja = Alojamiento{i, "Quiet room right DOWNTOWN Stockholm", 186922, "Nina", "Norrmalms", 59.34342, 18.05298, "Private room", 853, 1, 272};
        alojas.insertarAlojamiento(aloja, res);
        assert(res == OK);
    }
    // Pero ya no caben más
    aloja = Alojamiento{3000, "Quiet room right DOWNTOWN Stockholm", 186922, "Nina", "Norrmalms", 59.34342, 18.05298, "Private room", 853, 1, 272};
    alojas.insertarAlojamiento(aloja, res);
    assert(res == LISTA_LLENA);
}

// Prueba del constructor de copia
void testConstructorCopia()
{
    Alojamientos alojas;
    Resultado res;

    Alojamiento aloja;
    aloja = Alojamiento{170651, "Petit Charm Rooftop next to heaven", 814021, "Marie", "Sdermalms", 59.31568, 18.03138, "Entire home/apt", 745, 3, 197};
    alojas.insertarAlojamiento(aloja, res);
    aloja = Alojamiento{42808, "Quiet room right DOWNTOWN Stockholm", 186922, "Nina", "Norrmalms", 59.34342, 18.05298, "Private room", 853, 1, 272};
    alojas.insertarAlojamiento(aloja, res);
    aloja = Alojamiento{155685, "Hornstull with water view!", 748592, "Robert", "Sdermalms", 59.31535, 18.03277, "Entire home/apt", 3247, 4, 0};
    alojas.insertarAlojamiento(aloja, res);
    aloja = Alojamiento{145320, "In the middle of it all - with a view!", 703851, "Kim", "Sdermalms", 59.31364, 18.05256, "Private room", 1285, 2, 0};
    alojas.insertarAlojamiento(aloja, res);

    Alojamientos alojas_copia{alojas};

    assert(alojas == alojas_copia);
    assert(alojas.numeroAlojamientos() == alojas_copia.numeroAlojamientos());
}

void testConsultarAlojamiento()
{
    Alojamientos alojas;
    Resultado res;
    Alojamiento aloja;

    aloja = Alojamiento{170651, "Petit Charm Rooftop next to heaven", 814021, "Marie", "Sdermalms", 59.31568, 18.03138, "Entire home/apt", 745, 3, 197};
    alojas.insertarAlojamiento(aloja, res);
    aloja = Alojamiento{42808, "Quiet room right DOWNTOWN Stockholm", 186922, "Nina", "Norrmalms", 59.34342, 18.05298, "Private room", 853, 1, 272};
    alojas.insertarAlojamiento(aloja, res);
    aloja = Alojamiento{155685, "Hornstull with water view!", 748592, "Robert", "Sdermalms", 59.31535, 18.03277, "Entire home/apt", 3247, 4, 0};
    alojas.insertarAlojamiento(aloja, res);
    aloja = Alojamiento{145320, "In the middle of it all - with a view!", 703851, "Kim", "Sdermalms", 59.31364, 18.05256, "Private room", 1285, 2, 0};
    alojas.insertarAlojamiento(aloja, res);

    alojas.consultarAlojamiento(170651, aloja, res);
    assert(res == OK);
    assert((aloja == Alojamiento{170651, "Petit Charm Rooftop next to heaven", 814021, "Marie", "Sdermalms", 59.31568, 18.03138, "Entire home/apt", 745, 3, 197}));

    alojas.consultarAlojamiento(155685, aloja, res);
    assert(res == OK);
    assert((aloja == Alojamiento{155685, "Hornstull with water view!", 748592, "Robert", "Sdermalms", 59.31535, 18.03277, "Entire home/apt", 3247, 4, 0}));

    alojas.consultarAlojamiento(145320, aloja, res);
    assert(res == OK);
    assert((aloja == Alojamiento{145320, "In the middle of it all - with a view!", 703851, "Kim", "Sdermalms", 59.31364, 18.05256, "Private room", 1285, 2, 0}));

    alojas.consultarAlojamiento(42808, aloja, res);
    assert(res == OK);
    assert((aloja == Alojamiento{42808, "Quiet room right DOWNTOWN Stockholm", 186922, "Nina", "Norrmalms", 59.34342, 18.05298, "Private room", 853, 1, 272}));

    alojas.consultarAlojamiento(11111, aloja, res);
    assert(res == NO_EXISTE);

    alojas.consultarAlojamiento(55555, aloja, res);
    assert(res == NO_EXISTE);
}

void testNumeroAlojamientos()
{
    Alojamientos alojas;
    Alojamiento aloja;
    Resultado res;

    // Inserto 3000 alojamientos
    for (unsigned i = 0; i < 3000; i++)
    {
        assert(alojas.numeroAlojamientos() == i);
        aloja = Alojamiento{i, "Quiet room right DOWNTOWN Stockholm", 186922, "Nina", "Norrmalms", 59.34342, 18.05298, "Private room", 853, 1, 272};
        alojas.insertarAlojamiento(aloja, res);
        assert(res == OK);
    }
    // Pero ya no caben más
    assert(alojas.numeroAlojamientos() == 3000);
    aloja = Alojamiento{3000, "Quiet room right DOWNTOWN Stockholm", 186922, "Nina", "Norrmalms", 59.34342, 18.05298, "Private room", 853, 1, 272};
    alojas.insertarAlojamiento(aloja, res);
    assert(alojas.numeroAlojamientos() == 3000);
}

void testListaAlojamientos()
{
    Alojamientos alojas;
    Alojamiento aloja;
    Resultado res;
    Ids ids_alojamientos;

    // Inserto 3000 alojamientos
    for (unsigned i = 0; i < 3000; i++)
    {
        aloja = Alojamiento{i, "Quiet room right DOWNTOWN Stockholm", 186922, "Nina", "Norrmalms", 59.34342, 18.05298, "Private room", 853, 1, 272};
        alojas.insertarAlojamiento(aloja, res);
    }

    alojas.listaAlojamientos(ids_alojamientos);
    assert(ids_alojamientos.num_ids == 3000);

    for (unsigned i = 0; i < 3000; i++)
    {
        assert(ids_alojamientos.ids[i] == i);
    }
}

void testLeerAlojamientos()
{
    Alojamientos alojas;
    Alojamiento aloja;
    Resultado res;

    alojas.leerAlojamientos(FIC_ALOJAMIENTOS, res);

    assert(res == OK);
    assert(alojas.numeroAlojamientos() == 1997);

    assert((alojas[0] == Alojamiento{42808, "Quiet room right DOWNTOWN Stockholm", 186922, "Nina", "Norrmalms", 59.34342, 18.05298, "Private room", 853, 1, 272}));
    assert((alojas[224] == Alojamiento{2960624, "Seaview from a flat close to city", 5872968, "Caroline", "Bromma", 59.34141, 17.87939, "Entire home/apt", 402, 4, 125}));
    assert((alojas[1000] == Alojamiento{14601613, "Cute apartment in central Stockholm", 13266721, "Valerie", "Norrmalms", 59.34635, 18.05744, "Entire home/apt", 1501, 3, 314}));
    assert((alojas[1996] == Alojamiento{37012919, "Neat Apartment with Great Communications", 15086527, "Daniel", "stermalms", 59.34725, 18.06933, "Entire home/apt", 1001, 3, 11}));

    alojas.leerAlojamientos(FIC_ALOJAMIENTOS, res);
    assert(res == OK);
    assert(alojas.numeroAlojamientos() == 1997); // No debería haber incluido ninguno más

    alojas.leerAlojamientos("este_fichero_fake_no_existe.csv", res);
    assert(res == FIC_ERROR);
    assert(alojas.numeroAlojamientos() == 1997); // Se mantiene el número de alojamientos
}

void testAlojamientosAnfitrion()
{
    Alojamientos alojas;
    Resultado res;

    alojas.leerAlojamientos(FIC_ALOJAMIENTOS, res);

    for (unsigned i = 0; i < alojas.numeroAlojamientos(); i++)
    {
        Ids ids_alojamientos;
        unsigned id_anfitrion = alojas[i].consultarIdAnfitrion();
        alojas.alojamientosAnfitrion(id_anfitrion, ids_alojamientos);

        unsigned num_alojamientos_anfitrion = 0;
        for (unsigned j = 0; j < alojas.numeroAlojamientos(); j++)
        {
            if (alojas[j].consultarIdAnfitrion() == id_anfitrion)
            {
                assert(ids_alojamientos.ids[num_alojamientos_anfitrion] == alojas[j].consultarIdAlojamiento());
                num_alojamientos_anfitrion++;
            }
        }
        assert(num_alojamientos_anfitrion == ids_alojamientos.num_ids);
    }
}

void testAlojamientosAlrededor()
{
    Alojamientos alojas;
    Resultado res;
    Ids ids_alojamientos;

    alojas.leerAlojamientos(FIC_ALOJAMIENTOS, res);

    alojas.alojamientosAlrededor(59.34342, 18.05298, 0.5, ids_alojamientos);
    assert(ids_alojamientos.num_ids == 107);
    assert(ids_alojamientos.ids[0] == 42808);
    assert(ids_alojamientos.ids[49] == 13410312);
    assert(ids_alojamientos.ids[99] == 31896315);

    alojas.alojamientosAlrededor(59.34342, 18.05298, 1.5, ids_alojamientos);
    assert(ids_alojamientos.num_ids == 410);
    assert(ids_alojamientos.ids[0] == 42808);
    assert(ids_alojamientos.ids[199] == 13534140);
    assert(ids_alojamientos.ids[399] == 34794930);
}

void testAlojamientosBarrio()
{
    Alojamientos alojas;
    Resultado res;
    Ids ids_alojamientos;

    alojas.leerAlojamientos(FIC_ALOJAMIENTOS, res);

    alojas.alojamientosBarrio("Sdermalms", ids_alojamientos);

    assert(ids_alojamientos.num_ids == 567);

    for (unsigned i = 0; i < ids_alojamientos.num_ids; i++)
    {
        Alojamiento aloja;
        Resultado res;
        alojas.consultarAlojamiento(ids_alojamientos.ids[i], aloja, res);
        assert(res == OK);
        assert(aloja.consultar_barrio() == "Sdermalms");
    }

    alojas.alojamientosBarrio("Rinkeby-Tensta", ids_alojamientos);

    assert(ids_alojamientos.num_ids == 32);

    for (unsigned i = 0; i < ids_alojamientos.num_ids; i++)
    {
        Alojamiento aloja;
        Resultado res;
        alojas.consultarAlojamiento(ids_alojamientos.ids[i], aloja, res);
        assert(res == OK);
        assert(aloja.consultar_barrio() == "Rinkeby-Tensta");
    }

    alojas.alojamientosBarrio("Huelin", ids_alojamientos);

    assert(ids_alojamientos.num_ids == 0);
}

void testAlojamientosTipo()
{
    Alojamientos alojas;
    Resultado res;
    Ids ids_alojamientos;

    alojas.leerAlojamientos(FIC_ALOJAMIENTOS, res);

    alojas.alojamientosTipo("Private room", ids_alojamientos);

    assert(ids_alojamientos.num_ids == 486);

    for (unsigned i = 0; i < ids_alojamientos.num_ids; i++)
    {
        Alojamiento aloja;
        Resultado res;
        alojas.consultarAlojamiento(ids_alojamientos.ids[i], aloja, res);
        assert(res == OK);
        assert(aloja.consultarTipoAlojamiento() == "Private room");
    }

    alojas.alojamientosTipo("Entire home/apt", ids_alojamientos);

    assert(ids_alojamientos.num_ids == 1489);

    for (unsigned i = 0; i < ids_alojamientos.num_ids; i++)
    {
        Alojamiento aloja;
        Resultado res;
        alojas.consultarAlojamiento(ids_alojamientos.ids[i], aloja, res);
        assert(res == OK);
        assert(aloja.consultarTipoAlojamiento() == "Entire home/apt");
    }

    alojas.alojamientosTipo("Casa Mata", ids_alojamientos);

    assert(ids_alojamientos.num_ids == 0);
}

void testAlojamientosPrecio()
{
    Alojamientos alojas;
    Resultado res;
    Ids ids_alojamientos;

    alojas.leerAlojamientos(FIC_ALOJAMIENTOS, res);

    alojas.alojamientosPrecio(200.0, ids_alojamientos);

    assert(ids_alojamientos.num_ids == 20);

    for (unsigned i = 0; i < ids_alojamientos.num_ids; i++)
    {
        Alojamiento aloja;
        Resultado res;
        alojas.consultarAlojamiento(ids_alojamientos.ids[i], aloja, res);
        assert(res == OK);
        assert(aloja.consultarPrecio() <= 200.0);
    }

    alojas.alojamientosPrecio(300.0, ids_alojamientos);

    assert(ids_alojamientos.num_ids == 71);

    for (unsigned i = 0; i < ids_alojamientos.num_ids; i++)
    {
        Alojamiento aloja;
        Resultado res;
        alojas.consultarAlojamiento(ids_alojamientos.ids[i], aloja, res);
        assert(res == OK);
        assert(aloja.consultarPrecio() <= 300.0);
    }

    alojas.alojamientosPrecio(100.0, ids_alojamientos);

    assert(ids_alojamientos.num_ids == 0);
}

void testAlojamientosNoches()
{
    Alojamientos alojas;
    Resultado res;
    Ids ids_alojamientos;

    alojas.leerAlojamientos(FIC_ALOJAMIENTOS, res);

    alojas.alojamientosNoches(1, ids_alojamientos);

    assert(ids_alojamientos.num_ids == 462);

    for (unsigned i = 0; i < ids_alojamientos.num_ids; i++)
    {
        Alojamiento aloja;
        Resultado res;
        alojas.consultarAlojamiento(ids_alojamientos.ids[i], aloja, res);
        assert(res == OK);
        assert(aloja.consultarMinimoNoches() <= 1);
    }

    alojas.alojamientosNoches(2, ids_alojamientos);

    assert(ids_alojamientos.num_ids == 1087);
}

void testAlojamientosFiltros()
{
    Alojamientos alojas;
    Resultado res;
    Ids ids_alojamientos;

    alojas.leerAlojamientos(FIC_ALOJAMIENTOS, res);

    alojas.alojamientosFiltros("Sdermalms", "Entire home/apt", 600.0, 2, ids_alojamientos);

    assert(ids_alojamientos.num_ids == 13);

    for (unsigned i = 0; i < ids_alojamientos.num_ids; i++)
    {
        Alojamiento aloja;
        Resultado res;
        alojas.consultarAlojamiento(ids_alojamientos.ids[i], aloja, res);
        assert(res == OK);
        assert(aloja.consultar_barrio() == "Sdermalms");
        assert(aloja.consultarTipoAlojamiento() == "Entire home/apt");
        assert(aloja.consultarPrecio() <= 600.0);
        assert(aloja.consultarMinimoNoches() <= 2);
    }

    alojas.alojamientosFiltros("Rinkeby-Tensta", "Private room", 900.0, 2, ids_alojamientos);

    assert(ids_alojamientos.num_ids == 11);

    for (unsigned i = 0; i < ids_alojamientos.num_ids; i++)
    {
        Alojamiento aloja;
        Resultado res;
        alojas.consultarAlojamiento(ids_alojamientos.ids[i], aloja, res);
        assert(res == OK);
        assert(aloja.consultar_barrio() == "Rinkeby-Tensta");
        assert(aloja.consultarTipoAlojamiento() == "Private room");
        assert(aloja.consultarPrecio() <= 900.0);
        assert(aloja.consultarMinimoNoches() <= 2);
    }
}

void testEscribirFichero()
{
    Alojamientos alojas, _alojas;
    Resultado res;

    alojas.leerAlojamientos(FIC_ALOJAMIENTOS, res);

    alojas.escribirEnFichero("_" + FIC_ALOJAMIENTOS, res);
    assert(res == OK);

    _alojas.leerAlojamientos("_" + FIC_ALOJAMIENTOS, res);
    assert(res == OK);

    assert(alojas == _alojas);
}

void testModificarAlojamiento()
{
    Alojamientos alojas;
    Resultado res;
    Alojamiento aloja;

    aloja = Alojamiento{170651, "Petit Charm Rooftop next to heaven", 814021, "Marie", "Sdermalms", 59.31568, 18.03138, "Entire home/apt", 745, 3, 197};
    alojas.insertarAlojamiento(aloja, res);
    aloja = Alojamiento{42808, "Quiet room right DOWNTOWN Stockholm", 186922, "Nina", "Norrmalms", 59.34342, 18.05298, "Private room", 853, 1, 272};
    alojas.insertarAlojamiento(aloja, res);
    aloja = Alojamiento{155685, "Hornstull with water view!", 748592, "Robert", "Sdermalms", 59.31535, 18.03277, "Entire home/apt", 3247, 4, 0};
    alojas.insertarAlojamiento(aloja, res);
    aloja = Alojamiento{145320, "In the middle of it all - with a view!", 703851, "Kim", "Sdermalms", 59.31364, 18.05256, "Private room", 1285, 2, 0};
    alojas.insertarAlojamiento(aloja, res);

    // Modificamos alojamientos
    aloja = Alojamiento{42808, "__Quiet room right DOWNTOWN Stockholm", 186922, "__Nina", "__Norrmalms", 59.34342, 18.05298, "__Private room", 853, 1, 272};
    alojas.modificarAlojamiento(aloja, res);
    assert(res == OK);
    assert(alojas.numeroAlojamientos() == 4);
    assert((alojas[0] == Alojamiento{42808, "__Quiet room right DOWNTOWN Stockholm", 186922, "__Nina", "__Norrmalms", 59.34342, 18.05298, "__Private room", 853, 1, 272}));

    aloja = Alojamiento{145320, "__In the middle of it all - with a view!", 703851, "__Kim", "__Sdermalms", 59.31364, 18.05256, "__Private room", 1285, 2, 0};
    alojas.modificarAlojamiento(aloja, res);
    assert(res == OK);
    assert(alojas.numeroAlojamientos() == 4);
    assert((alojas[1] == Alojamiento{145320, "__In the middle of it all - with a view!", 703851, "__Kim", "__Sdermalms", 59.31364, 18.05256, "__Private room", 1285, 2, 0}));

    aloja = Alojamiento{555555, "Hornstull with water view!", 748592, "Robert", "Sdermalms", 59.31535, 18.03277, "Entire home/apt", 3247, 4, 0};
    alojas.modificarAlojamiento(aloja, res);
    assert(res == NO_EXISTE);

    aloja = Alojamiento{170651, "__Petit Charm Rooftop next to heaven", 814021, "__Marie", "__Sdermalms", 59.31568, 18.03138, "__Entire home/apt", 745, 3, 197};
    alojas.modificarAlojamiento(aloja, res);
    assert(res == OK);
    assert(alojas.numeroAlojamientos() == 4);
    assert((alojas[3] == Alojamiento{170651, "__Petit Charm Rooftop next to heaven", 814021, "__Marie", "__Sdermalms", 59.31568, 18.03138, "__Entire home/apt", 745, 3, 197}));
}

void testEliminarAlojamiento()
{
    Alojamientos alojas;
    Resultado res;
    Alojamiento aloja;

    aloja = Alojamiento{170651, "Petit Charm Rooftop next to heaven", 814021, "Marie", "Sdermalms", 59.31568, 18.03138, "Entire home/apt", 745, 3, 197};
    alojas.insertarAlojamiento(aloja, res);
    aloja = Alojamiento{42808, "Quiet room right DOWNTOWN Stockholm", 186922, "Nina", "Norrmalms", 59.34342, 18.05298, "Private room", 853, 1, 272};
    alojas.insertarAlojamiento(aloja, res);
    aloja = Alojamiento{155685, "Hornstull with water view!", 748592, "Robert", "Sdermalms", 59.31535, 18.03277, "Entire home/apt", 3247, 4, 0};
    alojas.insertarAlojamiento(aloja, res);
    aloja = Alojamiento{145320, "In the middle of it all - with a view!", 703851, "Kim", "Sdermalms", 59.31364, 18.05256, "Private room", 1285, 2, 0};
    alojas.insertarAlojamiento(aloja, res);

    // Eiminamos alojamientos
    alojas.eliminarAlojamiento(42808, res);
    assert(res == OK);
    assert(alojas.numeroAlojamientos() == 3);
    assert((alojas[0] == Alojamiento{145320, "In the middle of it all - with a view!", 703851, "Kim", "Sdermalms", 59.31364, 18.05256, "Private room", 1285, 2, 0}));
    assert((alojas[1] == Alojamiento{155685, "Hornstull with water view!", 748592, "Robert", "Sdermalms", 59.31535, 18.03277, "Entire home/apt", 3247, 4, 0}));
    assert((alojas[2] == Alojamiento{170651, "Petit Charm Rooftop next to heaven", 814021, "Marie", "Sdermalms", 59.31568, 18.03138, "Entire home/apt", 745, 3, 197}));

    alojas.eliminarAlojamiento(170651, res);
    assert(res == OK);
    assert(alojas.numeroAlojamientos() == 2);
    assert((alojas[0] == Alojamiento{145320, "In the middle of it all - with a view!", 703851, "Kim", "Sdermalms", 59.31364, 18.05256, "Private room", 1285, 2, 0}));
    assert((alojas[1] == Alojamiento{155685, "Hornstull with water view!", 748592, "Robert", "Sdermalms", 59.31535, 18.03277, "Entire home/apt", 3247, 4, 0}));

    alojas.eliminarAlojamiento(145320, res);
    assert(res == OK);
    assert(alojas.numeroAlojamientos() == 1);
    assert((alojas[0] == Alojamiento{155685, "Hornstull with water view!", 748592, "Robert", "Sdermalms", 59.31535, 18.03277, "Entire home/apt", 3247, 4, 0}));

    alojas.eliminarAlojamiento(155685, res);
    assert(res == OK);
    assert(alojas.numeroAlojamientos() == 0);

    alojas.eliminarAlojamiento(155685, res);
    assert(res == NO_EXISTE);
}

//**********************
int main()
{
    // Prueba del constructor por defecto
    cout << "testing... 'Alojamientos()'" << endl;
    testConstructor();
    cout << "   --- OK." << endl;

    // Prueba de insertarAlojamiento
    cout << "testing... 'void insertarAlojamiento(const Alojamiento &, Resultado &)'" << endl;
    testInsertarAlojamiento();
    cout << "   --- OK." << endl;

    // Prueba del constructor de copia
    cout << "testing... 'Alojamientos(const Alojamientos &)'" << endl;
    testConstructorCopia();
    cout << "   --- OK." << endl;

    // Prueba de consultarAlojamiento
    cout << "testing... 'void consultarAlojamiento(unsigned, Alojamiento &, Resultado &) const'" << endl;
    testConsultarAlojamiento();
    cout << "   --- OK." << endl;

    // Prueba de numeroAlojamientos
    cout << "testing... 'unsigned numeroAlojamientos() const'" << endl;
    testNumeroAlojamientos();
    cout << "   --- OK." << endl;

    // Prueba de listaAlojamientos
    cout << "testing... 'void listaAlojamientos(Ids &) const;'" << endl;
    testListaAlojamientos();
    cout << "   --- OK." << endl;

    // Prueba de leerAlojamientos
    cout << "testing... 'void leerAlojamientos(const std::string &, Resultado &)'" << endl;
    testLeerAlojamientos();
    cout << "   --- OK." << endl;

    // Prueba de alojamientosAnfitrion
    cout << "testing... 'void alojamientosAnfitrion(unsigned, Ids &) const'" << endl;
    testAlojamientosAnfitrion();
    cout << "   --- OK." << endl;

    // Prueba de alojamientosAlrededor
    cout << "testing... 'void alojamientosAlrededor(double, double, double, Ids &) const'" << endl;
    testAlojamientosAlrededor();
    cout << "   --- OK." << endl;

    // Prueba de alojamientosBarrio
    cout << "testing... 'void alojamientosBarrio(const std::string &, Ids &) const'" << endl;
    testAlojamientosBarrio();
    cout << "   --- OK." << endl;

    // Prueba de alojamientosTipo
    cout << "testing... 'void alojamientosTipo(const std::string &, Ids &) const'" << endl;
    testAlojamientosTipo();
    cout << "   --- OK." << endl;

    // Prueba de alojamientosPrecio
    cout << "testing... 'void alojamientosPrecio(double, Ids &) const'" << endl;
    testAlojamientosPrecio();
    cout << "   --- OK." << endl;

    // Prueba de alojamientosNoches
    cout << "testing... 'void alojamientosNoches(unsigned, Ids &) const'" << endl;
    testAlojamientosNoches();
    cout << "   --- OK." << endl;

    // Prueba de alojamientosFiltros
    cout << "testing... 'void alojamientosFiltros(const std::string &, const std::string &, double, unsigned, Ids &) const'" << endl;
    testAlojamientosFiltros();
    cout << "   --- OK." << endl;

    // Prueba de escribirEnFichero
    cout << "testing... 'void escribirEnFichero(const std::string &, Resultado &)'" << endl;
    testEscribirFichero();
    cout << "   --- OK." << endl;

    // Prueba de modificarAlojamiento
    cout << "testing... ' void modificarAlojamiento(const Alojamiento &, Resultado &);'" << endl;
    testModificarAlojamiento();
    cout << "   --- OK." << endl;

    // Prueba de eliminarAlojamiento
    cout << "testing... ' void eliminarAlojamiento(const Alojamiento &, Resultado &);'" << endl;
    testEliminarAlojamiento();
    cout << "   --- OK." << endl;

    cout << endl
         << "--- TEST OK." << endl;

    return 0;
}