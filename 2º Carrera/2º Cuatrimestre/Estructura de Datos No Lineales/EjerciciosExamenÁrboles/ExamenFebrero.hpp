/*Implementa una función genérica que transforme un árbol binario de un tipo genérico T, eliminando los descendientes propios de todo aquellos nodos cuyo contenido sea, al mismo tiempo, mayor o igual que el de sus ascendientes propios y menor o igual que el de sus descendientes propios.
 */

#include <iostream>
#include "../Árboles/abin.h"

// Llamada a la función recursiva que nos eliminará los nodos hijos.
template <typename T>
void eliminar_descendientes(Abin<T> &A)
{
  if (!A.arbolVacio())
  {
    eliminar_descendientes_rec(A.raiz(), A);
  }
}

// Función auxiliar que nos comprueba si es hoja o no para poder eliminar
template <typename T>
bool esHoja(typename Abin<T>::nodo n, const Abin<T> &A)
{
  return (A.hijoIzqdo(n) == Abin<T>::NODO_NULO && A.hijoDrcho(n) == Abin<T>::NODO_NULO);
}

// Función que comprueba si su valor es mayor que el de su padre
template <typename T>
bool Mayor_Ancestro(typename Abin<T>::nodo n, const Abin<T> &A)
{
  if (n == Abin<T>::NODO_NULO)
    return true;
  else
    return (A.elemento(n) >= A.elemento(A.padre(n)))
}

// Función que nos comprueba si su valor es menor que el de todos sus descendientes propios (hijos).
template <typename T>
bool Menor_Descendiente(typename Abin<T>::nodo n, const Abin<T> &A)
{
  if (n == Abin<T>::NODO_NULO)
    return true;
  else
    return (A.elemento(n) <= A.elemento(A.hijoIzqdo(n)) && A.elemento(n) <= A.elemento(A.hijoDrcho(n));
}

// Función que nos intercambie los nodos, para poder eliminarlos (que sean hojas)
template <typename T>
void swapeo(typename Abin<T>::nodo n, Abin<T> &A)
{
  if (n != Abin<T>::NODO_NULO)
  {
    // Vamos a intercambiar por defecto por el Hijo izquierdo y si este no existe, por el hijo derecho
    // Creamos un elemento auxiliar para realizar el intercambio
    if (A.hijoIzqdo(n) != Abin<T>::NODO_NULO)
    { // Si existe Hijo izquierdo, intercambiamos por él
      // intercambiamos los nodos
      T elemento_intercambio = A.elemento(n);
      A.elemento(n) = A.elemento(A.hijoIzqdo(n));
      A.elemento(A.hijoIzqdo(n)) = elemento_intercambio;
      swapeo(A.hijoIzqdo(n), A);
    }
    else if (A.hijoDrcho(n) != Abin<T>::NODO_NULO)
    {
      T elemento_intercambio = A.elemento(n);
      A.elemento(n) = A.elemento(A.hijoDrcho(n));
      A.elemento(A.hijoDrcho(n)) = elemento_intercambio;
      swapeo(A.hijoDrcho(n), A);
    }
  }
  else
  {
    if (A.hijoIzqdo(A.padre(n)) == n)
      A.eliminarHijoIzqdo(A.padre(n));
    else
      A.eliminarHijoDrcho(A.padre(n));
  }
}

// Función que recorre el Abin y va eliminando los descendientes que cumplen las dos condiciones
template <typename T>
void eliminar_descendientes_rec(typename Abin<T>::nodo n, Abin<T> &A)
{
  if (n != Abin<T>::NODO_NULO)
  {
    // Tenemos que comprobar que el nodo n cumple las dos condiciones para poder eliminar sus hijos
    if (!esHoja(n, A))
    { // tiene hijos los cuales hay que eliminar
      if (Mayor_Ancestro(n, A) && Menor_Descendiente(n, A))
      {
        if (!esHoja(A.hijoIzqdo(n), A)) // Si no es hoja el hijo izquierdo, hay que intercambiarlo hasta que sea una hoja
          swapeo(A.hijoIzqdo(n), A);
        else
          A.eliminarHijoIzqdo(n);

        if (!esHoja(A.hijoDrcho(n), A))
          swapeo(A.hijoDrcho(n), A);
        else
          A.eliminarHijoDrcho(n);
      }
    }
    // Sigo buscando
    eliminar_descendientes_rec(A.hijoIzqdo(n), A);
    eliminar_descendientes_rec(A.hijoDrcho(n), A);
  }
}