#include <iostream>
#include "../Árboles/abin.h"
#include "../Árboles/agen.h"

// Un nodo verde es aquel nodo que cumple una cierta codición, por ejemplo en este caso, nuestra condición es aquel que tiene estrictamente 3 nietos:

//--------------------------------------------------Mediante un ÁRBOL BINARIO--------------------------------------------------
template <typename T>
typename Abin<T>::nodo DosHijos(typename Abin<T>::nodo n, const Abin<T> &A)
{
  return (A.hijoIzqdo(n) != Abin<T>::NODO_NULO && A.hijoDrcho(n) != Abin<T>::NODO_NULO);
}

template <typename T>
size_t TresNietosAbin(typename Abin<T>::nodo n, const Abin<T> &A)
{
  if (DosHijos(n, A))
  { // Condición necesaria que tenga 3 nietos
    size_t nietos = 0;
    if (A.hijoIzqdo(A.hijoIzqdo(n)) != Abin<T>::NODO_NULO)
      nietos++;
    if (A.hijoIzqdo(A.hijoDrcho(n)) != Abin<T>::NODO_NULO)
      nietos++;
    if (A.hijoDrcho(A.hijoIzqdo(n)) != Abin<T>::NODO_NULO)
      nietos++;
    if (A.hijoDrcho(A.hijoDrcho(n)) != Abin<T>::NODO_NULO)
      nietos++;
    return nietos; // devolvemos el número de nietos
  }
  return 0;
}

template <typename T>
size_t ContarNodosVerdesAbin(const Abin<T> &A)
{
  return ContarNodosVerdesAbin_rec(A.raiz(), A);
}

template <typename T>
size_t ContarNodosVerdesAbin_rec(typename Abin<T>::nodo n, const Abin<T> &A)
{
  if (n == Abin<T>::NODO_NULO)
    return 0;
  // Solamente vamos a tener en cuenta los nodos que tengan 3 nietos;
  else if (TresNietosAbin(n, A) == 3)
  {
    return 1 + ContarNodosVerdesAbin_rec(A.hijoIzqdo(n), A) + ContarNodosVerdesAbin_rec(A.hijoDrcho(n), A);
  }
  else
  {
    return 0 + ContarNodosVerdesAbin_rec(A.hijoIzqdo(n), A) + ContarNodosVerdesAbin_rec(A.hijoDrcho(n), A);
  }
}

//--------------------------------------------------Mediante un ÁRBOL GENERAL--------------------------------------------------

template <typename T>
size_t TresNietosAgen(typename Agen<T>::nodo n, const Agen<T> &A)
{
  size_t nietos = 0;
  typename Agen<T>::nodo hijo = A.hijoIzqdo(n);
  while (hijo != Agen<T>::NODO_NULO)
  { // recorremos los hijos de n
    typename Agen<T>::nodo nieto = A.hijoIzqdo(hijo);
    while (nieto != Agen<T>::NODO_NULO)
    { // recorremos los nietos de n
      // Recorremos sus hermanos
      nietos++;
      hijo = A.hermDrcho(nieto);
    }
    hijo = A.hijoIzqdo(nieto);
  }
  return nietos;
}

template <typename T>
size_t ContarNodosVerdesAgen(const Agen<T> &A)
{
  return ContarNodosVerdesAgen_rec(A.raiz(), A);
}

template <typename T>
size_t ContarNodosVerdesAgen_rec(typename Agen<T>::nodo n, const Agen<T> &A)
{
  if (n != Agen<T>::NODO_NULO)
    return 0;
  else
  {
    typename Agen<T>::nodo hijo = A.hijoIzqdo(n);
    size_t contadorNodos = 0;
    while (hijo != Agen<T>::NODO_NULO)
    {
      if (TresNietosAgen(n, A) == 3)
        contadorNodos += 1 + ContarNodosVerdesAgen_rec(hijo, A);
      else
        contadorNodos += 0 + ContarNodosVerdesAgen_rec(hijo, A);
      hijo = A.hermDrcho(hijo);
    }
    return contadorNodos;
  }
}