#include <iostream>
#include "../Árboles/abin.h"
/*Nodos Franquistas: Te cargas SOLO los hijos izquierdos de cada NODO. Si te queda un hijo derecho de un hijo izquierdo lo mueves arriba*/

template <typename T>
void NodosFranquistas(const Abin<T> &A){
  if(!A.arbolVacio()){
    NodosFranquistas_rec(A.raiz(),A);
  }
}

//método auxiliar que me va a permitir eliminar un nodo
template <typename T>
bool esHoja(typename Abin<T>::nodo n, const Abin<T> &A){
  return (A.hijoIzqdo(n) == Abin<T>::NODO_NULO && A.hijoDrcho(n) == Abin<T>::NODO_NULO);
}

template <typename T>
void NodosFranquistas_rec(typename Abin<T>::nodo n, Abin<T> &A){
  if(n != Abin<T>::NODO_NULO){
    if(esHoja(n,A)){
      //para eliminar el nodo, tenemos que hacerlo llamando al padre, pero solamente eliminamos al hijo izquierdo
      typename Abin<T>::nodo padre = A.padre(n);
      if(n == A.hijoIzqdo(padre)){
        A.eliminarHijoIzqdo(padre);
        A.eliminarHijoDrcho(padre);
      } 
    }
      NodosFranquistas_rec(A.hijoIzqdo(n),A);
      NodosFranquistas_rec(A.hijoDrcho(n),A);
  }
}