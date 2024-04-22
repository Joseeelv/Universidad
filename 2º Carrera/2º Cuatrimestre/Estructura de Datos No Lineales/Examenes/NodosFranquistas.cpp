// Funciones Franquismo
// Te cargas SOLO los hijos izquierdos de cada NODO
// SI te queda un hijo derecho de un hijo izquierdo:lo mueves arriba
#include <iostream>
#include "../Prácticas/Árboles/abin.h"

template <typename T>
void nodo_franquistaAbin(Abin<T> &A)
{
    nodo_franquistaAbin_rec(A.raiz(), A);
}

//Intentar hacerlo

// template <typename T>
// void nodo_franquistaAbin_rec(typename Abin<T>::nodo n, Abin<T> &A)
// {
//     if (n != Abin<T>::NODO_NULO)
//     {
//         if(EsHoja(n, A))
//         {   
//             A.eliminarHijoIzqdo(A.padre(n));
//         }
//         else if(A.hijoDrcho(n) != Abin<T>::NODO_NULO)
//         {
//             if (n == A.hijoDrcho(A.padre(n)))
//             {
//                 A.elemento(A.padre(n)) = A.elemento(n);
//                 A.eliminarHijoDrcho(n);
//             }
//         }
//     }
//     else
//     {
//         if(A.hijoIzqdo(n) != Abin<T>::NODO_NULO)nodo_franquistaAbin_rec(A.hijoIzqdo(n), A);
//         if(A.hijoDrcho(n) != Abin<T>::NODO_NULO)nodo_franquistaAbin_rec(A.hijoDrcho(n), A);
//     }
// }