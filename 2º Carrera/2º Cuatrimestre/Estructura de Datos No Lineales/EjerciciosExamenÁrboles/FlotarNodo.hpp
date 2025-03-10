/*Dado un nodo cualquiera flotarlo hasta que se cumpla una condición. Por ejemplo, flotar un nodo hasta que el elemento del mismo sea mayor que el de su padre*/

#include <iostream>
#include "../Árboles/abin.h"

template <typename T>
void FlotarNodo(typename Abin<T>::nodo n, Abin<T> &A){
  if(n != Abin<T>::NODO_NULO && A.padre(n) != Abin<T>::NODO_NULO){
    //Dejamos de flotar el nodo cuando el elemento del padre es > que al del hijo
    if(A.elemento(n) < A.elemento(A.padre(n))){
      //realizamos el intercambio de nodos
      T elto_auxiliar = A.elemento(A.padre(n));
      A.padre(n) = A.elemento(n);
      A.elemento(n) = elto_auxiliar;
      FlotarNodo(A.hijoIzqdo(n),A); //Seguimos flotando
    }
    //Si el elemento del hijo > padre, termina
  }
  //Si es nulo, no se hace nada
}