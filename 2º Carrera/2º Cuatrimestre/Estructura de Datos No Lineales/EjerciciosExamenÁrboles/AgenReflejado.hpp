/*A partir de un árbol general, creamos otro intercambiando los subárboles del mismo.*/

#include <iostream>
#include "../Árboles/agen.h"

template <typename T>
Agen<T> AgenReflejado(const Agen<T>& A){
  //Creamos el nuevo árbol reflejado
  Agen<T> B;
  B.insertarRaiz(A.raiz());
  if(A.hijoIzqdo(A.raiz()) != Agen<T>::NODO_NULO){
    return AgenReflejado(A.raiz(),B.raiz(),A,B);
  }
  return B;
}

template <typename T>
void AgenReflejado(typename Agen<T>::nodo a, typename Agen<T>::nodo b, const Agen<T> &A, Agen<T> &B){
  if(a != Agen<T>::NODO_NULO){
    //Tenemos que ir insertando los hermanos de forma inversa
    typename Agen<T>::nodo aux = A.hijoIzqdo(a);
    while(aux != Agen<T>::NODO_NULO){
      B.insertarHijoIzqdo(b,A.elemento(aux)); //Si hay un hijo izq insertado, al insertar otro, el anterior pasa a ser hermano derecho
      AgenReflejado(aux,b,A,B);
      aux = A.hermDrcho(aux);
    }
  }
}