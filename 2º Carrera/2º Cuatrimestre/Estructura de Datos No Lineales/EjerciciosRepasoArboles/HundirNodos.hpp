/*Dado un elemento, buscar el nodo con dicho elemento y hundirlo, cuando sea hoja se elimina*/

#include <iostream>
#include "../Árboles/abin.h"

template <typename T>
void HundirNodo(const T& elto, Abin<T> &A){
  //Nos creamos un nodo auxiliar que usaremos para intercambiarlo por el nodo a hundir
  typename Abin<T>::nodo aux = Abin<T>::NODO_NULO;
  //Primero tenemos que buscar el nodo que concuerde con el elemento a eliminar
  if(BuscarElto(A.raiz(),elto, aux, A)){
    HundirNodo_rec(aux,A);
  }
}

//Método que nos devuelve el nodo que contiene el elemento elto
template <typename T>
bool BuscarElto(typename Abin<T>::nodo n, const T& elto, typename Abin<T>::nodo &encontrado, const Abin<T> &A){
  if(n == Abin<T>::NODO_NULO)
    return false;
  else{
    if(A.elemento(n) == elto)
      encontrado = n;
      return true;
    else{
      //Seguimos buscando
      return BuscarElto(A.hijoIzqdo(n),elto,encontrado,A) || BuscarElto(A.hijoDrcho(n),elto,encontrado,A);
    }
  }
}

//Método que nos comprueba si el nodo es hoja o no
template <typename T>
bool EsHoja(typename Abin<T>::nodo n, const Abin<T> &A){
  return (A.hijoIzqdo(n) == Abin<T>::NODO_NULO && A.hijoDrcho(n) == Abin<T>::NODO_NULO);
}

template <typename T>
void HundirNodo_rec(typename Abin<T>::nodo n, Abin<T>& A){
  if(n != Abin<T>::NODO_NULO){
    if(EsHoja(n,A)){//Si es hoja lo eliminamos
      if(A.elemento(n) == A.elemento(A.hijoIzqdo(A.padre(n)))){
        A.eliminarHijoIzqdo(A.padre(n));
      }
      else if(A.elemento(n) == A.elemento(A.hijoDrcho(A.padre(n)))){
        A.eliminarHijoDrcho(A.padre(n));
      }
    }else{
    //Si no es hoja, seguimos hundiendo el nodo
      T elto_auxiliar;
      if(A.hijoIzqdo(n) != Abin<T>::NODO_NULO){ //Si mi hijo izquierdo existe, intercambio por él
      //Se puede hacer un método "intercambio", que realice esto mismo.
      elto_auxiliar = A.elemento(A.hijoIzqdo(n));
      A.elemento(A.hijoIzqdo(n)) = A.elemento(n);
      A.elemento(n) = elto_auxiliar;
      HundirNodo_rec(A.hijoIzqdo(n),A);
      }
      else if(A.hijoIzqdo(n) == Abin<T>::NODO_NULO && A.hijoDrcho(n) != Abin<T>::NODO_NULO){
        //Si no tengo hijos izquierdo pero tengo hijo derecho, hacemos lo mismo
        elto_auxiliar = A.elemento(A.hijoDrcho(n));
        A.elemento(A.hijoDrcho(n)) = A.elemento(n);
        A.elemento(n) = elto_auxiliar;
        HundirNodo_rec(A.hijoDrcho(n),A);
      }
    }
  }
}