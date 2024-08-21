//Un arbol es perroflauta si tiene mas hijos izquierdos que derechos.

#include <iostream>
#include "../Árboles/Abin.h"

template <typename T>
bool perroflauta(const Abin<T> &A){
  if(!A.arbolVacio()){
    return perroflauta_rec(A.raiz(),A);
  }
}

//Función que calcula el numero de nodos hijos izquierdos y derechos
template <typename T>
size_t HijosI (typename Abin<T>::nodo n, const Abin<T> &A){
  if(n == Abin<T>::NODO_NULO) return 0;
  else if(A.hijoIzqdo(n) != Abin<T>::NODO_NULO)
      return 1 + HijosI(A.hijoIzqdo(n),A)+HijosI(A.hijoDrcho(n),A);
  else
    return HijosI(A.hijoDrcho(n),A);
}

template <typename T>
size_t HijosD (typename Abin<T>::nodo n, const Abin<T> &A){
  if(n == Abin<T>::NODO_NULO) return 0;
  else if(A.hijoDrcho(n) != Abin<T>::NODO_NULO)
    return 1 + HijosD(A.hijoIzqdo(n),A) + HijosD(A.hijoDrcho(n),A;
  else
    return HijosD(A.hijoIzqdo(n),A);
}

template <typename T>
bool perroflauta_rec(typename Abin<T>::nodo n, const Abin<T> &A){
  if(n == Abin<T>::NODO_NULO) return true;
  else{
    //Variables que nos irá guardando el número de hijos izquierdos y derechos que hay
    size_t hijosI = HijosI(A.raiz(),A),
           hijosD = HijosD(A.raiz(),A);
    return (hijosI > hijosD); //devuelve True si hijosI > hijosD, si no false.
  }
}