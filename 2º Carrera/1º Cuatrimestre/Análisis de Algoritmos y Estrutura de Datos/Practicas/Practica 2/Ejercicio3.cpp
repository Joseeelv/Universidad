/*3. Analice empíricamente los algoritmos del primer ejercicio en el caso promedio. Utilice
permutaciones aleatorias de un vector de enteros que contenga los n primeros números
naturales, donde n variará desde 1 000 hasta 20 000 en incrementos de 1 000*/

#include <iostream>
#include "ordenacion.h"
#include "cronometro.h"
#include <algorithm>

using namespace std;

void rellena(int vf[],int vi[], int); //declaramos una funcion que nos rellene el vector

int main(){ 
    int n=20000;//tamaño del vector
    int vi[n]; //vector a ordenar 
    int vf[n];//resultado de ordenar el vector

    
    random_shuffle(vi,vi+n);//randomizamos el vector

    for(n=1000;n<=20000;n+=1000){
    cronometro c1,c2,c3;//declaracion de los cronometros

    cout<<"-CALCULO DE TIEMPO ALGORIMOS DE ORDENACION N = "<<n<<" -"<<endl;

    //ALGORITMO INTERCAMBIO DIRECTO
    rellena(vf,vi,n);//rellenamos el vector
    c1.activar(); //iniciamos el cronometro para calcular el tiempo que tarda el algoritmo
    ordenacion_intercambio(vi,vi+n);
    c1.parar();
    double t1=c1.tiempo();//declaramos una variable que nos guarda el tiempo que tardo el algoritmo

    //ALGORITMO SELECCION DIRECTA
    rellena(vf,vi,n);//rellenamos el vector
    c2.activar();
    ordenacion_seleccion(vi,vi+n);
    c2.parar();
    double t2=c2.tiempo();

    //ALGORITMO INSERCION DIRECTA
    rellena(vf,vi,n);//rellenamos el vector
    c3.activar();
    ordenacion_insercion(vi,vi+n);
    c3.parar();
    double t3=c3.tiempo();

    //IMPRIMIMOS LOS TIEMPOS
    cout<<"~ TIEMPO ALGORITMO INTERCAMBIO DIRECTO:  "<<t1<<" segundos ~"<<endl;
    cout<<"~ TIEMPO ALGORITMO SELECCION DIRECTA:  "<<t2<<" segundos ~"<<endl;
    cout<<"~ TIEMPO ALGORITMO INSERCION DIRECTA:  "<<t3<<" segundos ~"<<endl;
    cout<<"\n";
    }
    return 0;
}

void rellena(int vf[], int vi[], int n){
    int i;
    for (i=0;i<n;i++){
        vf[i]=vi[i];
    }
}

