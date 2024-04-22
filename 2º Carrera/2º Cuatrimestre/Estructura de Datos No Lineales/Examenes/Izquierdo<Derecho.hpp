// Dado un árbol A, comprobar que todos los valores del subárbol izquierdo,
// son estrictamente menores que los valores del nodo raíz de A y,
// todos los valores del subárbol derecho, estrictamente mayores.
// Dicha condición se debe dar de igual modo en dichos subárboles.

#include <iostream>
#include "../Prácticas/Árboles/abin.h"

template <typename T>
bool menor(Abin<T> A){
    return menor_rec(A.raiz(),A);
}

template <typename T>
bool menor_rec(typename Abin<T>::nodo n, Abin<T> A){
    if(n!=Abin<T>::NODO_NULO){
        if(A.elemento(A.hijoIzqdo(n)) < A.elemento(A.hijoDrcho(n))){
            return menor_rec(A.hijoIzqdo(n),A);
            return menor_rec(A.hijoDrcho(n),A);
        }
        else{
            return false;
        }
        return true;
    }
}