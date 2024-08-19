/*Dado un árbol A, comprobar que todos los valores del subárbol izquierdo son estrictamente menores que los valores del nodo raíz de A y todos los valores del subárbol derecho, estrictamente mayores.Dicha condición se debe dar de igual modo en dichos subárboles.*/

/*Parece que se puede hacer mediante un ABB, pero este ya nos lo daría hecho, por tanto, vamos a hacer uso de un Abin comprobando que los elementos de los hijosIzquierdo < HijoDerecho*/
#include <iostream>
#include "../Árboles/abin.h"

template <typename T>
bool menorsubarbol(const Abin<T> &A){
  if(!A.arbolVacio()){
    return menorsubarbol_rec(A.raiz(),A);
  }
  return true; //damos por hecho que si el árbol está vacío cumple la condición
}

template <typename T>
bool menorsubarbol_rec(typename Abin<T>::nodo n, const Abin<T> &A){
  if(n == Abin<T>::NODO_NULO) return true;

  if(A.hijoIzqdo(n) != Abin<T>::NODO_NULO && A.hijoDrcho(n) != Abin<T>::NODO_NULO){ //Tenemos ambos hijos
    if(A.elemento(A.hijoIzqdo(n)) < A.elemento(A.hijoDrcho(n)))
      return menorsubarbol_rec(A.hijoIzqdo(n),A) && menorsubarbol_rec(A.hijoDrcho(n),A);
    else
      return false; //hijo izquierdo es mayor o igual que el hijo derecho.
  }
  //Si solamente tiene el hijo derecho, devuelvo true porque un nodo que no existe siempre es menor que un nodo que tiene valor
  else if(A.hijoIzqdo(n) == Abin<T>::NODO_NULO && A.hijoDrcho(n) != Abin<T>::NODO_NULO){
    return menorsubarbol_rec(A.hijoDrcho(n), A);
  }
  else if (A.hijoIzqdo(n) != Abin<T>::NODO_NULO && A.hijoDrcho(n) == Abin<T>::NODO_NULO){
    return false; //en el caso de que tenga hijo izquierdo pero no derecho, el subárbol izquierdo > derecho
  }
  else{
    return true; //no tiene hijos, está vacío por lo que se cumple la condición 
  }
}