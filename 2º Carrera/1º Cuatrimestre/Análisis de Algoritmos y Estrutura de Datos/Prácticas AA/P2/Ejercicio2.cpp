#include<iostream>
#include <algorithm> //next_permutation
#include "ordenacion.h"
#include "cronometro.h"
int N = 9;//numero total de elementos del vector
using namespace std;

//métodos que nos ordenarán el vector
bool prueba_ord_inter(int*,int*,int);
bool prueba_ord_selec(int*,int*,int);
bool prueba_ord_inser(int*,int*,int);
int main(){
/*Declaramos las variables que vamos a usar*/
    int vi[N], vf[N];
    double tiempo =0;

/*----PRUEBA ORDENACIÓN INTERCAMBIO----*/
    for(int n=0; n<=N;n++){
        //procedemos a rellenar el vector
        vi[n]=n; //vector ordenado
        //copiamos en el vector vf "ordenado"
        memcpy(vf,vi,sizeof(vi));
        do{
            if(!prueba_ord_inter(vi,vf,n)){
                cout<<"ERROR"<<endl;
                return -1;
            }
        }while(next_permutation(vi,vi+n));
    }
/*----PRUEBA ORDENACIÓN SELECCION----*/
    for(int n=0; n<=N;n++){
        //procedemos a rellenar el vector
        vi[n]=n; //vector ordenado
        //copiamos en el vector vf "ordenado"
        memcpy(vf,vi,sizeof(vi));
        do{
            if(!prueba_ord_selec(vi,vf,n)){
                cout<<"ERROR"<<endl;
                return -1;
            }
        }while(next_permutation(vi,vi+n));
    }
/*----PRUEBA ORDENACIÓN INSERCIÓN----*/
    for(int n=0; n<=N;n++){
        //procedemos a rellenar el vector
        vi[n]=n; //vector ordenado
        //copiamos en el vector vf "ordenado"
        memcpy(vf,vi,sizeof(vi));
        do{
            if(!prueba_ord_inser(vi,vf,n)){
                cout<<"ERROR"<<endl;
                return -1;
            }
        }while(next_permutation(vi,vi+n));
    }

    return 0;
}

bool prueba_ord_inter(int* a, int* b, int n){
    int vaux[n];//declaramos un vector auxiliar
    for(int i=0;i<n;i++){
        vaux[i]=a[i];
    }
    ordenacion_intercambio(vaux,vaux+n);//ordenamos mediante intercambio
    return(memcmp(vaux,b,n)==0);//devuelve true si el vector está ordenado correctamente.
}

bool prueba_ord_selec(int* a, int* b, int n){
    int vaux[n];
    for(int i=0;i<n;i++){
        vaux[i]=a[i];
    }
    ordenacion_seleccion(vaux,vaux+n);
    return(memcmp(vaux,b,n)==0);//devuelve true si se ha ordenado el vector correctamente
}

bool prueba_ord_inser(int* a, int *b, int n){
    int vaux[n];
    for(int i=0;i<n;i++){
        vaux[i]=a[i];
    }
    ordenacion_insercion(vaux,vaux+n);
    return(memcmp(vaux,b,n)==0);//devuelve true si se ha ordenado correctamente.
}