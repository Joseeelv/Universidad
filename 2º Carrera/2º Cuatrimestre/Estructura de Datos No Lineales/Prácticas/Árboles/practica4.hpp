#include "abb.h"
#include <iostream>
#include <vector>
/*-----2. Un árbol binario de búsqueda se puede equilibrar realizando el recorrido en inorden 
del  árbol  para  obtener  el  listado  ordenado  de  sus  elementos  y  a  continuación,  repartir  
equitativamente los elementos a izquierda y derecha colocando la mediana en la raíz y 
construyendo recursivamente los subárboles izquierdo y derecho de cada nodo. 
Implementa este algoritmo para equilibrar un ABB.-----*/
template <typename T>
void inorden(Abb<T> A, std::vector<T>& eltos){
    if(!A.vacio()){
        inorden(A.izqdo(),eltos);
        eltos.pushback(A.elemento());
        inorden(A.drcho(),eltos);
    }
}

template <typename T>
void equilibrio(Abb<T>& A){
  std::vector<T> valores;
  Abb<T> auxiliar;
  inorden(A,valores);
  equilibrio_rec(auxiliar,valores,0,valores.size()-1);
  A=auxiliar;
}
template <typename T>
void equilibrio_rec(Abb<T>& A, std::vector<T> eltos, int ini, int fin){
    int mitad = (fin+ini)/2; //la mitad es la raiz
    if(fin >= ini){
        A.insertar(eltos[mitad]);
        equilibrio_rec(A,eltos,ini,mitad-1);
        equilibrio_rec(A,eltos,mitad+1,fin);
    }
}

/*-----3. Dados dos conjuntos representados mediante árboles binarios de búsqueda, 
implementa  la  operación  unión  de  dos  conjuntos  que  devuelva  como  resultado  otro  
conjunto que sea la unión de ambos, representado por un ABB equilibrado.-----*/


/*-----4. Dados dos conjuntos representados mediante árboles binarios de búsqueda, 
implementa  la  operación  intersección  de  dos  conjuntos,  que  devuelva  como  resultado  
otro  conjunto  que  sea  la  intersección  de  ambos.  El  resultado  debe  quedar  en  un  árbol  
equilibrado. -----*/

/*-----5. Implementa el operador  para conjuntos definido como A  B = (A  B) - (A  B). 
La  implementación  del  operador    debe  realizarse  utilizando  obligatoriamente  la  
operación  ,  que  nos  indica  si  un  elemento  dado  pertenece  o  no  a  un  conjunto.  La  
representación del tipo Conjunto debe ser tal que la operación de pertenencia esté en el 
caso promedio en O(log n).-----*/

template <typename T>
class Conjunto{
        std::vector<T> eltos_;
        Abb<T> arbol_;
    public:
        Conjunto operator -(const Conjunto& );
};



Conjunto<T>::operator - (const Conjunto& B){
    Conjunto<T> resultado;
    //Intersección
    for(auto elem: eltos_){
        if(!B.pertenece(elem)){
            resultado.arbol_.insetar(elem);
        }
    }
    //Union
    for(auto elem: B.eltos_){
        if(!pertenece(elem)){
            resultado.arbol_.insertar(elem);
        }
    }
    inorden(resultado.arbol_, resultado.eltos_);
    equilibrio(resultado.arbol_);
    return resultado;
}