#include <iostream>
#include "agen.h"
#include <vector>
#include <string.h>

/*Ejercicio 4:  Un árbol es estrictamente ternario si todos sus nodos son hojas o tienen tres hijos. 
Escribe una función que, dado un árbol de grado arbitrario, nos indique si es o no estrictamente ternario.*/
template <typename T>
bool esTernario(typename Agen<T>::nodo n, Agen<T>& A){
    return esTernario_rec(A.raiz(),A);
}
template <typename T>
bool esTernario_rec(typename Agen<T>::nodo n, Agen<T>& A){
    if(n!= Agen<T>::NODO_NULO){
        int numhijos = nHijos(n,A);
        bool estado = (numhijos==0) || (numhijos == 3);
        typename Agen<T>::nodo aux = A.hijoIzqdo(n);
        while(aux && estado){
            estado &= esTernario_rec(aux,A);
            aux=A.hermDrcho(aux);
        }
        return estado;
    }
}
template <typename T>
int nHijos(typename Agen<T>::nodo n, Agen<T>& A){
    if(n!= Agen<T>::NODO_NULO){
        //Recorremos el árbol
        int hijos =0;
        typename Agen<T>::nodo aux = A.hijoIzqdo(n);
        while(aux){
            hijos++;
            aux=A.hermDrcho(aux);
        }
        return hijos;
    }
    else return 0;
}

/*Ejercicio 5: Una forma de representar una figura plana en blanco y negro consiste en utilizar un árbol cuaternario 
en el que cada nodo o tiene exactamente cuatro hijos, o bien es una hoja. Un nodo hoja puede ser blanco o negro y 
un nodo interno no tiene color. Una figura dibujada dentro de un cuadrado de lado 2k se representa de la forma siguiente: 
Se divide el cuadrado en cuatro cuadrantes y cada uno se representa como un hijo del nodo raíz. Si un cuadrante está completamente
negro corresponde a una hoja negra; si, por el contrario, el cuadrante está completamente blanco, éste corresponde 
a una hoja blanca; y si un cuadrante está parcialmente ocupado por negro y blanco, entonces corresponde a un nodo interno del árbol 
y este cuadrante se representa siguiendo el mismo método subdividiéndolo en otros cuatro cuadrantes. Como ejemplo se muestra una figura
en blanco y negro y su árbol asociado, tomando los cuadrantes en el sentido de las agujas del reloj a partir 
del cuadrante superior izquierdo.*/

typedef struct{
    std::string color;
    int x0x1[2];
    int y0y1[2];
}Pixel;
//se devuelve la matriz resultante por referencia.
template <typename Pixel>
void figura_rec(typename Agen<Pixel>::nodo n, Agen<Pixel>& A, std::vector<std::vector<Pixel> >& M){
    if(n!= Agen<Pixel>::NODO_NULO){
        if(A.elemento(n).color ==" "){ //ausencia de color -> recorremos el árbol
            typename Agen<Pixel>::nodo aux = A.hijoIzqdo(n);
            while(aux){
                figura_rec(aux,A,M);
                aux=A.hermDrcho(aux);
            }
        }
        else{
            if(A.elemento(n).color == "B" || A.elemento(n).color == "N"){
                for(auto i = A.elemento(n).x0x1[0]; i<=A.elemento(n).x0x1[1]; i++){
                    for(auto j=A.elemento(n).y0y1[0]; j<=A.elemento(n).y0y1[1]; j++){
                        M[i][j] = A.elemento(n).color;
                    }
                }
            }   
        }
    }
}


