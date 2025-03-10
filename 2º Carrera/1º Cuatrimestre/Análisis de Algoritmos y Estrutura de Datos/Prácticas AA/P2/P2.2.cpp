/*
Jose Luis Venega Sánchez
2. Realice pruebas de caja negra sobre los algoritmos del ejercicio anterior con las técnicas explicadas en la práctica 1. 
Utilice como batería de pruebas vectores de n enteros: varíe n desde 1 hasta 9 y pruebe todas las permutaciones de cada vector.
*/

//incluimos las librerias
#include <iostream>
#include <algorithm> //librería de next_permutation y random_shuffle
using namespace std;
int N = 9; //variable global 

//incluimos algoritmos de ordenación
#include "ordenacion.h"

/*
No hacemos uso de los métodos del ejercicio anterior, si no que
hacemos una implementación de este método, además haciendo uso de next_permutation
bool prueba_ordena(int e[], int s [], unsigned n) {
    int v[n];
    for (unsigned i=0;i<n;++i){
        v[ i ] = e[i ];
        cout << v[i] << " ";
    }
    cout << endl;
    ordena(v, v + n);
    return (memcmp(v, s, n) == 0); // Devuelve la comprobación del resultado.
}
*/

//declaramos los métodos
bool prueba_ordena_intercambio(int*, int*, int);
void imprime(int*);
int main(){
    int vi[N],vf[N];//vectores
    cout<<"\n---PRUEBA INTERCAMBIO DIRECTO---"<<endl;
    for(int n=1; n<=N; ++n){
        vi[n-1] = n-1;//rellenamos el vector
        memcpy(vf,vi,sizeof(vi));//copiamos en el vector final, el inicial.
        do{
            if(!prueba_ordena_intercambio(vi,vf,n)){
                cout<<"ERROR";
                return -1;
            }

        }while(next_permutation(vi,vi+n));
    }
    imprime(vi);
    cout<<" ~Algoritmo correcto~"<<endl;

    return 0;
}

bool prueba_ordena_intercambio(int *vi,int *vf, int n){
    //creamos un vector auxiliar
    int vaux[n];
    for(int i=0; i<n; i++){
        //copiamos el vector
        vaux[i] =vi[i];
    }
        //llamamos al algoritmo de ordnación
        ordenacion_intercambio(vaux,vaux+n);
        //devolvemos si el vector está ordenado o no, mediante comparación
        return(memcmp(vaux,vf,n)==0);
}

void imprime(int *a){
    for (int i=0; i<N; i++){
        cout<<" "<<a[i];
    }
}