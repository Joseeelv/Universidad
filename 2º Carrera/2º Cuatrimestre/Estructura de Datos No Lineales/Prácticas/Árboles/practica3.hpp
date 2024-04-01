#include "agen.h"
#include <iostream>

/*-----1. Implementa un subprograma que dado un árbol general nos calcule su grado.-----*/





/*-----3. Se define el desequilibrio de un árbol general como la máxima diferencia entre las 
alturas de los subárboles más bajo y más alto de cada nivel.Implementa un subprograma que 
calcule el grado de desequilibrio de un árbol general.-----*/
template <typename T>
int Altura(typename Agen<T>::nodo n, Agen<T> A){
    if(n==Agen<T>::NODO_NULO){
        return 0;
    }
    else{
        typename Agen<T>::nodo aux = A.HijoIzqdo(n);
        int altura= -1;
        while(aux){
            altura = max(altura,Altura_rec(aux,A));
        }
    }
}
template <typename T>
int Altura_rec(typename Agen<T>::nodo n, Agen<T> A){
    
}
template <typename T>
int ramaCorta(){ 

}

template <typename T> //Lo hacemos con el mínimo
int ramaCorta_rec(){}

desequilibrio -> return Altura_rec - RamaCorta_rec;


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

