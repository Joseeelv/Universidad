#ifndef AGEN_E_S_H
#define AGEN_E_S_H

#include <cassert>
#include <iostream>
#include <fstream>

using std::cin;
using std::cout;
using std::endl;
using std::istream;
using std::ostream;

template <typename T>
void rellenarAgen(Agen<T> &A, const T &fin)
// Pre: A está vacío
// Post: Rellena A con elementos leídos en preorden desde entrada estándar.
{
  T e;
  assert(A.arbolVacio());
  cout << "Raíz (Fin = " << fin << "): ";
  cin >> e;
  if (e != fin)
  {
    A.insertarRaiz(e);
    rellenarDescendientes(A.raiz(), A, fin);
  }
}

template <typename T>
void rellenarDescendientes(typename Agen<T>::nodo n, Agen<T> &A, const T &fin)
// Pre: n es un nodo válido de A.
// Post: Lee desde entrada estándar y en preorden los hijos de n.
{
  T elto;
  typename Agen<T>::nodo nh;

  cout << "Hijo de " << A.elemento(n) << " (Fin = " << fin << "): ";
  cin >> elto;

  while (elto != fin)
  {
    A.insertarHijoIzqdo(n, elto);
    nh = A.hijoIzqdo(n);
    rellenarDescendientes(nh, A, fin);
    n = nh; // Avanzamos para insertar hermanos a la derecha del último hijo.
    cout << "Hermano derecho de " << A.elemento(n) << " (Fin = " << fin << "): ";
    cin >> elto;
  }
}

template <typename T>
void imprimirAgen(const Agen<T> &A)
// Post: Muestra los nodos de A en la salida estándar.
{
  if (!A.arbolVacio())
  {
    cout << "Raíz del árbol: " << A.elemento(A.raiz()) << endl;
    imprimirDescendientes(A.raiz(), A);
  }
  else
  {
    cout << "Árbol vacío\n";
  }
}

template <typename T>
void imprimirDescendientes(typename Agen<T>::nodo n, const Agen<T> &A)
// Post: Muestra los descendientes de n en la salida estándar.
{
  typename Agen<T>::nodo hijo = A.hijoIzqdo(n);
  while (hijo != Agen<T>::NODO_NULO)
  {
    cout << "Hijo de " << A.elemento(n) << ": " << A.elemento(hijo) << endl;
    imprimirDescendientes(hijo, A);
    hijo = A.hermDrcho(hijo);
  }
}

#endif // AGEN_E_S_H