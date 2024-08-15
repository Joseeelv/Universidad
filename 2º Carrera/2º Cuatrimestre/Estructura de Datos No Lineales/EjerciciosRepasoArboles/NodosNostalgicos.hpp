//Son aquellos nodos que tienen más ancestros que descendientes.

#include <iostream>
#include "../Árboles/Agen.h"

template <typename T>
bool nostalgico(typename Agen<T>::nodo n, const Agen<T> &A){
  if(n == Agen<T>::NODO_NULO){
    return false; 
  }
  return (NumAncestros(n,A) > NumDescendientes(n,A)); //devolvemos True si número de ancestros > número de descendientes
}

template <typename T>
size_t NumAncestros(typename Agen<T>::nodo n, const Agen<T> &A){
  if(A.padre(n) == Agen<T>::NODO_NULO) return 0;
  else
    return 1 + NumAncestros(A.padre(n),A);
}

template <typename T>
size_t NumDescendientes(typename Agen<T>::nodo n, const Agen<T> &A){
  if(n == Agen<T>::NODO_NULO) return 0;
  else{
    //vamos a recorrer la lista de hijos y hermanos
    typename Agen<T>::nodo hijo = A.hijoIzqdo(n);
    size_t nhijos = 0;
    while(hijo != Agen<T>::NODO_NULO){
      nhijos += 1 + NumDescendientes(hijo,A);
      hijo = A.hermDrcho(hijo);
    }
    return nhijos;
  }
}