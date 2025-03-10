//Se dice de nodo rebelde aquel cuyas ideas son diferentes a la de la mayoría de sus ancestros.
// Dado un árbol binario cualquiera calcular el número de nodos rebeldes de dicho árbol.
//Es decir, un nodo es rebelde si su elemento es distinto al de su padre

#include <iostream>
#include "../Árboles/Abin.h"

template <typename T>
size_t NodosRebeldes(const Abin<T> &A){
  if(A.arbolVacio())
    return 0;
  else{
    return NodosRebeldes_rec(A.raiz(),A);
  }
}

template <typename T>
size_t NodosRebeldes_rec(typename Abin<T>::nodo n, const Abin<T> &A){
  if(n == Abin<T>::NODO_NULO) return 0;
  else{
    //Creamos un nodo auxiliar
    typename Abin<T>::nodo padre = A.padre(n);
    if(padre != Abin<T>::NODO_NULO && A.elemento(n) != A.elemento(padre))
      return 1+NodosRebeldes_rec(A.hijoIzqdo(n),A) + NodosRebeldes_rec(A.hijoDrcho(n),A);
    else 
      return 0+NodosRebeldes_rec(A.hijoIzqdo(n),A) + NodosRebeldes_rec(A.hijoDrcho(n),A);
  }
}