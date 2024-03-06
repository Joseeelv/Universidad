/*1. Escriba una función que determine y devuelva si una secuencia de caracteres de entrada es de la forma X&Y, donde X es una cadena de caracteres e Y es la cadena inversa,
separadas por el carácter ‘&*/

#include <iostream>
#include <stdlib.h>
#include "pilavec1.h"
#include <vector>
#include "pila_enla.h"
using namespace std;

bool cadena1(char *cadAux, int const tamcad){
    bool res=1;

    cout<<"Introduce una cadena de caracteres: ";
    cin >> cadAux;

    Pila<char> pila1;
    Pila<char> pila2;
    int i=0;
    while(i <=(tamcad-1)/2 && cadAux[i] != '&'){
        pila1.push(cadAux[i]);
        i++;
    }

    if(cadAux[i]=='&' && (i+i)<=tamcad){
        int j=i+i;
        while (j>=(i+i-1)/2 && cadAux[j] !='&'){
            pila2.push(cadAux[j]);
            j--;
        }
        i=(tamcad/2)+1;

        while (!pila1.vacia() && !pila2.vacia() && res!=0){
        if(pila1.pop() != pila2.pop()) res=0;
        i++;
        }
    } else res=0;

    pila1.~Pila();
    pila2.~Pila();
    return res;
}

