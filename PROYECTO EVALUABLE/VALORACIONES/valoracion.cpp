/***********************************************************************************
 * Fichero valoracion.cpp para la implementación de métodos de la clase
 * Valoracion para la gestión de la información correspondiente a la valoración de
 * un alojamiento turístico.
 *
 * Alumno/a: Ramón Montoro Mazuela 
 * Fecha: 
 * *********************************************************************************/

#include "valoracion.hpp"
#include "palabras.hpp"
#include <string>
#include <cctype>
#include <iostream>
#include <cassert>
#include <sstream>

using namespace std;

// ------- FUNCIONES AUXILIARES PARA LA IMPLEMENTACIÓN DE LOS MÉTODOS
// (IMPLEMENTADAS POR EL PROFESORADO)

// ------- FUNCIONES AUXILIARES PARA LA IMPLEMENTACIÓN DE LOS MÉTODOS
// (IMPLEMENTADAS POR EL PROFESORADO)

namespace
{
    bool fechaCorrecta(const string &fec)
    {
        bool correcta = fec.size() == 10;

        correcta = isdigit(fec[0]) &&
                   isdigit(fec[1]) &&
                   isdigit(fec[2]) &&
                   isdigit(fec[3]) &&
                   isdigit(fec[5]) &&
                   isdigit(fec[6]) &&
                   isdigit(fec[8]) &&
                   isdigit(fec[9]) &&
                   fec[4] == '-' &&
                   fec[7] == '-';

        return correcta;
    }

    void escribirSentimiento(bblProg2::Sentimiento sent)
    {
        switch (sent)
        {
        case bblProg2::neutro:
            cout << "neutro";
            break;
        case bblProg2::negativo:
            cout << "negativo";
            break;
        case bblProg2::positivo:
            cout << "positivo";
            break;
        }
    }

    // Limpia un comentario (cadena de caracteres):
    //  - elimina signos de puntuación
    //  - convierte todo a minúscula
    //  - elimina espacios repetidos
    //  - elimina todos los espacios iniciales y finales
    // PARÁMETROS:
    //  - comentario (E): comentario original
    //  - procesado (S): comentario procesado (limpio)
    void procesarComentario(const string &comentario, string &procesado)
    {
        procesado = comentario;

        while (!procesado.empty() && procesado[0] == ' ')
        {
            procesado.erase(0, 1);
        }

        while (!procesado.empty() && procesado.back() == ' ')
        {
            procesado.pop_back();
        }

        unsigned i = 0;
        while (i < procesado.size())
        {
            if (!ispunct(procesado[i]))
            {
                if (procesado[i] == ' ')
                {
                    if (i > 0 && procesado[i - 1] == ' ')
                    {
                        procesado.erase(i, 1);
                    }
                    else
                    {
                        i++;
                    }
                }
                else
                {
                    procesado[i] = tolower(procesado[i]);
                    i++;
                }
            }
            else
            {
                procesado.erase(i, 1);
            }
        }
    }

} // namespace

// ----------------------------------------------

namespace bblProg2
{
    // ---------- OPERADORES SOBRECARGADOS (IMPLEMENTADOS POR EL PROFESORADO)

    // Operador de comparación de igualdad (necesario para las pruebas unitarios)
    bool Valoracion::operator==(const Valoracion &otra_valoracion) const
    {
        return (id_alojamiento == otra_valoracion.id_alojamiento &&
                id_valoracion == otra_valoracion.id_valoracion &&
                fecha == otra_valoracion.fecha &&
                id_revisor == otra_valoracion.id_revisor &&
                nombre_revisor == otra_valoracion.nombre_revisor &&
                comentario == otra_valoracion.comentario &&
                sentimiento == otra_valoracion.sentimiento);
    }

    // -------------------------------------------------------------------

    // IMPLEMENTACIÓN DE LOS MÉTODOS PÚBLICOS Y PRIVADOS

        // Constructor por defecto.
        // Inicializa todos los atributos a sus valores por defecto
        Valoracion::Valoracion(): id_alojamiento{}, id_valoracion{}, fecha{}, id_revisor{}, nombre_revisor{}, comentario{}, sentimiento{} {}

        // Constructor de copia
        Valoracion::Valoracion(const Valoracion &otra_valoracion): id_alojamiento{otra_valoracion.consultarIdAlojamiento()}, id_valoracion{otra_valoracion.consultarIdValoracion()}, fecha{otra_valoracion.consultarFecha()}, id_revisor{otra_valoracion.consultarIdRevisor()}, nombre_revisor{otra_valoracion.consultarNombreRevisor()}, comentario{otra_valoracion.consultarComentarios()}, sentimiento{otra_valoracion.consultarSentimiento()} {}

        // Constructor específico.
        // Inicializa los atributos según los parámetros correspondientes.
        // Parámetros:
        //  - id_alo (E): identificador del alojamiento
        //  - id_val (E): identificador de la valoración
        //  - fec (E): fecha de la valoración (formato AAAA-MM-DD)
        //  - id_rev (E): identificador del revisor
        //  - nom_rev (E): nombre del revisor
        //  - comments (E): la valoración (comentarios)
        //  - sent (E): sentimiento de la valoración
        // PRECONDICIONES:
        //  - La fecha tiene formato correcto (AAAA-MM-DD)
        //  - 'nom_rev' no es una cadena vacía
        //  - 'comments' no es una cadena vacía
        Valoracion::Valoracion(unsigned id_alo,
                unsigned id_val,
                const std::string &fec,
                unsigned id_rev,
                const std::string &nom_rev,
                const std::string &comments,
                Sentimiento sent): id_alojamiento{id_alo}, id_valoracion{id_val}, fecha{fec}, id_revisor{id_rev}, nombre_revisor{nom_rev}, comentario{comments}, sentimiento{sent} {}

        // Destructor
        Valoracion::~Valoracion() {}

        // ----------------- MÉTODOS DE ASIGNACIÓN

        // Asigna el identificador del alojamiento
        // Parámetros:
        //  - id_alo (E): identificador del alojamiento
        void Valoracion::asignarIdAlojamiento(unsigned id_alo) {
            id_alojamiento=id_alo;
        }

        // Asigna el identificador de la valoración
        // Parámetros:
        //  - id_val (E): identificador de la valoración
        void Valoracion::asignarIdValoracion(unsigned id_val) {
            id_valoracion=id_val;
        }

        // Asigna fecha
        // Parámetros:
        //  - fec (E): fecha de la valoración
        // PRECONDICIÓN:
        //  - la fecha tiene formato correcto (AAAA-MM-DD)
        void Valoracion::asignarFecha(const std::string &fec) {
            bool cond=true;
            for(unsigned i=0; cond && i<fec.size(); ++i) {
                if(i!=4 && i!=7) {
                    cond=fec[i]>='0' && fec[i]<='9';
                }
            }
            cond=cond && (fec[4]=='-' && fec[7]=='-');
            assert(cond); // Se verifica el formato de la fecha
            fecha=fec;
        }

        // Asigna el identificador del revisor
        // Parámetros:
        //  - id_rev (E): identificador del revisor
        void Valoracion::asignarIdRevisor(unsigned id_rev) {
            id_revisor=id_rev;
        }

        // Asigna el nombre del revisor
        // Parámetros:
        //  - nom_rev (E): nombre del revisor
        // PRECONDICIÓN:
        //  - la cadena no está vacía
        void Valoracion::asignarNombreRevisor(const std::string &nom_rev) {
            assert(!nom_rev.empty());
            nombre_revisor=nom_rev;
        }

        // Asigna la valoración (comentario) al alojamiento
        // Parámetros:
        //  - comment (E): valoración (comentario)
        void Valoracion::asignarComentarios(const std::string &comments) {
            comentario=comments;
        }

        // Asigna un valor (positivo, negativo, neutro) al
        // sentimiento de la valoración
        // Parámetros:
        //  - sent (E): sentimiento de la valoración
        void Valoracion::asignarSentimiento(Sentimiento sent) {
            sentimiento=sent;
        }

        // Analiza y devuelve el sentimiento de la valoración.
        // Para ello:
        // 1) Cuenta cuántas palabras positivas y negativas hay en el comentario
        //    de la valoracion, a partir de las listas de palabras positivas y negativas
        //    que se reciben como parámetro.
        // 2) Si el número de palabras positivas supera (es mayor) en un determinado umbral
        //    al número de palabras negativas, se asigna sentimiento positivo a la valoración,
        // 3) si no, si el número de palabras negativas supera (es mayor) en un determinado umbral
        //    al número de palabras positivas, se asigna sentimiento negativo a la valoración,
        // 4) si no, se asigna sentimiento neutro a la valoración.
        //
        // El comentario debe preprocesarse antes de ser clasificado, para 1) eliminar
        // los signos de puntuación que contiene, 2) eliminar espacios repetidos, eliminar
        // todos los espacios que haya al principio o al final del comentario, y
        // 3) convertir todas las letras en minúsculas. Para ello, puede usarse la
        // función auxiliar 'procesarComentario'.
        // Parámetros:
        //  - pal_pos (E): lista de palabras positivas
        //  - pal_neg (E): lista de palabras negativas
        //  - umbral (E): umbral para la determinación del sentimiento
        //  - sent (S): sentimiento de la valoración
        void Valoracion::analizarSentimiento(const Palabras &pal_pos, const Palabras &pal_neg, unsigned umbral, Sentimiento &sent) const {
            string procesado;
            unsigned cont_pos=0, cont_neg=0;
            procesarComentario(comentario, procesado);
            for(unsigned i=0; i<pal_pos.numPalabras(); ++i) { // Para palabras positivas
                unsigned pos=0;
                pos=procesado.find(pal_pos[i], pos);
                while(pos!=string::npos) {
                    ++cont_pos; // Se incrementa el contador cada vez que se encuentre una palabra positiva
                    pos+=pal_pos[i].size(); // Se restringe la posición a partir de la que buscar, a partir de la última palabra encontrada (por si se repite)
                    pos=procesado.find(pal_pos[i], pos);
                }
            }
            for(unsigned i=0; i<pal_neg.numPalabras(); ++i) { // Para palabras negativas
                unsigned pos=0;
                pos=procesado.find(pal_neg[i], pos);
                while(pos!=string::npos) {
                    ++cont_neg;
                    pos+=pal_neg[i].size();
                    pos=procesado.find(pal_neg[i], pos);
                }
            }
            if(cont_pos>cont_neg+umbral) {
                sent=positivo;
            }
            else if(cont_neg>cont_pos+umbral) {
                sent=negativo;
            }
            else {
                sent=neutro;
            }
        }

        // ----------------- MÉTODOS DE CONSULTA

        // Consulta el id del alojamiento
        unsigned Valoracion::consultarIdAlojamiento() const {
            return id_alojamiento;
        }

        // Consulta el id de la valoración
        unsigned Valoracion::consultarIdValoracion() const {
            return id_valoracion;
        }

        // Consulta el id del revisor
        unsigned Valoracion::consultarIdRevisor() const {
            return id_revisor;
        }

        // Consulta el nombre del revisor
        std::string Valoracion::consultarNombreRevisor() const {
            return nombre_revisor;
        }

        // Consulta la fecha de la valoración
        std::string Valoracion::consultarFecha() const {
            return fecha;
        }

        // Consulta la valoración (comentarios) del alojamiento
        std::string Valoracion::consultarComentarios() const {
            return comentario;
        }

        // Consulta el sentimiento de la varloración
        Valoracion::Sentimiento Valoracion::consultarSentimiento() const {
            return sentimiento;
        }

        // Escribe por pantalla los datos de la valoración,
        // en el siguiente formato (nótese que se
        // usan tabuladores para formatear la salida):
        //  ID alojamiento:      <id_alojamiento>
        //  ID valoración:       <id_alojamiento>
        //  Fecha:               <fecha>
        //  ID revisor:          <id_revisor>
        //  Nombre revisor:      <nombre_revisor>
        //  --- COMENTARIO:
        //  <comentario>
        //  *** SENTIMIENTO: positivo/negativo/neutro
        void Valoracion::escribir() const {
            cout<<"ID alojamiento:"<<'\t'<<id_alojamiento<<endl;
            cout<<"ID valoración:"<<'\t'<<id_valoracion<<endl;
            cout<<"Fecha:"<<'\t'<<fecha<<endl;
            cout<<"ID revisor:"<<'\t'<<id_revisor<<endl;
            cout<<"Nombre revisor:"<<'\t'<<nombre_revisor<<endl;
            cout<<"--- COMENTARIO:"<<endl<<comentario<<endl;
            cout<<"*** SENTIMIENTO: "; escribirSentimiento(sentimiento); cout<<endl;
        }
} // namespace bblProg2
