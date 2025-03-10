
#include <iostream>
#include "../Prácticas/Árboles/abin.h"

template <typename T>
bool dosHijos(typename Abin<T>::nodo n, const Abin<T>& A){
	return (A.hijoIzqdo(n) != Abin<T>::NODO_NULO && A.hijoDrcho(n) != Abin<T>::NODO_NULO);
}

template <typename T>
size_t tresnietos(typename Abin<T>::nodo n, const Abin<T>& A){
	if(dosHijos(n,A)){ //Condición necesaria para que tenga 3 nietos.
      size_t nietos = 0;
        if(A.hijoIzqdo(A.hijoIzqdo(n))!=Abin<T>::NODO_NULO)nietos++;
        if(A.hijoIzqdo(A.hijoDrcho(n))!=Abin<T>::NODO_NULO)nietos++;
        if(A.hijoDrcho(A.hijoIzqdo(n))!=Abin<T>::NODO_NULO)nietos++;
        if(A.hijoDrcho(A.hijoDrcho(n))!=Abin<T>::NODO_NULO)nietos++;
        return nietos;
	}
    return 0;
}

template <typename T>
size_t nodo_verdes(const Abin<T>& A){
	return nodos_verdes_rec(A.raiz(),A);
}

template <typename T>
size_t nodos_verdes_rec(typename Abin<T>::nodo n, const Abin<T>& A){
	if(n==Abin<T>::NODO_NULO) return 0;
	else if(tresnietos(n,A)==3){ //condición
		return 1 + nodos_verdes_rec(A.hijoIzqdo(n),A) + nodos_verdes_rec(A.hijoDrcho(n),A);
	}
	else{
		return 0 + nodos_verdes_rec(A.hijoIzqdo(n),A) + nodos_verdes_rec(A.hijoDrcho(n),A);
	}
}