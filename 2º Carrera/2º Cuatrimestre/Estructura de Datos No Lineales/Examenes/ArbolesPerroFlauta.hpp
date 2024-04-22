// nodos perroflautas
// el arbol es perroflauta si tiene mas hijos izquierdos que derechos
#include <iostream>
#include "../Prácticas/Árboles/abin.h"

template <typename T>
bool perroflauta(Abin<T> &A)
{
    perroflauta_rec(A.raiz(), A);
}

template <typename T>
size_t HijoI(const Abin<T> &A)
{
    size_t nhijos = 0;
    typename Abin<T>::nodo n = A.raiz();
    if (n == Abin<T>::NODO_NULO)
        return 0;
    else if (A.hijoIzqdo(n) == Abin<T>::NODO_NULO)
        return HijoI(A.hijoDrcho(n), A);
    else
        return 1 + HijoI(A.hijoIzqdo(n), A) + HijoI(A.hijoDrcho(n), A);
}

template <typename T>
size_t HijoD(const Abin<T> &A)
{
    typename Abin<T>::nodo n = A.raiz();
    if (n == Abin<T>::NODO_NULO)
        return 0;
    else if (A.hijoDrcho(n) == Abin<T>::NODO_NULO)
        return HijoD(A.hijoIzqdo(n), A);
    else
        return 1 + HijoD(A.hijoDrcho(n), A) + HijoD(A.hijoIzqdo(n), A);
}
template <typename T>
bool perroflauta_rec(typename Abin<T>::nodo n, Abin<T> A)
{
    size_t nhijosI = HijoI(A.raiz(), A);
    size_t nhijosD = HijoD(A.raiz(), A);
    return nhijosD < nhijosI;
}
