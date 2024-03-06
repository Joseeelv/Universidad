#include <iostream>
#include "../abin_E-S.h" 
#include "../abin.h"
/*-----EJERCICIO 1-----*/
template <typename T> size_t cuentanodos(const Abin<T> &A){
  if(A.raiz() == Abin<T>::NODO_NULO) return 0; 
  return cuentanodosrec_(A.raiz(), A);
}

template <typename T> size_t cuentanodosrec_(typename Abin<T>::nodo n, const Abin<T> &A){
    if(n==Abin<T>::NODO_NULO)
    {
        return 0;
    }
    else 
    {
        return 1+(cuentanodosrec_(A.hijoIzqdo(n),A)+cuentanodosrec_(A.hijoDrcho(n),A));
    }
}  

/*-----EJERCICIO 2-----*/ //Altura -> longitud de la rama más larga
template <typename T> size_t altura (const Abin<T> &A){
    return ramarec(A.raiz(), A); //altura del nodo raiz = 0, árbol vacío = -1.
}

template <typename T> size_t alturarec(typename Abin<T>::nodo n, const Abin<T> &A){
    if(n == Abin<T>::NODO_NULO)
    {
        return -1;
    }
    else 
    {
        return 1+std::max(alturarec(A.hijoIzqdo(n),A)+alturarec(A.hijoDrcho(n),A));
    }
    //Devolvemos el máximo de las alturas del árbol
}

/*-----EJERCICIO 3-----*/
template <typename T> size_t profundidad(typename Abin<T>::nodo n, const Abin<T> &A){
    if(n== Abin<T>::NODO_NULO)
    {
        return -1;
    }
    else{
        return 1+profundidadrec(A.padre(n),A);
    }
}

/*-----EJERCICIO 4 Suponemos que estamos dentro del TAD con representación vectorial-----*/

template <typename T> size_t alturavecrec(typename Abin<T>::nodo n){
    if(nodos[n]==Abin<T>::NODO_NULO){
        return 0;
    }
    else{
        return 1+std::max(alturavecrec(nodos[n].hizqdo)+alturavecrec(nodos[n].hder));
    }
}

template <typename T>
size_t Abin<T>::altura_nodo(nodo n) const
{
    if (n == NODO_NULO)
    {
        return 0;
    }
    else
    {
        return 1 + std::max(altura_nodo(nodos[n].hizq), altura_nodo(nodos[n].hder));
    }
}
/*-----EJERCICIO 5 Repetimos el ejercicio anterior pero para celdas enlazadas-----*/
//ESTAMOS DENTRO DEL TAD ABIN ENLAZADO
template <typename T>
size_t altura_nodo_enla(typename Abin<T>:: nodo n){
    if(n == Abin<T>::NODO_NULO){
        return 0;
    }
    else{
        return 1+std::max(altura_nodo_enla(n->hizq)+altura_nodo_enla(n->hder));
    }
}

template <typename T>
size_t profundidad_enla(typename Abin<T>::nodo n){
    if(n==Abin<T>::NODO_NULO){
        return -1;
    }
    else{
        return 1 + profundidad_enla(n->padre);
    }
}
/*-----EJERCICIO 6 Nivel de desequilibrio de un árbol binario-----*/
template <typename T>
size_t desequilibrio(const Abin<T>& A){
    return desequilibrio_rec(A.raiz(),A);
}

template <typename T>
size_t desequilibrio_rec(typename Abin<T>::nodo n, const Abin<T> A){
    if(n == Abin<T>::NODO_NULO){
        return 0;
    }
    else{

        return std::max(std::abs(altura(A.hijoIzqdo(n),A) - altura(A.hijoDrcho(n),A),
               std::max(desequilibrio_rec(A.hijoIzqdo(n),A), desequilibrio_rec(A.hijoDrcho(n),A))));
    }
    //Calculamos la diferencia de altura de los hijos del nodo n y
    //calculamos el máximo desequilibrio de los subárboles de los hijos de n.
    //Devolvemos el número mayor
}

/*-----EJERCICIO 7 Cálculo de árbol binario pseudocompleto-----*/
template <typename T>
bool pseudocompleto(const Abin<T>& A){
    return pseudocompleto_rec(A.raiz(),A);
}

template <typename T>
bool EsHoja(typename Abin<T>::nodo n, const Abin<T>& A){
    return (A.hijoIzqdo(n) == Abin<T>::NODO_NULO && A.hijoDrcho(n) == Abin<T>::NODO_NULO);
}

template <typename T>
bool pseudocompleto_rec(typename Abin<T>::nodo n, const Abin<T> A){
    if(n==Abin<T>::NODO_NULO){
        return true;
    }
    else{
        if(A.hijoIzqdo(n)!=Abin<T>::NODO_NULO && A.hijoDrcho(n) != Abin<T>::NODO_NULO){
            return pseudocompleto_rec(A.hijoIzqdo(n),A) && pseudocompleto_rec(A.hijoDrcho(n),A);
            //tiene dos hijos.
        }
        else if(EsHoja(n,A)) {return true;} //no tiene hijos
        else{
            return false; //Solo tiene un hijo sea izquierdo o derecho.
        }
    }
}