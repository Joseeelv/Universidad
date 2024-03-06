//Las operaciones primitivas de este TAD son las siguientes:

#include "polinom.h"
#ifndef __POLINOMIO__H__
#define __POLINOMIO__H__

//creamos la clase polinomio

class polinomio
{
public:
    //Postcondiciones: Crea el polinomio nulo. El objetivo de este método es crear un objeto polinomio, 
    //reservando el espacio necesario e inicializando con el valor nulo.
        polinomio(unsigned gradoMax);

    //Postcondiciones: Devuelve el grado de un polinomio
        unsigned grado() const;

    //Postcondiciones: Devuelve el coeficiente correspondiente al monomio de grado n de un polinomio.
    // Si n > gradoMax, devuelve 0.
        double coeficiente(unsigned n) const;

    //Precondiciones: n ≤ gradoMax 
    //Postcondiciones: Asigna al monomio de grado n el coeficiente c.
        void coeficiente (unsigned n, double c);

    //Imprime por pantalla el polinomio
        void imprime () const;

    //-----------------Sobrecarga de los operadores "Ejercicio 1------------
        friend polinomio operator + (const polinomio& p1, const polinomio& p2);
        friend polinomio operator - (const polinomio& p1, const polinomio& p2);
        friend polinomio operator * (const polinomio& p1, const polinomio& p2);

private:
    unsigned gMax; //guarda el grado maximo que el polinomio puede alcanzar
    unsigned monomio; //guarda el numero de monomios que forman parte del polinomio
    double *coef; //puntero a los coeficientes de cada monomio "ax^n"    
};

#endif