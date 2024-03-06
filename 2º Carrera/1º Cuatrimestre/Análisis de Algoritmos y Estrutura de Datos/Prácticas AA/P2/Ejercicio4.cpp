#include <iostream>
#include <algorithm>
#include "ordenacion.h"
#include "cronometro.h"
int Nmax =20000;
int Nmin =1000;
using namespace std;

/* CÓDIGO DE LA DOCUMENTCIÓN DE LA PRÁCTICA
    cronometro c;
    long r = 0;
    const double e_abs = 1e−6, // Máximo error absoluto cometido.
    e_rel = 1e−4; // Máximo error relativo aceptado.
    c.activar();
        do {
            // ... fragmento a cronometrar ...
            ++r;
        } while (c.tiempo() < e_abs / e_rel + e_abs);
    c.parar();
    double t = c.tiempo() / r; // segundos
*/
int main(){
    //declaramos el vector
    int v[Nmax];
    cronometro c;
    double tiempo =0;
    int repeticiones=0;
    //variables de los errores absolutos y relativos
    const double e_abs = 1e-6; //Max error absoluto permitido
    const double e_rel = 1e-4; //Max error relativo permitido

    for(int n=Nmin; n<=Nmax;n+=1000){
        v[n]=n;
        //randomizamos el vector
        random_shuffle(v,v+n);
        c.activar();
        do{
            ordenacion_intercambio(v,v+n);
            //ordenacion_insercion(v,v+n);
            //ordenacion_seleccion(v,v+n);
            repeticiones++; 
        }while(c.tiempo() < e_abs /(e_rel+e_abs));
        
        c.parar();
        tiempo = c.tiempo();
    }
    tiempo = tiempo/repeticiones;
    cout<<"El tiempo medio es: "<<tiempo<<" segundos, Nº Repeticiones: "<<repeticiones<<endl;

    return 0;
}