/*1. Se dice que una pila es isomórfica a una cola cuando los elementos situados en posiciones
pares de la pila coinciden con los situados en posiciones impares de la cola.
Usando los TAD Pila y Cola, implemente una función que determine y devuelva si una
pila y una cola dadas son isomórficas o no.*/

#include <iostream>
#include "ejercicio1.h"
using namespace std;


bool pilaisomorfica(PilaD<int> p,ColaD<int> c){

    bool res=1; //verdadero
    PilaD<int> Paux;
    ColaD<int> Caux;

    //cargamos en las estructuras auxiliares los elementos de las estructuras
    while(!p.vacia){
        Paux.push(p.pop());
    }

    while(!c.vacia){
        Caux.push(c.pop);
    }

    //comprobamos que los elementos pares de cada estructura coinciden, si es así es isomorfica

    while(res && !c.vacia() && !Caux.vacia()){
        c.pop();//sacamos un elemento de la cola
        if(Caux.frente == c.frente()){
            c.pop(); 
            Caux.pop();
            Caux.pop();
        }
        else res = 0; //falso
    }

    return res;
}