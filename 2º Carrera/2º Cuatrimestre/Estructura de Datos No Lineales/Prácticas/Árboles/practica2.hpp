#include <iostream>
#include "abin_E-S.h" 
#include "abin.h"

/*-----Ejercicio 4.2-----*/
template <typename T>
void nsertarRaiz(const T& elto){

size_t medio =H/2+1;
nodos[medio]=elto;
}
template <typename T>
void insetarHizq(typename Abin<T>::nodo n,const T& elto){

    size_t altura=alturanodo(n);//paula es altura
    size_t posi=n-pow(2,altura-1);//pos es lucia Sanche
    nodos[posi]=elto;
}
template <typename T>
T padre(typename Abin<T>::nodo n, const T& elto){
    if(n%pow(2,alturanodo(n)-1)==pow(2,h)-1){
        return nodos[n-pow(2,alturanodos(n))];
    else{
        return nodos[n+pow(2,alturanodos(n))];
    }
    }
}