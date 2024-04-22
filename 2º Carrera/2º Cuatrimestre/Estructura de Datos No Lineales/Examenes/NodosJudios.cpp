// nodos Nazis
// Te cargas los nodos cuyo contenido sea "judio"
// La raiz del subarbol que se elimina pasa a ser su hijo derecho
#include <iostream>
#include "../Prácticas/Árboles/abin.h"

template <typename T>
void nodos_judios(Abin<T>& A){
    nodos_judios_rec(A.raiz(),A);
}

// template <typename T>
// void nodos_judios_rec(typename Abin<T>::nodo n, Abin<T>& A){
//     if(n!=Abin<T>::NODO_NULO){
//         if(A.elemento(A.hijoIzqdo(n))=="judio") A.eliminarHijoIzqdo(A.padre(n));
//     }
// }