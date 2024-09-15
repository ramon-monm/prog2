/* Escribir un programa que lea una serie de números reales, almacenados en el fichero datos_reales.dat, calcule su
media y su desviación estándar y escriba estas en un fichero de resultados, denominado estadisticas.dat.
Para ello, deben desarrollarse las siguientes funciones:
1. La función leer_datos lee del fichero, cuyo nombre se pasa como parámetro, una serie de números reales,
separados por saltos de línea, y los almacena en un array incompleto de números reales (de tipo Datos):
void leer_datos(const string &nombre_fic, Datos &datos);
2. La función calcular_estadisticas recibe un array incompleto, de tipo Datos. que contiene una lista de
números reales y, en caso de contenga al menos un número real (precondición), devuelve la media y la desviación
estándar de estos datos:
void calcular_estadisticas(const Datos &datos, double &media, double &desviacion);
1
3. La función escribir_datos escribe en el fichero, cuyo nombre se pasa como parámetro, las estadísticas
(número de datos, media y la desviación estándar) de los datos que se pasan como parámetro (almacenados
en un array incompleto de tipo Datos), en el siguiente formato:
Número de datos leídos: <número_de_datos>
La media de los datos es: <media>
La desviación estándar de los datos es: <desviación>
Si el número de datos leído es cero, la media y la desviación estándar deben ser ambas NaN. Es decir, debe aparecer
lo siguiente en el fichero:
Número de datos leídos: 0
La media de los datos es: NaN
La desviación estándar de los datos es: NaN
Esta es la cabecera de la función:
void escribir_datos(const string &nombre_fic, const Datos &datos); */

#include <iostream>
#include <fstream>
#include <string>
#include <array>
#include <cmath>
using namespace std;

const int N=15;
typedef array <double, N> Datos;

void leer_datos(const string fichero, Datos &datos);
void calcular_estadisticas(Datos &datos, double &med, double &de);

int main() {
    const string fichero="datos_reales.dat";
    Datos vect={0};
    double media, desviacion_est;
    leer_datos(fichero, vect); for(unsigned i=0; i<N; ++i) {cout<<vect[i]<<endl;}
    calcular_estadisticas(vect, media, desviacion_est);
    cout<<media<<" "<<desviacion_est<<endl;
    return 0;
}

void leer_datos(const string fichero, Datos &datos) {
    ifstream fi;
    unsigned i=0;
    fi.open(fichero);
    if(!fi.fail()) {
        fi>>datos[i];
        while(!fi.eof()) {
            ++i;
            fi>>datos[i];
        }
        fi.close();
    }
}

void calcular_estadisticas(Datos &datos, double &med, double &de) {
    double suma=0;
    unsigned n=0;
    for(unsigned i=0; i<N; ++i) {
        if(datos[i]!=0) {++n;}
        else {break;}
    }
    if(n>0) {
        for(unsigned i=0; i<n; ++i) {
            suma+=datos[i];
        }
        med=suma/n; suma=0;
        for(unsigned i=0; i<n; ++i) {
            suma+=pow(datos[i]-med, 2); 
        }
        de=sqrt(suma/(n-1));
    }
}