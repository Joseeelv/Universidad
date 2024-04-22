#include <iostream>
#include "../Prácticas/Árboles/agen.h"

template <typename T>
bool  similares_rec(typename Agen<T>::nodo a, typename Agen<T>::nodo b, const Agen<T>& A1, const Agen<T>& A2){
    if(A1.raiz() == nullptr && A2.raiz() == nullptr) return true; //arboles vacios

    else if(a==Agen<T>::NODO_NULO || b==Agen<T>::NODO_NULO) return false; //un nodo nulo y el otro no

    else if(Eshoja(a,A1) && Eshoja(b,A2)){ //Son hojas -> comprobamos valores y vemos si son iguales
        if(A1.elemento(a) == A2.elemento(b))return true;
        else return false;
    }
    else { //no son hojas, recorremos dependiendo si tienen o no el mismo numero de hijos
        bool flag = nHijos(a,A1) == nHijos(b,A2); //si no tienen los mismo hijos no cumplen la ramificación
        while(flag){ //siempre se ejecuta cuando el numero de hijos de los nodos son el mismo -> misma ramificación
            flag&=similares_rec(A1.hijoIzqdo(a), A2.hijoIzqdo(b),A1,A2);
            a = A1.hermDrcho(a);
            b = A2.hermDrcho(b);
        }
        return flag; //no se cumple lo anterior
    }
}

//hay que implementar el esHoja y el nHijos

template <typename T>
bool Eshoja(typename Agen<T>::nodo n, const Agen<T>& A){
    return(A.hijoIzqdo(n)==Agen<T>::NODO_NULO);
}

