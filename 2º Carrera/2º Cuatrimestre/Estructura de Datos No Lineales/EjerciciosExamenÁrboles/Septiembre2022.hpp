/*Construye una función que, dado un Árbol Binario, devuelva true si es un AVL y false en el caso contrario.*/
#include <iostream>
#include "../Árboles/abin.h"

//Para que un abin sea un AVL, este tiene que ser un ABB y estar equilibrado.

template <typename T>
bool esAVL(const Abin<T> &A){
  bool flag = esABB(A.raiz(),A); //Primero comprobamos si es un ABB
  flag &= esAVL_rec(A.raiz(),A); //Luego comprobamos si está equilibrado
  return flag;
}


//Método que nos comprueba si un nodo es hoja o no
template <typename T>
bool esHoja(typename Abin<T>::nodo n, const Abin<T> &A){
  return (A.hijoIzqdo(n) == Abin<T>::NODO_NULO && A.hijoDrcho(n) == Abin<T>::NODO_NULO);
}
//Metodo que nos comprueba si es una ABB
template <typename T>
bool esABB(typename Abin<T>::nodo n, const Abin<T> &A){
  if(n == Abin<T>::NODO_NULO) return true;
  else{
    //Para que un Abin sea un ABB, los elementos de los hijos tienen que ser menores a los elementos del padre
    if(!esHoja(n,A)){
      return (A.elemento(n) > A.elemento(A.hijoIzqdo(n)) && A.elemento(n) < A.elemento(A.hijoDrcho(n))
              && esABB(A.hijoIzqdo(n),A) && esABB(A.hijoDrcho(n),A));
    }
    if(A.hijoIzqdo(n)!= Abin<T>::NODO_NULO && A.hijoDrcho(n) == Abin<T>::NODO_NULO){
      return (A.elemento(n) > A.elemento(A.hijoIzqdo(n)) && esABB(A.hijoIzqdo(n),A) && esABB(A.hijoDrcho(n),A));
    }
    if(A.hijoIzqdo(n)== Abin<T>::NODO_NULO && A.hijoDrcho(n) != Abin<T>::NODO_NULO){
      return (A.elemento(n) < A.elemento(A.hijoDrcho(n)) && esABB(A.hijoIzqdo(n),A) && esABB(A.hijoDrcho(n),A));
    }
    else{ //esHoja(n,A);
      return true;
    }
  }
}

//Para saber si es equilibrado, vamos a comprobar si la diferencia de las alturas de los subárboles del nodo n es <= 1
template <typename T>
size_t altura(typename Abin<T>::nodo n, const Abin<T> &A){
  if(n == Abin<T>::NODO_NULO) return 0;
  else{
    return 1 + std::max(altura(A.hijoIzqdo(n),A),altura(A.hijoDrcho(n),A));
  }
}

//Comprobamos si está equilibrado o no
template <typename T>
bool esAVL_rec(typename Abin<T>::nodo n, const Abin<T> &A){
  if(n == Abin<T>::NODO_NULO) return true;

  size_t factor_desequilibrio = abs(altura(A.hijoIzqdo(n),A) - altura(A.hijoDrcho(n),A));

  return factor_desequilibrio <= 1 && esAVL_rec(A.hijoIzqdo(n),A) && esAVL_rec(A.hijoDrcho(n),A);
}

// //Comprobamos si está equilibrado o no
// template <typename T>
// bool esAVL_rec(typename Abin<T>::nodo n, const Abin<T> &A){
//   if(n == Abin<T>::NODO_NULO) return true;
//   else{
//     size_t factor_desequilibrio = abs(altura(A.hijoIzqdo(n),A) - altura(A.hijoDrcho(n),A));
//     //Tenemos ambos subárboles
//     if(!EsHoja(n,A)){
//       return(factor_desequilibrio <= 1 && EsAVL_rec(A.hijoIzqdo(n),A) && EsAVL_rec(A.hijoDrcho(n),A));
//     }
//     //Solo tiene subárbol izquierdo
//     if(A.hijoIzqdo(n) != Abin<T>::NODO_NULO && A.hijoDrch(n) == Abin<T>::NODO_NULO){
//       return (factor_desequilibrio <= 1 && EsAVL_rec(A.hijoIzqdo(n),A));
//     }
//     //Solo tiene subárbol derecho
//     if(A.hijoIzqdo(n) == Abin<T>::NODO_NULO && A.hijoDrcho(n) != Abin<T>::NODO_NULO){
//       return (factor_desequilibrio <= 1 && EsAVL_rec(A.hijoDrcho(n),A));
//     }
//     //Es una hoja
//     else return true;
//   }
// }