#include <iostream>
#include "abin_E-S.h" 
#include "abin.h"

/*Ejercicio de clase: Considere un árbol A, en el que puede suponer que no 
hay elementos repetidos. Dado un elemento x, devuelve el camino que existe entre la
raíz y el nodo cuyo elemento es x, si existe*/
template <typename T>
std::vector<T> busca_elto_rec(typename Abin<T>::nodo n, const Abin<T> A, const T elto,std::vector<T>& vector){
    if(n != Abin<T>::NODO_NULO){
        if(A.elemento(n)==elto){
        std::stack<T>pila;
        while(n!=A.raiz()){
            pila.push(A.elemento(n));
            n=A.padre(n);
        }
        pila.push(A.elemento(A.raiz()));
        while(!pila.empty()){
            vector.push_back(pila.top());
            pila.pop();
         }
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
            return 1+A.hijoIzqdo(n)+A.hijoDrcho(n);
        }
    }

}