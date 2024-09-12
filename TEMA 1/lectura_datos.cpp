#include <iostream> // Incluye flujos de entrada/teclado (cin) y de salida/pantalla (cout).
#include <fstream> // Incluye flujos de entrada (ifstream) y de salida (ofstream).
#include <string>
using namespace std;

int main() {
    const string fichero="datos.in";
    int num;
    const unsigned n=5; // Podemos declarar una variable para leer los n primeros datos del fichero.
    
    ifstream fi; // Declaramos un flujo de entrada a partir del que leer los datos.
    fi.open(fichero); // Abrimos el fichero con la orden .open() para el fichero.

    // Lectura del primer dato. 
    /*
    fi>>num;
    cout<<num; // La consola solo muestra el primer dato antes de los espaciados.
    */

   // Lectura de n datos.
   /*
   for(unsigned i=0; i<n; ++i) {
    fi>>num;
    cout<<num<<endl; // La consola muestra los n primeros datos del fichero (por defecto, no salen espaciados).
   }
   */

  // Comprobación de apertura del fichero previa y final de fichero.
  
  if(fi.fail()) { // Con la orden .fail (booleano), comprobamos si el fichero se ha abierto correctamente.
    cout<<"El fichero de entrada no se ha podido abrir correctamente"<<endl;
  }
  else { // Si el fichero se ha podido abrir correctamente, se hace la lectura total del mismo.
    fi>>num; // Hacemos una primera lectura por adelantado para poner a correr la cuenta de fichero.
    while(!fi.eof()) { // Se leen los datos hasta que se detecte el fin de fichero.
        cout<<num<<endl;
        fi>>num;
    }
  }

   fi.close();
   return 0;
}

/* 
COMPILACIÓN DEL SCRIPT:
>> g++ [archivo .cpp] -o [nombre ejecutable (.exe opcional)]

LANZAMIENTO DEL EJECUTABLE:
>> .\[nombre ejecutable].exe
*/