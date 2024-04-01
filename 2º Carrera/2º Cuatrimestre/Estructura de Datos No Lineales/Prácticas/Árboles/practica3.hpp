#include "agen.h"
#include <iostream>

/*-----1. Implementa un subprograma que dado un árbol general nos calcule su grado.-----*/
template <typename T>
size_t grado(typename Agen<T>::nodo n, Agen<T> A){
    return grado_rec(A.raiz(),A);
}

template <typename T>
size_t grado_rec(typename Agen<T>::nodo n, Agen<T> A){
    if(n==Agen<T>::NODO_NULO){
        return 0;
    }
    else{
        typename Agen<T>::nodo aux = A.hijoIzqdo(n);
        //Creamos una variable local que devolverá el máximo grado
        size_t grado = 0;
        size_t nhijos=0;
        while(aux){
            nhijos++;
            grado = std::max(grado,grado_rec(aux,A));
            aux = A.hermDrcho(aux);
        }
        return std::max(grado,nhijos);
    }
}

/*-----2. Implementa un subprograma que dados un árbol y 
un nodo dentro de dicho árbol determine la profundidad de 
éste nodo en el árbol.-----*/
template <typename T>
size_t profundidad(typename Agen<T>::nodo n, Agen<T> A){
    return profundidad_rec(n,A);
}
template <typename T>
size_t profundidad_rec(typename Agen<T>::nodo n, Agen<T> A){
    if(n==Agen<T>::NODO_NULO){
        return -1;
    }
    else{
        return 1+profundidad_rec(A.padre(n),A);
    }
}

/*-----3. Se define el desequilibrio de un árbol general como la máxima diferencia entre las 
alturas de los subárboles más bajo y más alto de cada nivel.Implementa un subprograma que 
calcule el grado de desequilibrio de un árbol general.-----*/
template <typename T>
size_t desequilibrio(const Agen<T> &A)
{
    return desequilibrio_rec(A.raiz(), A);
}
template <typename T>
size_t desequilibrio_rec(typename Agen<T>::nodo n, const Agen<T> &A)
{
    if (n == Agen<T>::NODO_NULO)
        return 0;
    else
    {
        size_t max_desequilibrio = 0;
        typename Agen<T>::nodo hijo = A.hijoIzqdo(n);
        while (hijo != Agen<T>::NODO_NULO)
        {
            max_desequilibrio = std::max(max_desequilibrio,
                                std::abs(altura_rec(hijo, A) -
                                altura_rec(A.hermDrcho(hijo), A)));
            hijo = A.hermDrcho(hijo);
        }
        return max_desequilibrio;
    }
}

/*-----4. Dado un árbol general de enteros A y un entero x, implementa un subprograma que 
realice la poda de A a partir de x. Se asume que no hay elementos repetidos en A.-----*/
template <typename T>
void buscarec(typename Agen<T>::nodo n, Agen<T> A, T elto,typename Agen<T>::nodo &encontrado){
    if(n!= Agen<T>::NODO_NULO){
        if(A.elemento(n) == elto){
            encontrado = n;
            podarAgenrec(encontrado,A);
        }
        else{
            typename Agen<T>::nodo aux = A.hijoIzqdo(n);
            while (aux != Agen<T>::NODO_NULO){
                buscarec(aux,A,elto);
                aux=A.hermDrcho(aux);
            }
        }
    }
}

template <typename T>
void podarAgen(Agen<T>& A, T elto){ //vamos a hacer la búsqueda en la propia funcion
    typename Agen<T>::nodo eliminar = buscarec(A.raiz(),A,elto,eliminar);
    if(eliminar != Agen<T>::NODO_NULO){
        podarAgenrec(eliminar,A);
        typename Agen<T>::nodo aux = A.hijoIzqdo(A.padre(eliminar));
        if(A.eliminar(aux)==elto){
            A.eliminarHijoIzqdo(A.padre(aux));
        }else{
            while(A.elemento(A.hermDrco(aux))!=elto){
                aux=A.hermDrcho(aux);
            }
            A.eliminar(A.hermDrcho(aux));
        }
    }
    else{
        std::cout<<"Nodo Nulo"<<std::endl; //el control del nodo nulo lo tenemos aquí, cuando eliminar es nulo.
    }
}

template <typename T>
void podaAgenrec(typename Agen<T>::nodo n, Agen<T>& A){
    while(A.hijoIzqdo(n)){
        podaAgenrec(A.hijoIzqdo(n),A);
        A.eliminarHijoIzqdo(n);
    }
    
}

