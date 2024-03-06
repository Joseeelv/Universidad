/*
Jose Luis Venega Sánchez
3. Analice empíricamente los algoritmos del primer ejercicio en el caso promedio. 
Utilice permutaciones aleatorias de un vector de enteros que contenga los n primeros números naturales, 
donde n variará desde 1 000 hasta 20 000 en incrementos de 1 000.
*/
#include <iostream>
#include <algorithm>//libreria de next_permutation y random_shuffle
#include "ordenacion.h"
#include "cronometro.h"
using namespace std;
int Nmax = 20000;
int Nmin = 1000;

void rellena(int*);
int main(){
    int vi[Nmax];//creamos el vector de tamaño maximo
    int contador =0;
    cronometro c;
    double tiempo=0;
    for(int n=Nmin;n<=Nmax;n= n+1000){
        rellena(vi);
        random_shuffle(vi,vi+n);//randomizamos el vector
        //---Prueba Intercambio ---
        c.activar();
        ordenacion_insercion(vi,vi+n);
        c.parar();
        tiempo += c.tiempo();
        contador++;
        cout<<"El tiempo es de "<<tiempo<<"s para un tam "<<n<<endl;
    }
    tiempo = tiempo/contador;
    cout<<"El tiempo medio es de "<<tiempo<<" segundos, para "<<contador<<" repeticiones"<<endl;
    return 0;
}

void rellena(int *v){
    for(int i=0; i<Nmax;i++){
        v[i]=i;
    }
}