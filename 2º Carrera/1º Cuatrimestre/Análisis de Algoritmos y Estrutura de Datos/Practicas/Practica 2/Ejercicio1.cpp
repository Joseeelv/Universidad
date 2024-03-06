/* 1. Programe los algoritmos de ordenación por intercambio directo, selección directa e inser-
ción directa para vectores de enteros.*/

#include <iostream>
#include "ordenacion.h"
#include "cronometro.h"
#include <algorithm>

using namespace std;

int main(){
    int vi[9]={1,4,2,3,6,5,9,7,8}; //vector a ordenar 
    int vf[9]={1,2,3,4,5,6,7,8,9};//resultado de ordenar el vector
    int n=9;//tamaño del vector
    cronometro c1,c2,c3;//declaracion de los cronometros

    cout<<"-CALCULO DE TIEMPO ALGORIMOS DE ORDENACION-"<<endl;

    //ALGORITMO INTERCAMBIO DIRECTO
    c1.activar(); //iniciamos el cronometro para calcular el tiempo que tarda el algoritmo
    ordenacion_intercambio(vi,vi+n);
    c1.parar();
    double t1=c1.tiempo();//declaramos una variable que nos guarda el tiempo que tardo el algoritmo

    //ALGORITMO SELECCION DIRECTA
    c2.activar();
    ordenacion_seleccion(vi,vi+n);
    c2.parar();
    double t2=c2.tiempo();

    //ALGORITMO INSERCION DIRECTA
    c3.activar();
    ordenacion_insercion(vi,vi+n);
    c3.parar();
    double t3=c3.tiempo();

    //IMPRIMIMOS LOS TIEMPOS
    cout<<"~ TIEMPO ALGORITMO INTERCAMBIO DIRECTO:  ~"<<t1<<" segundos "<<endl;
    cout<<"~ TIEMPO ALGORITMO SELECCION DIRECTA:  ~"<<t2<<" segundos "<<endl;
    cout<<"~ TIEMPO ALGORITMO INSERCION DIRECTA:  ~"<<t3<<" segundos "<<endl;

    return 0;
}

