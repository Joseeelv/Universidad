/*2. Escriba una función que dada una cola y dos elementos ay b, invierta la secuencia deli-
mitada por ambos dentro de ella.
Dado que la cola puede tener elementos repetidos, se invertirá la secuencia delimitada por
la primera ocurrencia de a y b.*/

#include <iostream>
#include "ejercicio2.h"
using namespace std;

ColaD<int>Invertir(ColaD<int>cola, int inicio, int fin){
    PilaD<int> pila;
    ColaD<int> CAUX;

    //La cola auxiliar recoge los elementos de la cola si esta no está vacia y el frente es distinto del inicio
    while(!cola.vacia && cola.frente != inicio){
        CAUX.push(cola.frente());
        cola.pop();
    }
    //La pila recoge los elementos de la cola que están al frente mientras este no sea el fin de la cola
    while(!cola.vacia && cola.frente!=fin){
        pila.push(cola.frente);
        cola.pop();
    }
    //introducimos elementos en la pila que esta al frente de la cola y eliminamos un elemento
    pila.push(cola.frente());
    cola.pop();

    while(!pila.vacia()){
        CAUX.push(pila.pop());
    }

    while(!cola.vacia()){
        CAUX.push(cola.frente());
        cola.pop();
    }

    //eliminamos la cola auxilar llamando al destructor

    CAUX.~ColaD();
    return cola; //devolvemos la cola actualizada
}