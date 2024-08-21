/*Árboles generales similares. Dos árboles generales son similares si tienen la misma estructura y el contenido de sus nodos hojas deben de ser el mismo*/

#include <iostream>
#include "../Árboles/agen.h"

template <typename T>
bool AgenSimilares(const Agen<T> &A, const Agen<T> &B){
  return AgenSimilares_rec(A.raiz(),B.raiz(),A,B);
}

//Metodo que nos comprueba si es una hoja
template <typename T>
bool EsHoja(typename Agen<T>::nodo n, const Agen<T> &A){
  return (A.hijoIzqdo(n)==Agen<T>::NODO_NULO);
}

//Método que nos calcula el número de hijos de un nodo
template <typename T>
size_t nHijos(typename Agen<T>::nodo n, const Agen<T> &A){
  if(n == Agen<T>::NODO_NULO) return 0;
  else{
    typename Agen<T>::nodo hijo = A.hijoIzqdo(n);
    size_t nodoshijos = 0;
    while(hijo != Agen<T>::NODO_NULO){
      nodoshijos ++;
      hijo = A.hermDrcho(hijo);
    }
    return nodoshijos;
  }
}

template <typename T>
bool AgenSimilares_rec(typename Agen<T>::nodo a, typename Agen<T>::nodo b, const Agen<T> &A, const Agen<T> &B){
  //Comprobamos si existen ambos nodos
  if(a == Agen<T>::NODO_NULO && b == Agen<T>::NODO_NULO)
    return true; //nodos iguales
  else if(a==Agen<T>::NODO_NULO || b == Agen<T>::NODO_NULO)
    return false; //nodos diferentes
  else if(EsHoja(a,A) && EsHoja(b,B)){ //comprobamos el contenido de las hojas
    if(A.elemento(a) == B.elemento(b)) return true;
    else return false;
  }
  else{
    //Ambos existen, vamos a comprobar la ramificación (el numero de hijos de un nodo)
    bool flag = nHijos(a,A) == nHijos(b,B);
    while(flag){ //Mientras que la flag sea True, vamos a ir comprobamos los hermanos de los nodos a y b
      flag &= AgenSimilares_rec(A.hijoIzqdo(a),B.hijoIzqdo(b),A,B);
      a = A.hermDrcho(a);
      b = A.hermDrcho(b);
    }
    return flag;
  }
}

