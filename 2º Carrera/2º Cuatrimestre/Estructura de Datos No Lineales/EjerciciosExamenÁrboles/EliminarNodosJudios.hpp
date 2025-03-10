/*Si encontramos un nodo judío eliminamos a sus descendientes y a él mismo*/
/*Leyenda -> J (nodo judio), N (nodo nazi)*/
#include <iostream>
#include "../Árboles/Agen.h"

template <typename T>
void EliminarNodosJudios(Agen<T> &A){
  EliminarNodosJudios_rec(A.raiz(),A);
}
template <typename T>
void EliminarNodosJudios_rec(typename Agen<T>::nodo n, Agen<T> &A){
  if(n!= Agen<T>::NODO_NULO){
    //vamos a recorrer el agen y eliminar sus hijos y hermanos
    if(A.elemento(n) == "J"){
      typename Agen<T>::nodo hijo = A.hijoIzqdo(n);
      while(hijo != Agen<T>::NODO_NULO){
          EliminarNodosJudios_rec(hijo,A);
          hijo = A.hermDrcho(hijo);
      }
    //ahora nos vamos a eliminar a los descendientes y al propio nodo J
      typename Agen<T>::nodo padre = A.padre(n);
      if(padre != Agen<T>::NODO_NULO){
        if(n == A.hijoIzqdo(padre)){
          A.eliminarHijoIzqdo(padre);
        }else{ //recorremos la lista de hermanos
          typename Agen<T>::nodo hijo = A.hijoIzqdo(padre);
          while(A.hermDrcho(hijo) != n){
            hijo = A.hermDrcho(hijo);
          }
          A.eliminarHermDrcho(hijo);
        }
      }else if(n == A.raiz()){
        A.eliminarRaiz();
      }
    }else{
      //Si no es "J", procedemos con los hijos
      typename Agen<T>::nodo hijo = A.hijoIzqdo(n);
      while (hijo != Agen<T>::NODO_NULO) {
        EliminarNodosJudios_rec(hijo, A);
        hijo = A.hermDrcho(hijo);
      }
    }
  } 
}