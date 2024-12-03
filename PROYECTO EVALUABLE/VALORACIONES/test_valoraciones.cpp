/******************************************************************************
 * test_valoraciones.cpp
 *
 * Programa principal de pruebas unitarias del módulo Valoraciones.
 *
 * Alumno/a:
 * Fecha:
 *****************************************************************************/

#include "utilidades.hpp"
#include "valoracion.hpp"
#include "valoraciones.hpp"

#include <iostream>
#include <string>
#include <cassert>
#include <cmath>
#include <iomanip>

using namespace std;
using namespace bblProg2;

const string FIC_VALORACIONES = "_valoraciones_test.csv";
const string FIC_PALABRAS_POSITIVAS = "positive-words.txt";
const string FIC_PALABRAS_NEGATIVAS = "negative-words.txt";

// Prueba del constructor por defecto
void test_constructor()
{
    Valoraciones valoraciones;
    unsigned pos, neg, neu;

    valoraciones.numeroValoraciones(pos, neg, neu);
    assert(pos == 0 && neg == 0 && neu == 0);
    valoraciones.numeroPalabras(pos, neg);
    assert(pos == 0 && neg == 0);
}

// Prueba del constructor de copia
void test_constructor_de_copia()
{
    Valoraciones valoraciones;
    Resultado res;
    unsigned pos, neg, neu;

    valoraciones.cargarPalabrasPositivas(FIC_PALABRAS_POSITIVAS, res);
    assert(res == OK);
    valoraciones.cargarPalabrasNegativas(FIC_PALABRAS_NEGATIVAS, res);
    assert(res == OK);
    valoraciones.numeroPalabras(pos, neg);
    assert(pos == 2006);
    assert(neg == 4783);

    valoraciones.cargarValoraciones(FIC_VALORACIONES, res);
    assert(res == OK);
    valoraciones.numeroValoraciones(pos, neg, neu);
    assert(pos == 8);
    assert(neg == 3);
    assert(neu == 0);

    // Llamada al constructor de copia
    Valoraciones copia{valoraciones};
    assert(valoraciones == copia);
}

// Prueba de cargar palabras positivas
void test_cargarPalabrasPositivas()
{
    Valoraciones valoraciones;
    Resultado res;
    unsigned pos, neg;
    Valoracion valoracion;
    string palabra;

    valoraciones.cargarPalabrasPositivas(FIC_PALABRAS_POSITIVAS, res);

    assert(res == OK);

    valoraciones.numeroPalabras(pos, neg);

    assert(pos == 2006);
    assert(neg == 0);

    valoraciones.__consultar_elemento_pos(0, false, true, valoracion, palabra);
    assert(palabra == "a+");
    valoraciones.__consultar_elemento_pos(999, false, true, valoracion, palabra);
    assert(palabra == "insightful");
    valoraciones.__consultar_elemento_pos(1999, false, true, valoracion, palabra);
    assert(palabra == "wows");
    valoraciones.__consultar_elemento_pos(2005, false, true, valoracion, palabra);
    assert(palabra == "zippy");
}

// Prueba de cargar palabras positivas
void test_cargar_palabras_negativas()
{
    Valoraciones valoraciones;
    Resultado res;
    unsigned pos, neg;
    Valoracion valoracion;
    string palabra;

    valoraciones.cargarPalabrasNegativas(FIC_PALABRAS_NEGATIVAS, res);

    assert(res == OK);

    valoraciones.numeroPalabras(pos, neg);

    assert(pos == 0);
    assert(neg == 4783);

    valoraciones.__consultar_elemento_pos(0, false, false, valoracion, palabra);
    assert(palabra == "2-faced");
    valoraciones.__consultar_elemento_pos(999, false, false, valoracion, palabra);
    assert(palabra == "despicably");
    valoraciones.__consultar_elemento_pos(1999, false, false, valoracion, palabra);
    assert(palabra == "head-aches");
    valoraciones.__consultar_elemento_pos(4782, false, false, valoracion, palabra);
    assert(palabra == "zombie");
}

// Prueba de cargarValoraciones
void test_cargar_valoraciones()
{
    Valoraciones valoraciones;
    Resultado res;
    unsigned pos, neg, neu;
    string palabra;
    Valoracion valoracion_aux;

    valoraciones.cargarPalabrasPositivas(FIC_PALABRAS_POSITIVAS, res);
    assert(res == OK);
    valoraciones.cargarPalabrasNegativas(FIC_PALABRAS_NEGATIVAS, res);
    assert(res == OK);
    valoraciones.numeroPalabras(pos, neg);
    assert(pos == 2006);
    assert(neg == 4783);

    valoraciones.cargarValoraciones(FIC_VALORACIONES, res);
    assert(res == OK);
    valoraciones.numeroValoraciones(pos, neg, neu);
    assert(pos == 8);
    assert(neg == 3);
    assert(neu == 0);

    // Comprobamos las valoraciones cargadas
    valoraciones.__consultar_elemento_pos(0, true, true, valoracion_aux, palabra);
    assert((valoracion_aux == Valoracion{42808, 85246, "2010-08-26", 45732, "Cassi", "Nina is truly a wonderful hostess. The room was very cozy and her apartment is lovely and perfectly located in a great neighborhood with lots of restaurants and cafes. There are two grocery stores within walking distance. It is also super close to the subway station, making it a breeze to get there from the airport and to get into city center.  Nina was  was not only very helpful and responsive, but tremendously pleasant and welcoming. When I arrived she had prepared a welcome kit with information about local attractions, maps of the city, and even a lonely planet guide. She even arranged for me to attend yoga class with her, which was fantastic! ", positivo}));
    valoraciones.__consultar_elemento_pos(1, true, false, valoracion_aux, palabra);
    assert((valoracion_aux == Valoracion{42808, 87545, "2010-08-30", 212295, "Eva", "  Nina is the worst person, and her apartment is the worst and most ugly we have ever stayed. The room was dirty and everythin was a mess. ", negativo}));
    valoraciones.__consultar_elemento_pos(2, true, true, valoracion_aux, palabra);
    assert((valoracion_aux == Valoracion{42808, 90227, "2010-09-04", 16461, "Dafne", "Nina's place is very nice, clean and very close to what's important, i.e. shops, restaurants and subway station. What really makes a difference is Nina herself, not only an extremely caring host, but also a splendid person. If at the end of your stay you leave as friends, that is a lot more than you thought you'd get from your trip to Stockholm. ", positivo}));
    valoraciones.__consultar_elemento_pos(3, true, true, valoracion_aux, palabra);
    assert((valoracion_aux == Valoracion{338470, 989514, "2012-03-11", 45732, "Cassi", "This place was great! Perfect for anyone who likes art. Very close to metro, 10-minute walk to trendy / hip restaurants and bars area. Gustaf is a very nice and charming host. He gave us handpicked guide and made some useful notes. I will definitely recommend this place to my friends!", positivo}));
    valoraciones.__consultar_elemento_pos(4, true, true, valoracion_aux, palabra);
    assert((valoracion_aux == Valoracion{145320, 156423122, "2017-05-30", 45732, "Cassi", "Very nice and wonderful place, everything was ok, clean and nice. We love this apartment. The best we have stayed ever!", positivo}));
    valoraciones.__consultar_elemento_pos(5, true, true, valoracion_aux, palabra);
    assert((valoracion_aux == Valoracion{145320, 170211906, "2017-07-15", 212295, "Eva", "  Horrible place, even worse than Nina's one. We made the wrong decision when hired this apartment! ", negativo}));
    valoraciones.__consultar_elemento_pos(6, true, true, valoracion_aux, palabra);
    assert((valoracion_aux == Valoracion{220851, 404219448, "2019-01-23", 6616639, "Eliska", "What a gem! Both the place and Fredric are just lovely. Had the best stay and felt like home. The location and value are amazing. Really cool place with an extra arty and soul touch  Will be back soon and defo booking the same place! ", positivo}));
    valoraciones.__consultar_elemento_pos(7, true, true, valoracion_aux, palabra);
    assert((valoracion_aux == Valoracion{220851, 411097466, "2019-02-11", 45732, "Cassi", "A lovely place to stay managed by a perfect guest", positivo}));
    valoraciones.__consultar_elemento_pos(8, true, true, valoracion_aux, palabra);
    assert((valoracion_aux == Valoracion{313763, 418091157, "2019-03-01", 212295, "Eva", "I am tired of telling always the same, but all the apartment that I hire are horrible. Ia have always very bad luck. I believe I am not goint to travel any more. Horrible experiences always!", negativo}));
    valoraciones.__consultar_elemento_pos(9, true, true, valoracion_aux, palabra);
    assert((valoracion_aux == Valoracion{313763, 430805847, "2019-03-31", 30497368, "Emma", "Martin was a fantastic host!", positivo}));
    valoraciones.__consultar_elemento_pos(10, true, true, valoracion_aux, palabra);
    assert((valoracion_aux == Valoracion{313763, 449750278, "2019-05-07", 255803528, "Matthias", "Martin was a very helpful host. The room in his classy appartment was the perfect homebase for my city exploration trip.", positivo}));

    // Si intento volver a cargar, no se añade nada (ya existen todas las valoraciones)
    valoraciones.cargarValoraciones(FIC_VALORACIONES, res);
    assert(res == OK);
    valoraciones.numeroValoraciones(pos, neg, neu);
    assert(pos == 8);
    assert(neg == 3);
    assert(neu == 0);

    // Comprobamos las valoraciones cargadas
    valoraciones.__consultar_elemento_pos(0, true, true, valoracion_aux, palabra);
    assert((valoracion_aux == Valoracion{42808, 85246, "2010-08-26", 45732, "Cassi", "Nina is truly a wonderful hostess. The room was very cozy and her apartment is lovely and perfectly located in a great neighborhood with lots of restaurants and cafes. There are two grocery stores within walking distance. It is also super close to the subway station, making it a breeze to get there from the airport and to get into city center.  Nina was  was not only very helpful and responsive, but tremendously pleasant and welcoming. When I arrived she had prepared a welcome kit with information about local attractions, maps of the city, and even a lonely planet guide. She even arranged for me to attend yoga class with her, which was fantastic! ", positivo}));
    valoraciones.__consultar_elemento_pos(1, true, false, valoracion_aux, palabra);
    assert((valoracion_aux == Valoracion{42808, 87545, "2010-08-30", 212295, "Eva", "  Nina is the worst person, and her apartment is the worst and most ugly we have ever stayed. The room was dirty and everythin was a mess. ", negativo}));
    valoraciones.__consultar_elemento_pos(2, true, true, valoracion_aux, palabra);
    assert((valoracion_aux == Valoracion{42808, 90227, "2010-09-04", 16461, "Dafne", "Nina's place is very nice, clean and very close to what's important, i.e. shops, restaurants and subway station. What really makes a difference is Nina herself, not only an extremely caring host, but also a splendid person. If at the end of your stay you leave as friends, that is a lot more than you thought you'd get from your trip to Stockholm. ", positivo}));
    valoraciones.__consultar_elemento_pos(3, true, true, valoracion_aux, palabra);
    assert((valoracion_aux == Valoracion{338470, 989514, "2012-03-11", 45732, "Cassi", "This place was great! Perfect for anyone who likes art. Very close to metro, 10-minute walk to trendy / hip restaurants and bars area. Gustaf is a very nice and charming host. He gave us handpicked guide and made some useful notes. I will definitely recommend this place to my friends!", positivo}));
    valoraciones.__consultar_elemento_pos(4, true, true, valoracion_aux, palabra);
    assert((valoracion_aux == Valoracion{145320, 156423122, "2017-05-30", 45732, "Cassi", "Very nice and wonderful place, everything was ok, clean and nice. We love this apartment. The best we have stayed ever!", positivo}));
    valoraciones.__consultar_elemento_pos(5, true, true, valoracion_aux, palabra);
    assert((valoracion_aux == Valoracion{145320, 170211906, "2017-07-15", 212295, "Eva", "  Horrible place, even worse than Nina's one. We made the wrong decision when hired this apartment! ", negativo}));
    valoraciones.__consultar_elemento_pos(6, true, true, valoracion_aux, palabra);
    assert((valoracion_aux == Valoracion{220851, 404219448, "2019-01-23", 6616639, "Eliska", "What a gem! Both the place and Fredric are just lovely. Had the best stay and felt like home. The location and value are amazing. Really cool place with an extra arty and soul touch  Will be back soon and defo booking the same place! ", positivo}));
    valoraciones.__consultar_elemento_pos(7, true, true, valoracion_aux, palabra);
    assert((valoracion_aux == Valoracion{220851, 411097466, "2019-02-11", 45732, "Cassi", "A lovely place to stay managed by a perfect guest", positivo}));
    valoraciones.__consultar_elemento_pos(8, true, true, valoracion_aux, palabra);
    assert((valoracion_aux == Valoracion{313763, 418091157, "2019-03-01", 212295, "Eva", "I am tired of telling always the same, but all the apartment that I hire are horrible. Ia have always very bad luck. I believe I am not goint to travel any more. Horrible experiences always!", negativo}));
    valoraciones.__consultar_elemento_pos(9, true, true, valoracion_aux, palabra);
    assert((valoracion_aux == Valoracion{313763, 430805847, "2019-03-31", 30497368, "Emma", "Martin was a fantastic host!", positivo}));
    valoraciones.__consultar_elemento_pos(10, true, true, valoracion_aux, palabra);
    assert((valoracion_aux == Valoracion{313763, 449750278, "2019-05-07", 255803528, "Matthias", "Martin was a very helpful host. The room in his classy appartment was the perfect homebase for my city exploration trip.", positivo}));
}

void test_guardar_valoraciones()
{
    Valoraciones valoraciones;
    Resultado res;
    unsigned pos, neg, neu;
    string palabra;
    Valoracion valoracion_aux;

    valoraciones.cargarPalabrasPositivas(FIC_PALABRAS_POSITIVAS, res);
    assert(res == OK);
    valoraciones.cargarPalabrasNegativas(FIC_PALABRAS_NEGATIVAS, res);
    assert(res == OK);
    valoraciones.numeroPalabras(pos, neg);
    assert(pos == 2006);
    assert(neg == 4783);

    valoraciones.cargarValoraciones(FIC_VALORACIONES, res);
    assert(res == OK);
    valoraciones.numeroValoraciones(pos, neg, neu);
    assert(pos == 8);
    assert(neg == 3);
    assert(neu == 0);

    // Guardamos en fichero
    valoraciones.guardarValoraciones("_valoraciones_test_copia_orden.csv", res);
    assert(res == OK);

    Valoraciones aux;
    aux.cargarPalabrasPositivas(FIC_PALABRAS_POSITIVAS, res);
    assert(res == OK);
    aux.cargarPalabrasNegativas(FIC_PALABRAS_NEGATIVAS, res);
    assert(res == OK);
    aux.numeroPalabras(pos, neg);
    assert(pos == 2006);
    assert(neg == 4783);
    aux.cargarValoraciones("_valoraciones_test_copia_orden.csv", res);
    assert(res == OK);
    aux.numeroValoraciones(pos, neg, neu);
    assert(pos == 8);
    assert(neg == 3);
    assert(neu == 0);

    assert(aux == valoraciones);
}

// Prueba de actualizarSentimiento
void test_actualizar_sentimiento()
{
    Valoraciones valoraciones;
    Resultado res;

    valoraciones.cargarPalabrasPositivas(FIC_PALABRAS_POSITIVAS, res);
    valoraciones.cargarPalabrasNegativas(FIC_PALABRAS_NEGATIVAS, res);
    valoraciones.cargarValoraciones(FIC_VALORACIONES, res);

    // Comprobamos las valoraciones cargadas
    Valoracion valoracion_aux;
    string palabra;
    valoraciones.__consultar_elemento_pos(0, true, true, valoracion_aux, palabra);
    assert((valoracion_aux == Valoracion{42808, 85246, "2010-08-26", 45732, "Cassi", "Nina is truly a wonderful hostess. The room was very cozy and her apartment is lovely and perfectly located in a great neighborhood with lots of restaurants and cafes. There are two grocery stores within walking distance. It is also super close to the subway station, making it a breeze to get there from the airport and to get into city center.  Nina was  was not only very helpful and responsive, but tremendously pleasant and welcoming. When I arrived she had prepared a welcome kit with information about local attractions, maps of the city, and even a lonely planet guide. She even arranged for me to attend yoga class with her, which was fantastic! ", positivo}));
    valoraciones.__consultar_elemento_pos(1, true, false, valoracion_aux, palabra);
    assert((valoracion_aux == Valoracion{42808, 87545, "2010-08-30", 212295, "Eva", "  Nina is the worst person, and her apartment is the worst and most ugly we have ever stayed. The room was dirty and everythin was a mess. ", negativo}));
    valoraciones.__consultar_elemento_pos(2, true, true, valoracion_aux, palabra);
    assert((valoracion_aux == Valoracion{42808, 90227, "2010-09-04", 16461, "Dafne", "Nina's place is very nice, clean and very close to what's important, i.e. shops, restaurants and subway station. What really makes a difference is Nina herself, not only an extremely caring host, but also a splendid person. If at the end of your stay you leave as friends, that is a lot more than you thought you'd get from your trip to Stockholm. ", positivo}));
    valoraciones.__consultar_elemento_pos(3, true, true, valoracion_aux, palabra);
    assert((valoracion_aux == Valoracion{338470, 989514, "2012-03-11", 45732, "Cassi", "This place was great! Perfect for anyone who likes art. Very close to metro, 10-minute walk to trendy / hip restaurants and bars area. Gustaf is a very nice and charming host. He gave us handpicked guide and made some useful notes. I will definitely recommend this place to my friends!", positivo}));
    valoraciones.__consultar_elemento_pos(4, true, true, valoracion_aux, palabra);
    assert((valoracion_aux == Valoracion{145320, 156423122, "2017-05-30", 45732, "Cassi", "Very nice and wonderful place, everything was ok, clean and nice. We love this apartment. The best we have stayed ever!", positivo}));
    valoraciones.__consultar_elemento_pos(5, true, true, valoracion_aux, palabra);
    assert((valoracion_aux == Valoracion{145320, 170211906, "2017-07-15", 212295, "Eva", "  Horrible place, even worse than Nina's one. We made the wrong decision when hired this apartment! ", negativo}));
    valoraciones.__consultar_elemento_pos(6, true, true, valoracion_aux, palabra);
    assert((valoracion_aux == Valoracion{220851, 404219448, "2019-01-23", 6616639, "Eliska", "What a gem! Both the place and Fredric are just lovely. Had the best stay and felt like home. The location and value are amazing. Really cool place with an extra arty and soul touch  Will be back soon and defo booking the same place! ", positivo}));
    valoraciones.__consultar_elemento_pos(7, true, true, valoracion_aux, palabra);
    assert((valoracion_aux == Valoracion{220851, 411097466, "2019-02-11", 45732, "Cassi", "A lovely place to stay managed by a perfect guest", positivo}));
    valoraciones.__consultar_elemento_pos(8, true, true, valoracion_aux, palabra);
    assert((valoracion_aux == Valoracion{313763, 418091157, "2019-03-01", 212295, "Eva", "I am tired of telling always the same, but all the apartment that I hire are horrible. Ia have always very bad luck. I believe I am not goint to travel any more. Horrible experiences always!", negativo}));
    valoraciones.__consultar_elemento_pos(9, true, true, valoracion_aux, palabra);
    assert((valoracion_aux == Valoracion{313763, 430805847, "2019-03-31", 30497368, "Emma", "Martin was a fantastic host!", positivo}));
    valoraciones.__consultar_elemento_pos(10, true, true, valoracion_aux, palabra);
    assert((valoracion_aux == Valoracion{313763, 449750278, "2019-05-07", 255803528, "Matthias", "Martin was a very helpful host. The room in his classy appartment was the perfect homebase for my city exploration trip.", positivo}));

    // Ahora modificamos sentimiento de algunas valoraciones
    valoraciones.actualizarSentimiento(87545, 5, res);
    assert(res == OK);
    valoraciones.__consultar_elemento_pos(1, true, false, valoracion_aux, palabra);
    assert((valoracion_aux == Valoracion{42808, 87545, "2010-08-30", 212295, "Eva", "  Nina is the worst person, and her apartment is the worst and most ugly we have ever stayed. The room was dirty and everythin was a mess. ", neutro}));
    valoraciones.actualizarSentimiento(430805847, 5, res);
    assert(res == OK);
    valoraciones.__consultar_elemento_pos(9, true, true, valoracion_aux, palabra);
    assert((valoracion_aux == Valoracion{313763, 430805847, "2019-03-31", 30497368, "Emma", "Martin was a fantastic host!", neutro}));
    valoraciones.actualizarSentimiento(449750278, 5, res);
    assert(res == OK);
    valoraciones.__consultar_elemento_pos(10, true, true, valoracion_aux, palabra);
    assert((valoracion_aux == Valoracion{313763, 449750278, "2019-05-07", 255803528, "Matthias", "Martin was a very helpful host. The room in his classy appartment was the perfect homebase for my city exploration trip.", neutro}));
    valoraciones.actualizarSentimiento(555555, 5, res);
    assert(res == NO_EXISTE);

    // El resto debe seguir igual
    valoraciones.__consultar_elemento_pos(0, true, true, valoracion_aux, palabra);
    assert((valoracion_aux == Valoracion{42808, 85246, "2010-08-26", 45732, "Cassi", "Nina is truly a wonderful hostess. The room was very cozy and her apartment is lovely and perfectly located in a great neighborhood with lots of restaurants and cafes. There are two grocery stores within walking distance. It is also super close to the subway station, making it a breeze to get there from the airport and to get into city center.  Nina was  was not only very helpful and responsive, but tremendously pleasant and welcoming. When I arrived she had prepared a welcome kit with information about local attractions, maps of the city, and even a lonely planet guide. She even arranged for me to attend yoga class with her, which was fantastic! ", positivo}));
    valoraciones.__consultar_elemento_pos(2, true, true, valoracion_aux, palabra);
    assert((valoracion_aux == Valoracion{42808, 90227, "2010-09-04", 16461, "Dafne", "Nina's place is very nice, clean and very close to what's important, i.e. shops, restaurants and subway station. What really makes a difference is Nina herself, not only an extremely caring host, but also a splendid person. If at the end of your stay you leave as friends, that is a lot more than you thought you'd get from your trip to Stockholm. ", positivo}));
    valoraciones.__consultar_elemento_pos(3, true, true, valoracion_aux, palabra);
    assert((valoracion_aux == Valoracion{338470, 989514, "2012-03-11", 45732, "Cassi", "This place was great! Perfect for anyone who likes art. Very close to metro, 10-minute walk to trendy / hip restaurants and bars area. Gustaf is a very nice and charming host. He gave us handpicked guide and made some useful notes. I will definitely recommend this place to my friends!", positivo}));
    valoraciones.__consultar_elemento_pos(4, true, true, valoracion_aux, palabra);
    assert((valoracion_aux == Valoracion{145320, 156423122, "2017-05-30", 45732, "Cassi", "Very nice and wonderful place, everything was ok, clean and nice. We love this apartment. The best we have stayed ever!", positivo}));
    valoraciones.__consultar_elemento_pos(5, true, true, valoracion_aux, palabra);
    assert((valoracion_aux == Valoracion{145320, 170211906, "2017-07-15", 212295, "Eva", "  Horrible place, even worse than Nina's one. We made the wrong decision when hired this apartment! ", negativo}));
    valoraciones.__consultar_elemento_pos(6, true, true, valoracion_aux, palabra);
    assert((valoracion_aux == Valoracion{220851, 404219448, "2019-01-23", 6616639, "Eliska", "What a gem! Both the place and Fredric are just lovely. Had the best stay and felt like home. The location and value are amazing. Really cool place with an extra arty and soul touch  Will be back soon and defo booking the same place! ", positivo}));
    valoraciones.__consultar_elemento_pos(7, true, true, valoracion_aux, palabra);
    assert((valoracion_aux == Valoracion{220851, 411097466, "2019-02-11", 45732, "Cassi", "A lovely place to stay managed by a perfect guest", positivo}));
    valoraciones.__consultar_elemento_pos(8, true, true, valoracion_aux, palabra);
    assert((valoracion_aux == Valoracion{313763, 418091157, "2019-03-01", 212295, "Eva", "I am tired of telling always the same, but all the apartment that I hire are horrible. Ia have always very bad luck. I believe I am not goint to travel any more. Horrible experiences always!", negativo}));
}

// Prueba de actualizarSentimientos
void test_actualizar_sentimientos()
{
    Valoraciones valoraciones;
    Resultado res;
    unsigned pos, neg, neu;

    valoraciones.cargarPalabrasPositivas(FIC_PALABRAS_POSITIVAS, res);
    valoraciones.cargarPalabrasNegativas(FIC_PALABRAS_NEGATIVAS, res);
    valoraciones.cargarValoraciones(FIC_VALORACIONES, res);

    valoraciones.actualizarSentimientos(1);
    valoraciones.numeroValoraciones(pos, neg, neu);
    assert(pos == 7 && neg == 3 && neu == 1);

    valoraciones.actualizarSentimientos(2);
    valoraciones.numeroValoraciones(pos, neg, neu);
    assert(pos == 6 && neg == 3 && neu == 2);

    valoraciones.actualizarSentimientos(3);
    valoraciones.numeroValoraciones(pos, neg, neu);
    assert(pos == 5 && neg == 1 && neu == 5);

    valoraciones.actualizarSentimientos(4);
    valoraciones.numeroValoraciones(pos, neg, neu);
    assert(pos == 4 && neg == 1 && neu == 6);

    valoraciones.actualizarSentimientos(5);
    valoraciones.numeroValoraciones(pos, neg, neu);
    assert(pos == 4 && neg == 0 && neu == 7);

    // Comprobamos las valoraciones cargadas
    Valoracion valoracion_aux;
    string palabra;
    valoraciones.__consultar_elemento_pos(0, true, true, valoracion_aux, palabra);
    assert((valoracion_aux == Valoracion{42808, 85246, "2010-08-26", 45732, "Cassi", "Nina is truly a wonderful hostess. The room was very cozy and her apartment is lovely and perfectly located in a great neighborhood with lots of restaurants and cafes. There are two grocery stores within walking distance. It is also super close to the subway station, making it a breeze to get there from the airport and to get into city center.  Nina was  was not only very helpful and responsive, but tremendously pleasant and welcoming. When I arrived she had prepared a welcome kit with information about local attractions, maps of the city, and even a lonely planet guide. She even arranged for me to attend yoga class with her, which was fantastic! ", positivo}));
    valoraciones.__consultar_elemento_pos(1, true, false, valoracion_aux, palabra);
    assert((valoracion_aux == Valoracion{42808, 87545, "2010-08-30", 212295, "Eva", "  Nina is the worst person, and her apartment is the worst and most ugly we have ever stayed. The room was dirty and everythin was a mess. ", neutro}));
    valoraciones.__consultar_elemento_pos(2, true, true, valoracion_aux, palabra);
    assert((valoracion_aux == Valoracion{42808, 90227, "2010-09-04", 16461, "Dafne", "Nina's place is very nice, clean and very close to what's important, i.e. shops, restaurants and subway station. What really makes a difference is Nina herself, not only an extremely caring host, but also a splendid person. If at the end of your stay you leave as friends, that is a lot more than you thought you'd get from your trip to Stockholm. ", neutro}));
    valoraciones.__consultar_elemento_pos(3, true, true, valoracion_aux, palabra);
    assert((valoracion_aux == Valoracion{338470, 989514, "2012-03-11", 45732, "Cassi", "This place was great! Perfect for anyone who likes art. Very close to metro, 10-minute walk to trendy / hip restaurants and bars area. Gustaf is a very nice and charming host. He gave us handpicked guide and made some useful notes. I will definitely recommend this place to my friends!", positivo}));
    valoraciones.__consultar_elemento_pos(4, true, true, valoracion_aux, palabra);
    assert((valoracion_aux == Valoracion{145320, 156423122, "2017-05-30", 45732, "Cassi", "Very nice and wonderful place, everything was ok, clean and nice. We love this apartment. The best we have stayed ever!", positivo}));
    valoraciones.__consultar_elemento_pos(5, true, true, valoracion_aux, palabra);
    assert((valoracion_aux == Valoracion{145320, 170211906, "2017-07-15", 212295, "Eva", "  Horrible place, even worse than Nina's one. We made the wrong decision when hired this apartment! ", neutro}));
    valoraciones.__consultar_elemento_pos(6, true, true, valoracion_aux, palabra);
    assert((valoracion_aux == Valoracion{220851, 404219448, "2019-01-23", 6616639, "Eliska", "What a gem! Both the place and Fredric are just lovely. Had the best stay and felt like home. The location and value are amazing. Really cool place with an extra arty and soul touch  Will be back soon and defo booking the same place! ", positivo}));
    valoraciones.__consultar_elemento_pos(7, true, true, valoracion_aux, palabra);
    assert((valoracion_aux == Valoracion{220851, 411097466, "2019-02-11", 45732, "Cassi", "A lovely place to stay managed by a perfect guest", neutro}));
    valoraciones.__consultar_elemento_pos(8, true, true, valoracion_aux, palabra);
    assert((valoracion_aux == Valoracion{313763, 418091157, "2019-03-01", 212295, "Eva", "I am tired of telling always the same, but all the apartment that I hire are horrible. Ia have always very bad luck. I believe I am not goint to travel any more. Horrible experiences always!", neutro}));
    valoraciones.__consultar_elemento_pos(9, true, true, valoracion_aux, palabra);
    assert((valoracion_aux == Valoracion{313763, 430805847, "2019-03-31", 30497368, "Emma", "Martin was a fantastic host!", neutro}));
    valoraciones.__consultar_elemento_pos(10, true, true, valoracion_aux, palabra);
    assert((valoracion_aux == Valoracion{313763, 449750278, "2019-05-07", 255803528, "Matthias", "Martin was a very helpful host. The room in his classy appartment was the perfect homebase for my city exploration trip.", neutro}));
}

// Prueba de numeroValoraciones
void test_numero_valoraciones()
{
    Valoraciones valoraciones;
    Resultado res;
    unsigned pos, neg, neu;

    valoraciones.cargarPalabrasPositivas(FIC_PALABRAS_POSITIVAS, res);
    assert(res == OK);
    valoraciones.cargarPalabrasNegativas(FIC_PALABRAS_NEGATIVAS, res);
    assert(res == OK);

    valoraciones.cargarValoraciones(FIC_VALORACIONES, res);
    assert(res == OK);
    valoraciones.numeroValoraciones(pos, neg, neu);
    assert(pos == 8);
    assert(neg == 3);
    assert(neu == 0);
}

// Prueba de listaValoraciones
void test_lista_valoraciones()
{
    Valoraciones valoraciones;
    Resultado res;
    unsigned pos, neg, neu;

    valoraciones.cargarPalabrasPositivas(FIC_PALABRAS_POSITIVAS, res);
    assert(res == OK);
    valoraciones.cargarPalabrasNegativas(FIC_PALABRAS_NEGATIVAS, res);
    assert(res == OK);

    valoraciones.cargarValoraciones(FIC_VALORACIONES, res);
    assert(res == OK);
    valoraciones.numeroValoraciones(pos, neg, neu);
    assert(pos == 8);
    assert(neg == 3);
    assert(neu == 0);

    Ids ids_positivas, ids_negativas, ids_neutras;
    valoraciones.listaValoraciones(ids_positivas, ids_negativas, ids_neutras);
    assert(ids_positivas.num_ids == 8);
    assert(ids_negativas.num_ids == 3);
    assert(ids_neutras.num_ids == 0);
    assert(ids_positivas.ids[0] == 85246);
    assert(ids_positivas.ids[7] == 449750278);
    assert(ids_negativas.ids[0] == 87545);
    assert(ids_negativas.ids[2] == 418091157);
}

// Prueba de numeroPalabras
void test_numero_palabras()
{
    Valoraciones valoraciones;
    Resultado res;
    unsigned pos, neg;

    valoraciones.cargarPalabrasPositivas(FIC_PALABRAS_POSITIVAS, res);
    assert(res == OK);
    valoraciones.cargarPalabrasNegativas(FIC_PALABRAS_NEGATIVAS, res);
    assert(res == OK);
    valoraciones.numeroPalabras(pos, neg);
    assert(pos == 2006);
    assert(neg == 4783);
}

// Prueba de buscarValoracion
void test_buscar_valoracion()
{
    Valoraciones valoraciones;
    Resultado res;
    unsigned pos, neg, neu;
    Valoracion valoracion_aux;
    bool encontrada;

    valoraciones.cargarPalabrasPositivas(FIC_PALABRAS_POSITIVAS, res);
    assert(res == OK);
    valoraciones.cargarPalabrasNegativas(FIC_PALABRAS_NEGATIVAS, res);
    assert(res == OK);
    valoraciones.numeroPalabras(pos, neg);
    assert(pos == 2006);
    assert(neg == 4783);
    valoraciones.insertarValoracion(Valoracion{42808, 85246, "2010-08-26", 45732, "Cassi", "Nina is truly a wonderful hostess. The room was very cozy and her apartment is lovely and perfectly located in a great neighborhood with lots of restaurants and cafes. There are two grocery stores within walking distance. It is also super close to the subway station, making it a breeze to get there from the airport and to get into city center.  Nina was  was not only very helpful and responsive, but tremendously pleasant and welcoming. When I arrived she had prepared a welcome kit with information about local attractions, maps of the city, and even a lonely planet guide. She even arranged for me to attend yoga class with her, which was fantastic! ", positivo}, res);
    assert(res == OK);
    valoraciones.insertarValoracion(Valoracion{145320, 156423122, "2017-05-30", 45732, "Cassi", "Very nice and wonderful place, everything was ok, clean and nice. We love this apartment. The best we have stayed ever!", positivo}, res);
    assert(res == OK);
    valoraciones.insertarValoracion(Valoracion{313763, 449750278, "2019-05-07", 255803528, "Matthias", "Martin was a very helpful host. The room in his classy appartment was the perfect homebase for my city exploration trip.", positivo}, res);
    assert(res == OK);
    valoraciones.insertarValoracion(Valoracion{42808, 87545, "2010-08-30", 212295, "Eva", "  Nina is the worst person, and her apartment is the worst and most ugly we have ever stayed. The room was dirty and everythin was a mess. ", negativo}, res);
    assert(res == OK);
    valoraciones.insertarValoracion(Valoracion{313763, 418091157, "2019-03-01", 212295, "Eva", "I am tired of telling always the same but all the apartment that I hire are horrible. Ia have always very bad luck. I believe I am not goint to travel any more. Horrible experiences always!", negativo}, res);
    assert(res == OK);
    valoraciones.numeroValoraciones(pos, neg, neu);
    assert(pos == 3);
    assert(neg == 2);
    assert(neu == 0);

    // Buscamos valoraciones
    valoraciones.buscarValoracion(85246, valoracion_aux, encontrada);
    assert((valoracion_aux == Valoracion{42808, 85246, "2010-08-26", 45732, "Cassi", "Nina is truly a wonderful hostess. The room was very cozy and her apartment is lovely and perfectly located in a great neighborhood with lots of restaurants and cafes. There are two grocery stores within walking distance. It is also super close to the subway station, making it a breeze to get there from the airport and to get into city center.  Nina was  was not only very helpful and responsive, but tremendously pleasant and welcoming. When I arrived she had prepared a welcome kit with information about local attractions, maps of the city, and even a lonely planet guide. She even arranged for me to attend yoga class with her, which was fantastic! ", positivo}));
    assert(encontrada);

    valoraciones.buscarValoracion(156423122, valoracion_aux, encontrada);
    assert((valoracion_aux == Valoracion{145320, 156423122, "2017-05-30", 45732, "Cassi", "Very nice and wonderful place, everything was ok, clean and nice. We love this apartment. The best we have stayed ever!", positivo}));
    assert(encontrada);

    valoraciones.buscarValoracion(449750278, valoracion_aux, encontrada);
    assert((valoracion_aux == Valoracion{313763, 449750278, "2019-05-07", 255803528, "Matthias", "Martin was a very helpful host. The room in his classy appartment was the perfect homebase for my city exploration trip.", positivo}));
    assert(encontrada);

    valoraciones.buscarValoracion(87545, valoracion_aux, encontrada);
    assert((valoracion_aux == Valoracion{42808, 87545, "2010-08-30", 212295, "Eva", "  Nina is the worst person, and her apartment is the worst and most ugly we have ever stayed. The room was dirty and everythin was a mess. ", negativo}));
    assert(encontrada);

    valoraciones.buscarValoracion(418091157, valoracion_aux, encontrada);
    assert((valoracion_aux == Valoracion{313763, 418091157, "2019-03-01", 212295, "Eva", "I am tired of telling always the same but all the apartment that I hire are horrible. Ia have always very bad luck. I believe I am not goint to travel any more. Horrible experiences always!", negativo}));
    assert(encontrada);

    valoraciones.buscarValoracion(5555555, valoracion_aux, encontrada);
    assert(!encontrada);
}

// Prueba de insertarValoracion
void test_insertar_valoracion()
{
    Valoraciones valoraciones;
    Palabras pal_pos, pal_neg;
    Sentimiento sent;
    Resultado res;
    unsigned pos, neg, neu;
    string palabra;
    Valoracion valoracion_aux;

    valoraciones.cargarPalabrasPositivas(FIC_PALABRAS_POSITIVAS, res);
    assert(res == OK);
    valoraciones.cargarPalabrasNegativas(FIC_PALABRAS_NEGATIVAS, res);
    assert(res == OK);
    valoraciones.numeroPalabras(pos, neg);
    assert(pos == 2006);
    assert(neg == 4783);

    pal_pos.leerPalabras(FIC_PALABRAS_POSITIVAS, res);
    assert(pal_pos.numPalabras() == 2006);
    assert(res == OK);
    pal_neg.leerPalabras(FIC_PALABRAS_NEGATIVAS, res);
    assert(pal_neg.numPalabras() == 4783);
    assert(res == OK);

    Valoracion valoracion = Valoracion{145320, 156423122, "2017-05-30", 45732, "Cassi", "Very nice and wonderful place, everything was ok, clean and nice. We love this apartment. The best we have stayed ever!", neutro};
    valoracion.analizarSentimiento(pal_pos, pal_neg, 0, sent);
    valoracion.asignarSentimiento(sent);
    valoraciones.insertarValoracion(valoracion, res);
    assert(res == OK);
    valoraciones.numeroValoraciones(pos, neg, neu);
    assert(pos == 1);
    assert(neg == 0);
    assert(neu == 0);
    valoraciones.__consultar_elemento_pos(0, true, true, valoracion_aux, palabra);
    assert((valoracion_aux == Valoracion{145320, 156423122, "2017-05-30", 45732, "Cassi", "Very nice and wonderful place, everything was ok, clean and nice. We love this apartment. The best we have stayed ever!", positivo}));

    valoracion = Valoracion{313763, 418091157, "2019-03-01", 212295, "Eva", "I am tired of telling always the same but all the apartment that I hire are horrible. Ia have always very bad luck. I believe I am not goint to travel any more. Horrible experiences always!", neutro};
    valoracion.analizarSentimiento(pal_pos, pal_neg, 0, sent);
    valoracion.asignarSentimiento(sent);
    valoraciones.insertarValoracion(valoracion, res);
    assert(res == OK);
    valoraciones.numeroValoraciones(pos, neg, neu);
    assert(pos == 1);
    assert(neg == 1);
    assert(neu == 0);
    valoraciones.__consultar_elemento_pos(0, true, true, valoracion_aux, palabra);
    assert((valoracion_aux == Valoracion{145320, 156423122, "2017-05-30", 45732, "Cassi", "Very nice and wonderful place, everything was ok, clean and nice. We love this apartment. The best we have stayed ever!", positivo}));
    valoraciones.__consultar_elemento_pos(1, true, true, valoracion_aux, palabra);
    assert((valoracion_aux == Valoracion{313763, 418091157, "2019-03-01", 212295, "Eva", "I am tired of telling always the same but all the apartment that I hire are horrible. Ia have always very bad luck. I believe I am not goint to travel any more. Horrible experiences always!", negativo}));

    valoracion = Valoracion{42808, 85246, "2010-08-26", 45732, "Cassi", "Nina is truly a wonderful hostess. The room was very cozy and her apartment is lovely and perfectly located in a great neighborhood with lots of restaurants and cafes. There are two grocery stores within walking distance. It is also super close to the subway station, making it a breeze to get there from the airport and to get into city center.  Nina was  was not only very helpful and responsive, but tremendously pleasant and welcoming. When I arrived she had prepared a welcome kit with information about local attractions, maps of the city, and even a lonely planet guide. She even arranged for me to attend yoga class with her, which was fantastic! ", neutro};
    valoracion.analizarSentimiento(pal_pos, pal_neg, 0, sent);
    valoracion.asignarSentimiento(sent);
    valoraciones.insertarValoracion(valoracion, res);
    assert(res == OK);
    valoraciones.numeroValoraciones(pos, neg, neu);
    assert(pos == 2);
    assert(neg == 1);
    assert(neu == 0);
    valoraciones.__consultar_elemento_pos(0, true, true, valoracion_aux, palabra);
    assert((valoracion_aux == Valoracion{42808, 85246, "2010-08-26", 45732, "Cassi", "Nina is truly a wonderful hostess. The room was very cozy and her apartment is lovely and perfectly located in a great neighborhood with lots of restaurants and cafes. There are two grocery stores within walking distance. It is also super close to the subway station, making it a breeze to get there from the airport and to get into city center.  Nina was  was not only very helpful and responsive, but tremendously pleasant and welcoming. When I arrived she had prepared a welcome kit with information about local attractions, maps of the city, and even a lonely planet guide. She even arranged for me to attend yoga class with her, which was fantastic! ", positivo}));
    valoraciones.__consultar_elemento_pos(1, true, true, valoracion_aux, palabra);
    assert((valoracion_aux == Valoracion{145320, 156423122, "2017-05-30", 45732, "Cassi", "Very nice and wonderful place, everything was ok, clean and nice. We love this apartment. The best we have stayed ever!", positivo}));
    valoraciones.__consultar_elemento_pos(2, true, true, valoracion_aux, palabra);
    assert((valoracion_aux == Valoracion{313763, 418091157, "2019-03-01", 212295, "Eva", "I am tired of telling always the same but all the apartment that I hire are horrible. Ia have always very bad luck. I believe I am not goint to travel any more. Horrible experiences always!", negativo}));

    valoracion = Valoracion{313763, 449750278, "2019-05-07", 255803528, "Matthias", "Martin was a very helpful host. The room in his classy appartment was the perfect homebase for my city exploration trip.", neutro};
    valoracion.analizarSentimiento(pal_pos, pal_neg, 0, sent);
    valoracion.asignarSentimiento(sent);
    valoraciones.insertarValoracion(valoracion, res);
    assert(res == OK);
    valoraciones.numeroValoraciones(pos, neg, neu);
    assert(pos == 3);
    assert(neg == 1);
    assert(neu == 0);
    valoraciones.__consultar_elemento_pos(0, true, true, valoracion_aux, palabra);
    assert((valoracion_aux == Valoracion{42808, 85246, "2010-08-26", 45732, "Cassi", "Nina is truly a wonderful hostess. The room was very cozy and her apartment is lovely and perfectly located in a great neighborhood with lots of restaurants and cafes. There are two grocery stores within walking distance. It is also super close to the subway station, making it a breeze to get there from the airport and to get into city center.  Nina was  was not only very helpful and responsive, but tremendously pleasant and welcoming. When I arrived she had prepared a welcome kit with information about local attractions, maps of the city, and even a lonely planet guide. She even arranged for me to attend yoga class with her, which was fantastic! ", positivo}));
    valoraciones.__consultar_elemento_pos(1, true, true, valoracion_aux, palabra);
    assert((valoracion_aux == Valoracion{145320, 156423122, "2017-05-30", 45732, "Cassi", "Very nice and wonderful place, everything was ok, clean and nice. We love this apartment. The best we have stayed ever!", positivo}));
    valoraciones.__consultar_elemento_pos(2, true, true, valoracion_aux, palabra);
    assert((valoracion_aux == Valoracion{313763, 418091157, "2019-03-01", 212295, "Eva", "I am tired of telling always the same but all the apartment that I hire are horrible. Ia have always very bad luck. I believe I am not goint to travel any more. Horrible experiences always!", negativo}));
    valoraciones.__consultar_elemento_pos(3, true, true, valoracion_aux, palabra);
    assert((valoracion_aux == Valoracion{313763, 449750278, "2019-05-07", 255803528, "Matthias", "Martin was a very helpful host. The room in his classy appartment was the perfect homebase for my city exploration trip.", positivo}));

    valoracion = Valoracion{42808, 87545, "2010-08-30", 212295, "Eva", "  Nina is the worst person, and her apartment is the worst and most ugly we have ever stayed. The room was dirty and everythin was a mess. ", neutro};
    valoracion.analizarSentimiento(pal_pos, pal_neg, 0, sent);
    valoracion.asignarSentimiento(sent);
    valoraciones.insertarValoracion(valoracion, res);
    assert(res == OK);
    valoraciones.numeroValoraciones(pos, neg, neu);
    assert(pos == 3);
    assert(neg == 2);
    assert(neu == 0);
    valoraciones.__consultar_elemento_pos(0, true, true, valoracion_aux, palabra);
    assert((valoracion_aux == Valoracion{42808, 85246, "2010-08-26", 45732, "Cassi", "Nina is truly a wonderful hostess. The room was very cozy and her apartment is lovely and perfectly located in a great neighborhood with lots of restaurants and cafes. There are two grocery stores within walking distance. It is also super close to the subway station, making it a breeze to get there from the airport and to get into city center.  Nina was  was not only very helpful and responsive, but tremendously pleasant and welcoming. When I arrived she had prepared a welcome kit with information about local attractions, maps of the city, and even a lonely planet guide. She even arranged for me to attend yoga class with her, which was fantastic! ", positivo}));
    valoraciones.__consultar_elemento_pos(1, true, true, valoracion_aux, palabra);
    assert((valoracion_aux == Valoracion{42808, 87545, "2010-08-30", 212295, "Eva", "  Nina is the worst person, and her apartment is the worst and most ugly we have ever stayed. The room was dirty and everythin was a mess. ", negativo}));
    valoraciones.__consultar_elemento_pos(2, true, true, valoracion_aux, palabra);
    assert((valoracion_aux == Valoracion{145320, 156423122, "2017-05-30", 45732, "Cassi", "Very nice and wonderful place, everything was ok, clean and nice. We love this apartment. The best we have stayed ever!", positivo}));
    valoraciones.__consultar_elemento_pos(3, true, true, valoracion_aux, palabra);
    assert((valoracion_aux == Valoracion{313763, 418091157, "2019-03-01", 212295, "Eva", "I am tired of telling always the same but all the apartment that I hire are horrible. Ia have always very bad luck. I believe I am not goint to travel any more. Horrible experiences always!", negativo}));
    valoraciones.__consultar_elemento_pos(4, true, true, valoracion_aux, palabra);
    assert((valoracion_aux == Valoracion{313763, 449750278, "2019-05-07", 255803528, "Matthias", "Martin was a very helpful host. The room in his classy appartment was the perfect homebase for my city exploration trip.", positivo}));

    valoraciones.insertarValoracion(Valoracion{42808, 85246, "2010-08-26", 45732, "Cassi", "Nina is truly a wonderful hostess. The room was very cozy and her apartment is lovely and perfectly located in a great neighborhood with lots of restaurants and cafes. There are two grocery stores within walking distance. It is also super close to the subway station, making it a breeze to get there from the airport and to get into city center.  Nina was  was not only very helpful and responsive, but tremendously pleasant and welcoming. When I arrived she had prepared a welcome kit with information about local attractions, maps of the city, and even a lonely planet guide. She even arranged for me to attend yoga class with her, which was fantastic! ", positivo}, res);
    assert(res == YA_EXISTE);
    valoraciones.insertarValoracion(Valoracion{145320, 156423122, "2017-05-30", 45732, "Cassi", "Very nice and wonderful place, everything was ok, clean and nice. We love this apartment. The best we have stayed ever!", positivo}, res);
    assert(res == YA_EXISTE);
    valoraciones.insertarValoracion(Valoracion{313763, 449750278, "2019-05-07", 255803528, "Matthias", "Martin was a very helpful host. The room in his classy appartment was the perfect homebase for my city exploration trip.", positivo}, res);
    assert(res == YA_EXISTE);
    valoraciones.insertarValoracion(Valoracion{42808, 87545, "2010-08-30", 212295, "Eva", "  Nina is the worst person, and her apartment is the worst and most ugly we have ever stayed. The room was dirty and everythin was a mess. ", negativo}, res);
    assert(res == YA_EXISTE);
    valoraciones.insertarValoracion(Valoracion{313763, 418091157, "2019-03-01", 212295, "Eva", "I am tired of telling always the same but all the apartment that I hire are horrible. Ia have always very bad luck. I believe I am not goint to travel any more. Horrible experiences always!", negativo}, res);
    assert(res == YA_EXISTE);
    valoraciones.numeroValoraciones(pos, neg, neu);
    assert(pos == 3);
    assert(neg == 2);
    assert(neu == 0);
}

void test_eliminar_valoracion()
{
    Valoraciones valoraciones;
    Resultado res;
    unsigned pos, neg, neu;
    string palabra;
    Valoracion valoracion_aux;

    valoraciones.cargarPalabrasPositivas(FIC_PALABRAS_POSITIVAS, res);
    assert(res == OK);
    valoraciones.cargarPalabrasNegativas(FIC_PALABRAS_NEGATIVAS, res);
    assert(res == OK);
    valoraciones.numeroPalabras(pos, neg);
    assert(pos == 2006);
    assert(neg == 4783);

    valoraciones.cargarValoraciones(FIC_VALORACIONES, res);
    assert(res == OK);
    valoraciones.numeroValoraciones(pos, neg, neu);
    assert(pos == 8);
    assert(neg == 3);
    assert(neu == 0);

    valoraciones.eliminarValoracion(85246, res);
    assert(res == OK);
    valoraciones.numeroValoraciones(pos, neg, neu);
    assert(pos == 7);
    assert(neg == 3);
    assert(neu == 0);

    valoraciones.__consultar_elemento_pos(0, true, false, valoracion_aux, palabra);
    assert((valoracion_aux == Valoracion{42808, 87545, "2010-08-30", 212295, "Eva", "  Nina is the worst person, and her apartment is the worst and most ugly we have ever stayed. The room was dirty and everythin was a mess. ", negativo}));
    valoraciones.__consultar_elemento_pos(1, true, true, valoracion_aux, palabra);
    assert((valoracion_aux == Valoracion{42808, 90227, "2010-09-04", 16461, "Dafne", "Nina's place is very nice, clean and very close to what's important, i.e. shops, restaurants and subway station. What really makes a difference is Nina herself, not only an extremely caring host, but also a splendid person. If at the end of your stay you leave as friends, that is a lot more than you thought you'd get from your trip to Stockholm. ", positivo}));
    valoraciones.__consultar_elemento_pos(2, true, true, valoracion_aux, palabra);
    assert((valoracion_aux == Valoracion{338470, 989514, "2012-03-11", 45732, "Cassi", "This place was great! Perfect for anyone who likes art. Very close to metro, 10-minute walk to trendy / hip restaurants and bars area. Gustaf is a very nice and charming host. He gave us handpicked guide and made some useful notes. I will definitely recommend this place to my friends!", positivo}));
    valoraciones.__consultar_elemento_pos(3, true, true, valoracion_aux, palabra);
    assert((valoracion_aux == Valoracion{145320, 156423122, "2017-05-30", 45732, "Cassi", "Very nice and wonderful place, everything was ok, clean and nice. We love this apartment. The best we have stayed ever!", positivo}));
    valoraciones.__consultar_elemento_pos(4, true, true, valoracion_aux, palabra);
    assert((valoracion_aux == Valoracion{145320, 170211906, "2017-07-15", 212295, "Eva", "  Horrible place, even worse than Nina's one. We made the wrong decision when hired this apartment! ", negativo}));
    valoraciones.__consultar_elemento_pos(5, true, true, valoracion_aux, palabra);
    assert((valoracion_aux == Valoracion{220851, 404219448, "2019-01-23", 6616639, "Eliska", "What a gem! Both the place and Fredric are just lovely. Had the best stay and felt like home. The location and value are amazing. Really cool place with an extra arty and soul touch  Will be back soon and defo booking the same place! ", positivo}));
    valoraciones.__consultar_elemento_pos(6, true, true, valoracion_aux, palabra);
    assert((valoracion_aux == Valoracion{220851, 411097466, "2019-02-11", 45732, "Cassi", "A lovely place to stay managed by a perfect guest", positivo}));
    valoraciones.__consultar_elemento_pos(7, true, true, valoracion_aux, palabra);
    assert((valoracion_aux == Valoracion{313763, 418091157, "2019-03-01", 212295, "Eva", "I am tired of telling always the same, but all the apartment that I hire are horrible. Ia have always very bad luck. I believe I am not goint to travel any more. Horrible experiences always!", negativo}));
    valoraciones.__consultar_elemento_pos(8, true, true, valoracion_aux, palabra);
    assert((valoracion_aux == Valoracion{313763, 430805847, "2019-03-31", 30497368, "Emma", "Martin was a fantastic host!", positivo}));
    valoraciones.__consultar_elemento_pos(9, true, true, valoracion_aux, palabra);
    assert((valoracion_aux == Valoracion{313763, 449750278, "2019-05-07", 255803528, "Matthias", "Martin was a very helpful host. The room in his classy appartment was the perfect homebase for my city exploration trip.", positivo}));

    valoraciones.eliminarValoracion(404219448, res);
    assert(res == OK);
    valoraciones.numeroValoraciones(pos, neg, neu);
    assert(pos == 6);
    assert(neg == 3);
    assert(neu == 0);

    valoraciones.__consultar_elemento_pos(0, true, false, valoracion_aux, palabra);
    assert((valoracion_aux == Valoracion{42808, 87545, "2010-08-30", 212295, "Eva", "  Nina is the worst person, and her apartment is the worst and most ugly we have ever stayed. The room was dirty and everythin was a mess. ", negativo}));
    valoraciones.__consultar_elemento_pos(1, true, true, valoracion_aux, palabra);
    assert((valoracion_aux == Valoracion{42808, 90227, "2010-09-04", 16461, "Dafne", "Nina's place is very nice, clean and very close to what's important, i.e. shops, restaurants and subway station. What really makes a difference is Nina herself, not only an extremely caring host, but also a splendid person. If at the end of your stay you leave as friends, that is a lot more than you thought you'd get from your trip to Stockholm. ", positivo}));
    valoraciones.__consultar_elemento_pos(2, true, true, valoracion_aux, palabra);
    assert((valoracion_aux == Valoracion{338470, 989514, "2012-03-11", 45732, "Cassi", "This place was great! Perfect for anyone who likes art. Very close to metro, 10-minute walk to trendy / hip restaurants and bars area. Gustaf is a very nice and charming host. He gave us handpicked guide and made some useful notes. I will definitely recommend this place to my friends!", positivo}));
    valoraciones.__consultar_elemento_pos(3, true, true, valoracion_aux, palabra);
    assert((valoracion_aux == Valoracion{145320, 156423122, "2017-05-30", 45732, "Cassi", "Very nice and wonderful place, everything was ok, clean and nice. We love this apartment. The best we have stayed ever!", positivo}));
    valoraciones.__consultar_elemento_pos(4, true, true, valoracion_aux, palabra);
    assert((valoracion_aux == Valoracion{145320, 170211906, "2017-07-15", 212295, "Eva", "  Horrible place, even worse than Nina's one. We made the wrong decision when hired this apartment! ", negativo}));
    valoraciones.__consultar_elemento_pos(5, true, true, valoracion_aux, palabra);
    assert((valoracion_aux == Valoracion{220851, 411097466, "2019-02-11", 45732, "Cassi", "A lovely place to stay managed by a perfect guest", positivo}));
    valoraciones.__consultar_elemento_pos(6, true, true, valoracion_aux, palabra);
    assert((valoracion_aux == Valoracion{313763, 418091157, "2019-03-01", 212295, "Eva", "I am tired of telling always the same, but all the apartment that I hire are horrible. Ia have always very bad luck. I believe I am not goint to travel any more. Horrible experiences always!", negativo}));
    valoraciones.__consultar_elemento_pos(7, true, true, valoracion_aux, palabra);
    assert((valoracion_aux == Valoracion{313763, 430805847, "2019-03-31", 30497368, "Emma", "Martin was a fantastic host!", positivo}));
    valoraciones.__consultar_elemento_pos(8, true, true, valoracion_aux, palabra);
    assert((valoracion_aux == Valoracion{313763, 449750278, "2019-05-07", 255803528, "Matthias", "Martin was a very helpful host. The room in his classy appartment was the perfect homebase for my city exploration trip.", positivo}));

    valoraciones.eliminarValoracion(449750278, res);
    assert(res == OK);
    valoraciones.numeroValoraciones(pos, neg, neu);
    assert(pos == 5);
    assert(neg == 3);
    assert(neu == 0);

    valoraciones.__consultar_elemento_pos(0, true, false, valoracion_aux, palabra);
    assert((valoracion_aux == Valoracion{42808, 87545, "2010-08-30", 212295, "Eva", "  Nina is the worst person, and her apartment is the worst and most ugly we have ever stayed. The room was dirty and everythin was a mess. ", negativo}));
    valoraciones.__consultar_elemento_pos(1, true, true, valoracion_aux, palabra);
    assert((valoracion_aux == Valoracion{42808, 90227, "2010-09-04", 16461, "Dafne", "Nina's place is very nice, clean and very close to what's important, i.e. shops, restaurants and subway station. What really makes a difference is Nina herself, not only an extremely caring host, but also a splendid person. If at the end of your stay you leave as friends, that is a lot more than you thought you'd get from your trip to Stockholm. ", positivo}));
    valoraciones.__consultar_elemento_pos(2, true, true, valoracion_aux, palabra);
    assert((valoracion_aux == Valoracion{338470, 989514, "2012-03-11", 45732, "Cassi", "This place was great! Perfect for anyone who likes art. Very close to metro, 10-minute walk to trendy / hip restaurants and bars area. Gustaf is a very nice and charming host. He gave us handpicked guide and made some useful notes. I will definitely recommend this place to my friends!", positivo}));
    valoraciones.__consultar_elemento_pos(3, true, true, valoracion_aux, palabra);
    assert((valoracion_aux == Valoracion{145320, 156423122, "2017-05-30", 45732, "Cassi", "Very nice and wonderful place, everything was ok, clean and nice. We love this apartment. The best we have stayed ever!", positivo}));
    valoraciones.__consultar_elemento_pos(4, true, true, valoracion_aux, palabra);
    assert((valoracion_aux == Valoracion{145320, 170211906, "2017-07-15", 212295, "Eva", "  Horrible place, even worse than Nina's one. We made the wrong decision when hired this apartment! ", negativo}));
    valoraciones.__consultar_elemento_pos(5, true, true, valoracion_aux, palabra);
    assert((valoracion_aux == Valoracion{220851, 411097466, "2019-02-11", 45732, "Cassi", "A lovely place to stay managed by a perfect guest", positivo}));
    valoraciones.__consultar_elemento_pos(6, true, true, valoracion_aux, palabra);
    assert((valoracion_aux == Valoracion{313763, 418091157, "2019-03-01", 212295, "Eva", "I am tired of telling always the same, but all the apartment that I hire are horrible. Ia have always very bad luck. I believe I am not goint to travel any more. Horrible experiences always!", negativo}));
    valoraciones.__consultar_elemento_pos(7, true, true, valoracion_aux, palabra);
    assert((valoracion_aux == Valoracion{313763, 430805847, "2019-03-31", 30497368, "Emma", "Martin was a fantastic host!", positivo}));

    valoraciones.eliminarValoracion(87545, res);
    assert(res == OK);
    valoraciones.numeroValoraciones(pos, neg, neu);
    assert(pos == 5);
    assert(neg == 2);
    assert(neu == 0);

    valoraciones.__consultar_elemento_pos(0, true, true, valoracion_aux, palabra);
    assert((valoracion_aux == Valoracion{42808, 90227, "2010-09-04", 16461, "Dafne", "Nina's place is very nice, clean and very close to what's important, i.e. shops, restaurants and subway station. What really makes a difference is Nina herself, not only an extremely caring host, but also a splendid person. If at the end of your stay you leave as friends, that is a lot more than you thought you'd get from your trip to Stockholm. ", positivo}));
    valoraciones.__consultar_elemento_pos(1, true, true, valoracion_aux, palabra);
    assert((valoracion_aux == Valoracion{338470, 989514, "2012-03-11", 45732, "Cassi", "This place was great! Perfect for anyone who likes art. Very close to metro, 10-minute walk to trendy / hip restaurants and bars area. Gustaf is a very nice and charming host. He gave us handpicked guide and made some useful notes. I will definitely recommend this place to my friends!", positivo}));
    valoraciones.__consultar_elemento_pos(2, true, true, valoracion_aux, palabra);
    assert((valoracion_aux == Valoracion{145320, 156423122, "2017-05-30", 45732, "Cassi", "Very nice and wonderful place, everything was ok, clean and nice. We love this apartment. The best we have stayed ever!", positivo}));
    valoraciones.__consultar_elemento_pos(3, true, true, valoracion_aux, palabra);
    assert((valoracion_aux == Valoracion{145320, 170211906, "2017-07-15", 212295, "Eva", "  Horrible place, even worse than Nina's one. We made the wrong decision when hired this apartment! ", negativo}));
    valoraciones.__consultar_elemento_pos(4, true, true, valoracion_aux, palabra);
    assert((valoracion_aux == Valoracion{220851, 411097466, "2019-02-11", 45732, "Cassi", "A lovely place to stay managed by a perfect guest", positivo}));
    valoraciones.__consultar_elemento_pos(5, true, true, valoracion_aux, palabra);
    assert((valoracion_aux == Valoracion{313763, 418091157, "2019-03-01", 212295, "Eva", "I am tired of telling always the same, but all the apartment that I hire are horrible. Ia have always very bad luck. I believe I am not goint to travel any more. Horrible experiences always!", negativo}));
    valoraciones.__consultar_elemento_pos(6, true, true, valoracion_aux, palabra);
    assert((valoracion_aux == Valoracion{313763, 430805847, "2019-03-31", 30497368, "Emma", "Martin was a fantastic host!", positivo}));

    valoraciones.eliminarValoracion(418091157, res);
    assert(res == OK);
    valoraciones.numeroValoraciones(pos, neg, neu);
    assert(pos == 5);
    assert(neg == 1);
    assert(neu == 0);

    valoraciones.__consultar_elemento_pos(0, true, true, valoracion_aux, palabra);
    assert((valoracion_aux == Valoracion{42808, 90227, "2010-09-04", 16461, "Dafne", "Nina's place is very nice, clean and very close to what's important, i.e. shops, restaurants and subway station. What really makes a difference is Nina herself, not only an extremely caring host, but also a splendid person. If at the end of your stay you leave as friends, that is a lot more than you thought you'd get from your trip to Stockholm. ", positivo}));
    valoraciones.__consultar_elemento_pos(1, true, true, valoracion_aux, palabra);
    assert((valoracion_aux == Valoracion{338470, 989514, "2012-03-11", 45732, "Cassi", "This place was great! Perfect for anyone who likes art. Very close to metro, 10-minute walk to trendy / hip restaurants and bars area. Gustaf is a very nice and charming host. He gave us handpicked guide and made some useful notes. I will definitely recommend this place to my friends!", positivo}));
    valoraciones.__consultar_elemento_pos(2, true, true, valoracion_aux, palabra);
    assert((valoracion_aux == Valoracion{145320, 156423122, "2017-05-30", 45732, "Cassi", "Very nice and wonderful place, everything was ok, clean and nice. We love this apartment. The best we have stayed ever!", positivo}));
    valoraciones.__consultar_elemento_pos(3, true, true, valoracion_aux, palabra);
    assert((valoracion_aux == Valoracion{145320, 170211906, "2017-07-15", 212295, "Eva", "  Horrible place, even worse than Nina's one. We made the wrong decision when hired this apartment! ", negativo}));
    valoraciones.__consultar_elemento_pos(4, true, true, valoracion_aux, palabra);
    assert((valoracion_aux == Valoracion{220851, 411097466, "2019-02-11", 45732, "Cassi", "A lovely place to stay managed by a perfect guest", positivo}));
    valoraciones.__consultar_elemento_pos(5, true, true, valoracion_aux, palabra);
    assert((valoracion_aux == Valoracion{313763, 430805847, "2019-03-31", 30497368, "Emma", "Martin was a fantastic host!", positivo}));

    valoraciones.eliminarValoracion(170211906, res);
    assert(res == OK);
    valoraciones.numeroValoraciones(pos, neg, neu);
    assert(pos == 5);
    assert(neg == 0);
    assert(neu == 0);

    valoraciones.__consultar_elemento_pos(0, true, true, valoracion_aux, palabra);
    assert((valoracion_aux == Valoracion{42808, 90227, "2010-09-04", 16461, "Dafne", "Nina's place is very nice, clean and very close to what's important, i.e. shops, restaurants and subway station. What really makes a difference is Nina herself, not only an extremely caring host, but also a splendid person. If at the end of your stay you leave as friends, that is a lot more than you thought you'd get from your trip to Stockholm. ", positivo}));
    valoraciones.__consultar_elemento_pos(1, true, true, valoracion_aux, palabra);
    assert((valoracion_aux == Valoracion{338470, 989514, "2012-03-11", 45732, "Cassi", "This place was great! Perfect for anyone who likes art. Very close to metro, 10-minute walk to trendy / hip restaurants and bars area. Gustaf is a very nice and charming host. He gave us handpicked guide and made some useful notes. I will definitely recommend this place to my friends!", positivo}));
    valoraciones.__consultar_elemento_pos(2, true, true, valoracion_aux, palabra);
    assert((valoracion_aux == Valoracion{145320, 156423122, "2017-05-30", 45732, "Cassi", "Very nice and wonderful place, everything was ok, clean and nice. We love this apartment. The best we have stayed ever!", positivo}));
    valoraciones.__consultar_elemento_pos(3, true, true, valoracion_aux, palabra);
    assert((valoracion_aux == Valoracion{220851, 411097466, "2019-02-11", 45732, "Cassi", "A lovely place to stay managed by a perfect guest", positivo}));
    valoraciones.__consultar_elemento_pos(4, true, true, valoracion_aux, palabra);
    assert((valoracion_aux == Valoracion{313763, 430805847, "2019-03-31", 30497368, "Emma", "Martin was a fantastic host!", positivo}));

    valoraciones.eliminarValoracion(170211906, res);
    assert(res == NO_EXISTE);
    valoraciones.numeroValoraciones(pos, neg, neu);
    assert(pos == 5);
    assert(neg == 0);
    assert(neu == 0);

    valoraciones.__consultar_elemento_pos(0, true, true, valoracion_aux, palabra);
    assert((valoracion_aux == Valoracion{42808, 90227, "2010-09-04", 16461, "Dafne", "Nina's place is very nice, clean and very close to what's important, i.e. shops, restaurants and subway station. What really makes a difference is Nina herself, not only an extremely caring host, but also a splendid person. If at the end of your stay you leave as friends, that is a lot more than you thought you'd get from your trip to Stockholm. ", positivo}));
    valoraciones.__consultar_elemento_pos(1, true, true, valoracion_aux, palabra);
    assert((valoracion_aux == Valoracion{338470, 989514, "2012-03-11", 45732, "Cassi", "This place was great! Perfect for anyone who likes art. Very close to metro, 10-minute walk to trendy / hip restaurants and bars area. Gustaf is a very nice and charming host. He gave us handpicked guide and made some useful notes. I will definitely recommend this place to my friends!", positivo}));
    valoraciones.__consultar_elemento_pos(2, true, true, valoracion_aux, palabra);
    assert((valoracion_aux == Valoracion{145320, 156423122, "2017-05-30", 45732, "Cassi", "Very nice and wonderful place, everything was ok, clean and nice. We love this apartment. The best we have stayed ever!", positivo}));
    valoraciones.__consultar_elemento_pos(3, true, true, valoracion_aux, palabra);
    assert((valoracion_aux == Valoracion{220851, 411097466, "2019-02-11", 45732, "Cassi", "A lovely place to stay managed by a perfect guest", positivo}));
    valoraciones.__consultar_elemento_pos(4, true, true, valoracion_aux, palabra);
    assert((valoracion_aux == Valoracion{313763, 430805847, "2019-03-31", 30497368, "Emma", "Martin was a fantastic host!", positivo}));
}

// Prueba de modificarValoracion
void test_modificar_valoracion()
{
    Valoraciones valoraciones;
    Resultado res;
    unsigned pos, neg, neu;
    string palabra;
    Valoracion valoracion_aux;

    valoraciones.cargarPalabrasPositivas(FIC_PALABRAS_POSITIVAS, res);
    assert(res == OK);
    valoraciones.cargarPalabrasNegativas(FIC_PALABRAS_NEGATIVAS, res);
    assert(res == OK);
    valoraciones.numeroPalabras(pos, neg);
    assert(pos == 2006);
    assert(neg == 4783);

    valoraciones.cargarValoraciones(FIC_VALORACIONES, res);
    assert(res == OK);
    valoraciones.numeroValoraciones(pos, neg, neu);
    assert(pos == 8);
    assert(neg == 3);
    assert(neu == 0);

    // ******** Modificamos valoraciones

    valoraciones.modificarValoracion(Valoracion{145320, 156423122, "2017-05-20", 45732, "Cassi Na", "Very nice and wonderful place, everything was ok, clean and nice. We love this apartment.", positivo}, res);
    assert(res == OK);
    valoraciones.numeroValoraciones(pos, neg, neu);
    assert(pos == 8);
    assert(neg == 3);
    assert(neu == 0);

    // Comprobamos las valoraciones
    valoraciones.__consultar_elemento_pos(0, true, true, valoracion_aux, palabra);
    assert((valoracion_aux == Valoracion{42808, 85246, "2010-08-26", 45732, "Cassi", "Nina is truly a wonderful hostess. The room was very cozy and her apartment is lovely and perfectly located in a great neighborhood with lots of restaurants and cafes. There are two grocery stores within walking distance. It is also super close to the subway station, making it a breeze to get there from the airport and to get into city center.  Nina was  was not only very helpful and responsive, but tremendously pleasant and welcoming. When I arrived she had prepared a welcome kit with information about local attractions, maps of the city, and even a lonely planet guide. She even arranged for me to attend yoga class with her, which was fantastic! ", positivo}));
    valoraciones.__consultar_elemento_pos(1, true, false, valoracion_aux, palabra);
    assert((valoracion_aux == Valoracion{42808, 87545, "2010-08-30", 212295, "Eva", "  Nina is the worst person, and her apartment is the worst and most ugly we have ever stayed. The room was dirty and everythin was a mess. ", negativo}));
    valoraciones.__consultar_elemento_pos(2, true, true, valoracion_aux, palabra);
    assert((valoracion_aux == Valoracion{42808, 90227, "2010-09-04", 16461, "Dafne", "Nina's place is very nice, clean and very close to what's important, i.e. shops, restaurants and subway station. What really makes a difference is Nina herself, not only an extremely caring host, but also a splendid person. If at the end of your stay you leave as friends, that is a lot more than you thought you'd get from your trip to Stockholm. ", positivo}));
    valoraciones.__consultar_elemento_pos(3, true, true, valoracion_aux, palabra);
    assert((valoracion_aux == Valoracion{338470, 989514, "2012-03-11", 45732, "Cassi", "This place was great! Perfect for anyone who likes art. Very close to metro, 10-minute walk to trendy / hip restaurants and bars area. Gustaf is a very nice and charming host. He gave us handpicked guide and made some useful notes. I will definitely recommend this place to my friends!", positivo}));
    valoraciones.__consultar_elemento_pos(4, true, true, valoracion_aux, palabra);
    assert((valoracion_aux == Valoracion{145320, 156423122, "2017-05-20", 45732, "Cassi Na", "Very nice and wonderful place, everything was ok, clean and nice. We love this apartment.", positivo}));
    valoraciones.__consultar_elemento_pos(5, true, true, valoracion_aux, palabra);
    assert((valoracion_aux == Valoracion{145320, 170211906, "2017-07-15", 212295, "Eva", "  Horrible place, even worse than Nina's one. We made the wrong decision when hired this apartment! ", negativo}));
    valoraciones.__consultar_elemento_pos(6, true, true, valoracion_aux, palabra);
    assert((valoracion_aux == Valoracion{220851, 404219448, "2019-01-23", 6616639, "Eliska", "What a gem! Both the place and Fredric are just lovely. Had the best stay and felt like home. The location and value are amazing. Really cool place with an extra arty and soul touch  Will be back soon and defo booking the same place! ", positivo}));
    valoraciones.__consultar_elemento_pos(7, true, true, valoracion_aux, palabra);
    assert((valoracion_aux == Valoracion{220851, 411097466, "2019-02-11", 45732, "Cassi", "A lovely place to stay managed by a perfect guest", positivo}));
    valoraciones.__consultar_elemento_pos(8, true, true, valoracion_aux, palabra);
    assert((valoracion_aux == Valoracion{313763, 418091157, "2019-03-01", 212295, "Eva", "I am tired of telling always the same, but all the apartment that I hire are horrible. Ia have always very bad luck. I believe I am not goint to travel any more. Horrible experiences always!", negativo}));
    valoraciones.__consultar_elemento_pos(9, true, true, valoracion_aux, palabra);
    assert((valoracion_aux == Valoracion{313763, 430805847, "2019-03-31", 30497368, "Emma", "Martin was a fantastic host!", positivo}));
    valoraciones.__consultar_elemento_pos(10, true, true, valoracion_aux, palabra);
    assert((valoracion_aux == Valoracion{313763, 449750278, "2019-05-07", 255803528, "Matthias", "Martin was a very helpful host. The room in his classy appartment was the perfect homebase for my city exploration trip.", positivo}));

    valoraciones.modificarValoracion(Valoracion{145320, 156423122, "2017-05-20", 45732, "Cassi Na", "Horrible and awful place, unpleasant and dissapointing. I am very disgusted", negativo}, res);
    assert(res == OK);
    valoraciones.numeroValoraciones(pos, neg, neu);
    assert(pos == 7);
    assert(neg == 4);
    assert(neu == 0);
    // Comprobamos las valoraciones
    valoraciones.__consultar_elemento_pos(0, true, true, valoracion_aux, palabra);
    assert((valoracion_aux == Valoracion{42808, 85246, "2010-08-26", 45732, "Cassi", "Nina is truly a wonderful hostess. The room was very cozy and her apartment is lovely and perfectly located in a great neighborhood with lots of restaurants and cafes. There are two grocery stores within walking distance. It is also super close to the subway station, making it a breeze to get there from the airport and to get into city center.  Nina was  was not only very helpful and responsive, but tremendously pleasant and welcoming. When I arrived she had prepared a welcome kit with information about local attractions, maps of the city, and even a lonely planet guide. She even arranged for me to attend yoga class with her, which was fantastic! ", positivo}));
    valoraciones.__consultar_elemento_pos(1, true, false, valoracion_aux, palabra);
    assert((valoracion_aux == Valoracion{42808, 87545, "2010-08-30", 212295, "Eva", "  Nina is the worst person, and her apartment is the worst and most ugly we have ever stayed. The room was dirty and everythin was a mess. ", negativo}));
    valoraciones.__consultar_elemento_pos(2, true, true, valoracion_aux, palabra);
    assert((valoracion_aux == Valoracion{42808, 90227, "2010-09-04", 16461, "Dafne", "Nina's place is very nice, clean and very close to what's important, i.e. shops, restaurants and subway station. What really makes a difference is Nina herself, not only an extremely caring host, but also a splendid person. If at the end of your stay you leave as friends, that is a lot more than you thought you'd get from your trip to Stockholm. ", positivo}));
    valoraciones.__consultar_elemento_pos(3, true, true, valoracion_aux, palabra);
    assert((valoracion_aux == Valoracion{338470, 989514, "2012-03-11", 45732, "Cassi", "This place was great! Perfect for anyone who likes art. Very close to metro, 10-minute walk to trendy / hip restaurants and bars area. Gustaf is a very nice and charming host. He gave us handpicked guide and made some useful notes. I will definitely recommend this place to my friends!", positivo}));
    valoraciones.__consultar_elemento_pos(4, true, true, valoracion_aux, palabra);
    assert((valoracion_aux == Valoracion{145320, 156423122, "2017-05-20", 45732, "Cassi Na", "Horrible and awful place, unpleasant and dissapointing. I am very disgusted", negativo}));
    valoraciones.__consultar_elemento_pos(5, true, true, valoracion_aux, palabra);
    assert((valoracion_aux == Valoracion{145320, 170211906, "2017-07-15", 212295, "Eva", "  Horrible place, even worse than Nina's one. We made the wrong decision when hired this apartment! ", negativo}));
    valoraciones.__consultar_elemento_pos(6, true, true, valoracion_aux, palabra);
    assert((valoracion_aux == Valoracion{220851, 404219448, "2019-01-23", 6616639, "Eliska", "What a gem! Both the place and Fredric are just lovely. Had the best stay and felt like home. The location and value are amazing. Really cool place with an extra arty and soul touch  Will be back soon and defo booking the same place! ", positivo}));
    valoraciones.__consultar_elemento_pos(7, true, true, valoracion_aux, palabra);
    assert((valoracion_aux == Valoracion{220851, 411097466, "2019-02-11", 45732, "Cassi", "A lovely place to stay managed by a perfect guest", positivo}));
    valoraciones.__consultar_elemento_pos(8, true, true, valoracion_aux, palabra);
    assert((valoracion_aux == Valoracion{313763, 418091157, "2019-03-01", 212295, "Eva", "I am tired of telling always the same, but all the apartment that I hire are horrible. Ia have always very bad luck. I believe I am not goint to travel any more. Horrible experiences always!", negativo}));
    valoraciones.__consultar_elemento_pos(9, true, true, valoracion_aux, palabra);
    assert((valoracion_aux == Valoracion{313763, 430805847, "2019-03-31", 30497368, "Emma", "Martin was a fantastic host!", positivo}));
    valoraciones.__consultar_elemento_pos(10, true, true, valoracion_aux, palabra);
    assert((valoracion_aux == Valoracion{313763, 449750278, "2019-05-07", 255803528, "Matthias", "Martin was a very helpful host. The room in his classy appartment was the perfect homebase for my city exploration trip.", positivo}));

    valoraciones.modificarValoracion(Valoracion(145320, 170211906, "2017-07-30", 212295, "Eva", "Very nice and wonderful place, I love it", positivo), res);
    assert(res == OK);
    valoraciones.numeroValoraciones(pos, neg, neu);
    assert(pos == 8);
    assert(neg == 3);
    assert(neu == 0);
    // Comprobamos las valoraciones
    valoraciones.__consultar_elemento_pos(0, true, true, valoracion_aux, palabra);
    assert((valoracion_aux == Valoracion{42808, 85246, "2010-08-26", 45732, "Cassi", "Nina is truly a wonderful hostess. The room was very cozy and her apartment is lovely and perfectly located in a great neighborhood with lots of restaurants and cafes. There are two grocery stores within walking distance. It is also super close to the subway station, making it a breeze to get there from the airport and to get into city center.  Nina was  was not only very helpful and responsive, but tremendously pleasant and welcoming. When I arrived she had prepared a welcome kit with information about local attractions, maps of the city, and even a lonely planet guide. She even arranged for me to attend yoga class with her, which was fantastic! ", positivo}));
    valoraciones.__consultar_elemento_pos(1, true, false, valoracion_aux, palabra);
    assert((valoracion_aux == Valoracion{42808, 87545, "2010-08-30", 212295, "Eva", "  Nina is the worst person, and her apartment is the worst and most ugly we have ever stayed. The room was dirty and everythin was a mess. ", negativo}));
    valoraciones.__consultar_elemento_pos(2, true, true, valoracion_aux, palabra);
    assert((valoracion_aux == Valoracion{42808, 90227, "2010-09-04", 16461, "Dafne", "Nina's place is very nice, clean and very close to what's important, i.e. shops, restaurants and subway station. What really makes a difference is Nina herself, not only an extremely caring host, but also a splendid person. If at the end of your stay you leave as friends, that is a lot more than you thought you'd get from your trip to Stockholm. ", positivo}));
    valoraciones.__consultar_elemento_pos(3, true, true, valoracion_aux, palabra);
    assert((valoracion_aux == Valoracion{338470, 989514, "2012-03-11", 45732, "Cassi", "This place was great! Perfect for anyone who likes art. Very close to metro, 10-minute walk to trendy / hip restaurants and bars area. Gustaf is a very nice and charming host. He gave us handpicked guide and made some useful notes. I will definitely recommend this place to my friends!", positivo}));
    valoraciones.__consultar_elemento_pos(4, true, true, valoracion_aux, palabra);
    assert((valoracion_aux == Valoracion{145320, 156423122, "2017-05-20", 45732, "Cassi Na", "Horrible and awful place, unpleasant and dissapointing. I am very disgusted", negativo}));
    valoraciones.__consultar_elemento_pos(5, true, true, valoracion_aux, palabra);
    assert((valoracion_aux == Valoracion{145320, 170211906, "2017-07-30", 212295, "Eva", "Very nice and wonderful place, I love it", positivo}));
    valoraciones.__consultar_elemento_pos(6, true, true, valoracion_aux, palabra);
    assert((valoracion_aux == Valoracion{220851, 404219448, "2019-01-23", 6616639, "Eliska", "What a gem! Both the place and Fredric are just lovely. Had the best stay and felt like home. The location and value are amazing. Really cool place with an extra arty and soul touch  Will be back soon and defo booking the same place! ", positivo}));
    valoraciones.__consultar_elemento_pos(7, true, true, valoracion_aux, palabra);
    assert((valoracion_aux == Valoracion{220851, 411097466, "2019-02-11", 45732, "Cassi", "A lovely place to stay managed by a perfect guest", positivo}));
    valoraciones.__consultar_elemento_pos(8, true, true, valoracion_aux, palabra);
    assert((valoracion_aux == Valoracion{313763, 418091157, "2019-03-01", 212295, "Eva", "I am tired of telling always the same, but all the apartment that I hire are horrible. Ia have always very bad luck. I believe I am not goint to travel any more. Horrible experiences always!", negativo}));
    valoraciones.__consultar_elemento_pos(9, true, true, valoracion_aux, palabra);
    assert((valoracion_aux == Valoracion{313763, 430805847, "2019-03-31", 30497368, "Emma", "Martin was a fantastic host!", positivo}));
    valoraciones.__consultar_elemento_pos(10, true, true, valoracion_aux, palabra);
    assert((valoracion_aux == Valoracion{313763, 449750278, "2019-05-07", 255803528, "Matthias", "Martin was a very helpful host. The room in his classy appartment was the perfect homebase for my city exploration trip.", positivo}));
}

// Prueba de valoracionesAlojamiento
void test_valoraciones_alojamiento()
{
    Valoraciones valoraciones;
    Resultado res;
    unsigned pos, neg, neu;
    Valoracion valoracion_aux;

    valoraciones.cargarPalabrasPositivas(FIC_PALABRAS_POSITIVAS, res);
    assert(res == OK);
    valoraciones.cargarPalabrasNegativas(FIC_PALABRAS_NEGATIVAS, res);
    assert(res == OK);
    valoraciones.numeroPalabras(pos, neg);
    assert(pos == 2006);
    assert(neg == 4783);

    valoraciones.cargarValoraciones(FIC_VALORACIONES, res);
    assert(res == OK);
    valoraciones.numeroValoraciones(pos, neg, neu);
    assert(pos == 8);
    assert(neg == 3);
    assert(neu == 0);

    // Consultamos las valoraciones de un alojamiento
    Ids ids;
    valoraciones.valoracionesAlojamiento(42808, ids);
    assert(ids.num_ids == 3);
    assert(ids.ids[0] == 85246);
    assert(ids.ids[2] == 90227);
    assert(ids.ids[1] == 87545);
}

// Prueba de valoracionesRevisor
void test_valoraciones_revisor()
{
    Valoraciones valoraciones;
    Resultado res;
    unsigned pos, neg, neu;
    Valoracion valoracion_aux;
    Ids ids;

    valoraciones.cargarPalabrasPositivas(FIC_PALABRAS_POSITIVAS, res);
    assert(res == OK);
    valoraciones.cargarPalabrasNegativas(FIC_PALABRAS_NEGATIVAS, res);
    assert(res == OK);
    valoraciones.numeroPalabras(pos, neg);
    assert(pos == 2006);
    assert(neg == 4783);

    valoraciones.cargarValoraciones(FIC_VALORACIONES, res);
    assert(res == OK);
    valoraciones.numeroValoraciones(pos, neg, neu);
    assert(pos == 8);
    assert(neg == 3);
    assert(neu == 0);

    // Consultamos las valoraciones de un revisor
    valoraciones.valoracionesRevisor(45732, ids);
    assert(ids.num_ids == 4);
    assert(ids.ids[0] == 85246);
    assert(ids.ids[1] == 989514);
    assert(ids.ids[2] == 156423122);
    assert(ids.ids[3] == 411097466);

    // Consultamos las valoraciones de un revisor
    valoraciones.valoracionesRevisor(212295, ids);
    assert(ids.num_ids == 3);
    assert(ids.ids[0] == 87545);
    assert(ids.ids[1] == 170211906);
    assert(ids.ids[2] == 418091157);
}
// //***************************
int main()
{
    // Prueba del constructor por defecto
    cout << "testing... 'Valoraciones()'" << endl;
    test_constructor();
    cout << "   --- OK." << endl;

    // Prueba de cargarPalabrasPositivas
    cout << "testing... 'void cargarPalabrasPositivas(const std::string &, Resultado &)'" << endl;
    test_cargarPalabrasPositivas();
    cout << "   --- OK." << endl;

    // Prueba de cargarPalabrasNegativas
    cout << "testing... 'void cargarPalabrasNegativas(const std::string &, Resultado &)'" << endl;
    test_cargar_palabras_negativas();
    cout << "   --- OK." << endl;

    // Prueba de insertarValoracion
    cout << "testing... 'void insertarValoracion(const Valoracion &, Resultado &)'" << endl;
    test_insertar_valoracion();
    cout << "   --- OK." << endl;

    // Prueba de buscarValoracion
    cout << "testing... 'void buscarValoracion(unsigned, Valoracion &, bool &) const'" << endl;
    test_buscar_valoracion();
    cout << "   --- OK." << endl;

    // Prueba de cargarValoraciones
    cout << "testing... 'void cargarValoraciones(const std::string &, Resultado &)'" << endl;
    test_cargar_valoraciones();
    cout << "   --- OK." << endl;

    // Prueba de guardarValoraciones
    cout << "testing... 'void guardarValoraciones(const std::string &, Resultado &)'" << endl;
    test_guardar_valoraciones();
    cout << "   --- OK." << endl;

    // Prueba de actualizarSentimiento
    cout << "testing... 'void actualizarSentimiento(unsigned, unsigned, Resultado &)'" << endl;
    test_actualizar_sentimiento();
    cout << "   --- OK." << endl;

    // Prueba de actualizarSentimientos
    cout << "testing... 'void actualizarSentimientos(unsigned)'" << endl;
    test_actualizar_sentimientos();
    cout << "   --- OK." << endl;

    // Prueba de numeroValoraciones
    cout << "testing... 'void numeroValoraciones(unsigned &, unsigned &, unsigned &) const'" << endl;
    test_numero_valoraciones();
    cout << "   --- OK." << endl;

    // Prueba de listaValoraciones
    cout << "testing... 'void listaValoraciones(Ids &, Ids &, Ids &) const'" << endl;
    test_lista_valoraciones();
    cout << "   --- OK." << endl;

    // Prueba de numeroPalabras
    cout << "testing... 'void numeroPalabras(unsigned &, unsigned &) const'" << endl;
    test_numero_palabras();
    cout << "   --- OK." << endl;

    // Prueba del constructor de copia
    cout << "testing... 'Valoraciones(const Valoraciones &)'" << endl;
    test_constructor_de_copia();
    cout << "   --- OK." << endl;

    // Prueba del eliminarValoracion
    cout << "testing... 'void eliminarValoracion(unsigned, bool &, Resultado &)'" << endl;
    test_eliminar_valoracion();
    cout << "   --- OK." << endl;

    // Prueba del modidicar_valoracion
    cout << "testing... 'void modificarValoracion(const Valoracion &, Resultado &)'" << endl;
    test_modificar_valoracion();
    cout << "   --- OK." << endl;

    // Prueba del valoracionesAlojamiento
    cout << "testing... 'void valoracionesAlojamiento(unsigned, Ids &) const'" << endl;
    test_valoraciones_alojamiento();
    cout << "   --- OK." << endl;

    // Prueba del valoracionesRevisor
    cout << "testing... 'void valoracionesRevisor(unsigned, Ids &, Ids &) const'" << endl;
    test_valoraciones_revisor();
    cout << "   --- OK." << endl;

    cout << endl
         << "--- TEST OK." << endl;
}