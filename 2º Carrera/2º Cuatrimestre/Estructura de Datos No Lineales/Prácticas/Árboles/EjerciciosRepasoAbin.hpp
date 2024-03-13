#include <iostream>
#include "abin_E-S.h" 
#include "abin.h"

/*Ejercicio de clase: Considere un árbol A, en el que puede suponer que no 
hay elementos repetidos. Dado un elemento x, devuelve el camino que existe entre la
raíz y el nodo cuyo elemento es x, si existe*/
template <typename T>
std::vector<T> busca_elto(const Abin<T>A,const T elto){
    return busca_elto_rec(A.raiz(),A,elto);:
}
template <typename T>
std::vector<T> busca_elto_rec(typename Abin<T>::nodo n, const Abin<T> A, const T elto){
    if(n != Abin<T>::NODO_NULO){
        if(A.elemento(n)==elto){
        std::stack<T>pila;
        std::vector<T>vector;
        while(n!=A.raiz()){ //Si ponemos n!= A.padre(A.raiz()); Nos podemos olvidar de poner la línea 22 de código;
            pila.push(A.elemento(n));
            n=A.padre(n);
        }
        pila.push(A.elemento(A.raiz()));
        while(!pila.empty()){
            vector.push_back(pila.top());
            pila.pop();
         }
         return vector;
        }
        else{
            busca_elto_rec(A.hijoIzqdo(n),A,elto);
            busca_elto_rec(A.hijoDrcho(n),A,elto);
        }
    }
}

/*Ejercicio de clase 2: Implementa una función que, dado un árbol , devuelva el número de nodos
prósperos que existen en él. Se considera que un nodo es próspero si es estrictamente más rico
que sus ascendientes, pero menos rico que sus descendientes*/
//1+Hi+Hd
template <typename T>
size_t nodos_prosperos(const Abin<T> A){
    return (A.raiz(),A);
}

template <typename T>
bool es_prospero(typename Abin<T>::nodo n, const Abin<T> A){
    if(n != Abin<T>::NODO_NULO){
        if(ascendiente(n,A)&& descendiente(n,A)){ 
            return true;
        }else{
            return false;
        }
    }else{
            return false;
        }
}
template <typename T>
bool ascendiente(typename Abin<T>::nodo n, const Abin<T> A){
    bool nodo_max = true;
    while(n!=A.raiz()&& nodo_max){
        if(A.elemento(n)>A.elemento(padre(n))){
            nodo_max = true;
            else{
                return false;
            }
        }
    }
} //devuelve true si es prospero ascendentemente

template<typename T>
bool descendiente(typename Abin<T>::nodo n, const Abin<T> A){
    if(n!=Abin<T>::NODO_NULO){
        if(A.elemento(n)<A.elemento(A.hijoIzqdo(n))&& A.elemento(n)<A.elemento(A.hijoDrcho(n))){
            return descendiente(A.hijoIzqdo(n),A)||descendiente(A.hijoDrcho(n),A);
        }else{ //no cumple que sea mayor que el descendiente
            return false;
        }
    }else{
        return true;
    }
} //devuelve true si es prospero descendentemente

template <typename T>
size_t nodos_prosperos_rec(typename Abin<T>::nodo n, Abin<T> A){
    if(n==Abin<T>::NODO_NULO){
        return 0;
    }else{
        if(es_prospero(n)){
            return 1+nodos_prosperos_rec(A.hijoIzqdo(n),A)+nodos_prosperos_rec(A.hijoDrcho(n),A);
        }
       // else return 0+nodos_prosperos_rec(A.hijoIzqdo(n),A)+nodos_prosperos_rec(A.hijoDrcho(n),A);
    }
}
/*Ejercicio 3: Dado un árbol y un nodo podamos el árbol y el propio nodo*/
template <typename T>
void poda(typename Abin<T>::nodo n, Abin<T> A){
    if(n!=Abin<T>::NODO_NULO){
        return poda_rec(n,A);
    }
    typename Abin<T>::nodo papa = A.padre(n);
    if((papa = A.raiz() && EsHoja(papa,A))){
            A.eliminarRaiz();
    }
    else if(n==A.hijoIzqdo(papa)){
        A.eliminarHijoIzqdo(papa);
    }else A.eliminarHijoDrcho(papa);

}
template <typename T>
void poda_rec (typename Abin<T>::nodo n, Abin<T>& A){
    if(n!=typename Abin<T>::NODO_NULO){
        if(!EsHoja(n,A)){ //Si no es hoja tiene hijos.
            poda_rec(A.hijoIzqdo(n),A);
            poda_rec(A.hijoDrcho(n),A);
            A.eliminarHijoIzqdo(n);
            A.eliminarHijoDrcho(n);
        }
    }
}
template <typename T>
bool EsHoja(typename Abin<T>::nodo n, const Abin<T>& A){
    return (A.hijoIzqdo(n) == Abin<T>::NODO_NULO && A.hijoDrcho(n) == Abin<T>::NODO_NULO);
}

