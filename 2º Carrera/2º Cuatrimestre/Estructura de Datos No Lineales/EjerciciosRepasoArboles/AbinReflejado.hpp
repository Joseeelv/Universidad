/*A partir de un árbol binario, creamos otro intercambiando los subárboles del mismo.*/

#include <iostream>
#include "../Árboles/abin.h"

template <typename T>
Abin<T> AbinReflejado(const Abin<T> &A){
  //Nos creamos el árbol a devolver
  Abin<T> B;
  B.insertarRaiz(A.raiz()):
  if(!A.arbolVacio()){
    return AbinReflejado_rec(A.raiz(),B.raiz(),B,A);
  } 
  return B;
}

template <typename T>
void AbinReflejado_rec(typename Abin<T>::nodo a,typename Abin<T>::nodo b, Abin<T> &B, const Abin<T> &A){
  if(a != Abin<T>::NODO_NULO){
    if(A.hijoIzqdo(a) != Abin<T>::NODO_NULO)
      B.insertarHijoDrcho(b,A.elemento(A.hijoIzqdo(a)));
    AbinReflejado_rec(A.hijoIzqdo(a),B.hijoDrcho(b),B,A);
    
    if(A.hijoDrcho(a) != Abin<T>::NODO_NULO)
      B.insertarHijoIzqdo(b,A.elemento(A.hijoDrcho(a)));
    AbinReflejado_rec(A.hijoDrcho(a),B.hijoIzqdo(b),B,A);
  }
}