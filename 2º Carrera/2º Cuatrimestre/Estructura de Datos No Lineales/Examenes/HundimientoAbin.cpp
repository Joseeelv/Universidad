#include <iostream>
#include "../Prácticas/Árboles/abin.h"
// tenemos un Abin y un nodo, hacemos que este sea una hoja y lo eliminamos

template <typename T>
void hundir(typename Abin<T>::nodo n, Abin<T> A, const T &e)
{
    typename Abin<T>::nodo aux;
    if (buscar_rec(A.raiz(), A, e, aux))
    {
        hundir_rec(aux, A);
    }
}

template <typename T>
bool buscar_rec(typename Abin<T>::nodo n, Abin<T> A, const T &e, typename Abin<T>::nodo &res)
{
    if (n != Abin<T>::NODO_NULO)
    {
        if (A.elemento(n) == e)
        {
            res = n;
            return true;
        }
        else
        {
            return buscar_rec(A.hijoIzqdo(n), A, e, res) || buscar_rec(A.hijoDrcho(n), A, e, res);
        }
    }
    return false;
}

template <typename T>
void swap(typename Abin<T>::nodo a, typename Abin<T>::nodo b, Abin<T> A)
{
    typename Abin<T>::nodo aux = a;
    a = b;
    b = aux;
}

template <typename T>
void hundir_rec(typename Abin<T>::nodo n, Abin<T> A)
{
    if (n != Abin<T>::NODO_NULO)
    {
        if (A.hijoIzqdo(n) != Abin<T>::NODO_NULO)
        {
            swap(n, A.hijoIzqdo(n), A);
            hundir_rec(A.hijoIzqdo(n), A);
        }
        else if (A.hijoDrcho(n) != Abin<T>::NODO_NULO)
        {
            swap(n, A.hijoDrcho(n), A);
            hundir_rec(A.hijoDrcho(n), A);
        }
        else
        {
            if (A.hijoIzqdo(A.padre(n)) == n)
                A.eliminarHijoIzqdo(A.padre(n));
            else
                A.eliminarHijoDrcho(A.padre(n));
        }
    }
}