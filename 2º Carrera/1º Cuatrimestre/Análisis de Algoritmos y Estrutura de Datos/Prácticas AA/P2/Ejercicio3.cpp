#include <iostream>
#include <algorithm>
#include "ordenacion.h"
#include "cronometro.h"
int Nmax = 20000;
int Nmin = 1000;
using namespace std;

int main(){
//declaramos vectores
    int vi[Nmax];
    cronometro c;
    double tiempo=0;
    int repeticiones=0;
    for(int n=Nmin;n<=Nmax;n+=1000){
        vi[n]=n;//rellenamos el vector ordenadamente
        //lo randomizamos
        random_shuffle(vi,vi+n);
        c.activar();
        ordenacion_intercambio(vi,vi+n);
        //ordenacion_insercion(vi,vi+n);
        //ordenacion_seleccion(vi,vi+n);
        c.parar();
        tiempo+=c.tiempo();
        repeticiones++;
    }
    tiempo = tiempo/repeticiones;
    cout<<"Tiempo medio: "<<tiempo<<" segundos, Nº repeticiones: "<<repeticiones<<endl;
    return 0;
}
