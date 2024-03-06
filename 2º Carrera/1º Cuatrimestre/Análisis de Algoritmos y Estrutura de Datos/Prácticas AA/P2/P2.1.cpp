/*
Jose Luis Venega Sánchez - 
1. Programe los algoritmos de ordenación por intercambio directo, selección directa e inserción directa para vectores de enteros.
*/
//incluimos las librerías que vamos a usar:
#include <iostream>
#include <algorithm> //libreria de random_shuffle
#include "ordenacion.h" //algoritmos de ordenación
#include "cronometro.h" //clase cronómetro
/* CÓDIGO QUE NOS DA LA DOCUMENTACIÓN
    const long r = 1000000;
    cronometro c;
    c. activar ();
    // ... fragmento a cronometrar ...
    c.parar();
    double t = c.tiempo() / r; // segundos
*/

void rellenar(int * , int* , int); //metodo para rellenar el vector de valores.
using namespace std;

int main(){
    //creamos los vectores
    int n=0; //N el numero de elementos del vector
    //delaramos los cronometros.
    cronometro int_directo = cronometro();
    cronometro selec, inserc;
    double t1=0, t2=0, t3=0;
    unsigned opc; //opción del switch

    cout<<"Introduce el numero de elementos del vector: ";
    cin >> n;
    int v[n],v_ordenado[n]; //v vector desordenado,v_ordenado vector final ordenado.
    rellenar(v, v_ordenado, n);//rellenamos los vectores.
    cout<<"---- PRUEBAS DE ORDENACION ----"<<endl;
    //desordenamos el vector inicial -> v[]
    random_shuffle(v, v+n);//(inicio, inicio+n = fin);
    for(int i=0; i<n; i++){
        cout<<"Posicion "<<i<<", Elemento: "<<v[i]<<endl;
    }
      
    do{
        cout<<"0 -- Salir del programa"<<endl;
        cout<<"1 -- Pueba de Intercambio directo"<<endl;
        cout<<"2 -- Prueba de Seleccion directa"<<endl;
        cout<<"3 -- Prueba de Inserccion directa"<<endl;
        cout<<"4 -- Hacer todas las pruebas a la vez"<<endl;
        cout<<"---------------------------------\n"
        <<"Introduce una opción: "; cin >> opc;
    }while(opc>4);
    switch (opc)
    {
    case 0:
        cout<<"Saliendo del programa";
        return 0;
    case 1:
        cout<<"-- PRUEBA DE INTERCAMBIO DIRECTO --"<<endl;
        int_directo.activar();//iniciamos el cronometro
        ordenacion_intercambio(v,v+n);//algoritmo de ordenación intercambio directo
        int_directo.parar();//paramos el cronometro
        t1 = int_directo.tiempo();
        cout<<"Tiempo de ordenación intercambio directo --> "<<t1<<"ms"<<endl;
        break;
    //hacemos lo mismo para los demás casos:
    case 2:
        cout<<"-- PRUEBA DE SELECCION DIRECTA --"<<endl;
        selec.activar();
        ordenacion_seleccion(v,v+n);
        selec.parar();
        t2 = selec.tiempo();
        cout<<"Tiempo de ordenación seleccion directa --> "<<t2<<"ms"<<endl;
        break;
    case 3:
        cout<<"-- PRUEBA DE INSERCCION DIRECTA --"<<endl;
        inserc.activar();
        ordenacion_insercion(v,v+n);
        inserc.parar();
        t3 = inserc.tiempo();
        cout<<"Tiempo de ordenación inserccion directa --> "<<t3<<"ms"<<endl;
        break;
    case 4:
        cout<<"-- PRUEBA DE TODOS LOS ALGORITMOS A LA VEZ --"<<endl;
        int_directo.activar();//iniciamos el cronometro
        ordenacion_intercambio(v,v+n);//algoritmo de ordenación intercambio directo
        int_directo.parar();//paramos el cronometro
        t1 = int_directo.tiempo();

        selec.activar();
        ordenacion_seleccion(v,v+n);
        selec.parar();
        t2 = selec.tiempo();
        
        inserc.activar();
        ordenacion_insercion(v,v+n);
        inserc.parar();
        t3 = inserc.tiempo();
        
        cout<<"Tiempo de ordenación intercambio directo --> "<<t1<<"ms"<<endl;
        cout<<"Tiempo de ordenación seleccion directa --> "<<t2<<"ms"<<endl;
        cout<<"Tiempo de ordenación inserccion directa --> "<<t3<<"ms"<<endl;
    default:
        break;
    }
    return 0;
}

//vamos a crear una función rellenar que nos va a crear un vector ordenado de N elementos
void rellenar(int *a,int *b, int n){
    for(int i=0; i<n; i++){
        a[i] = i;
        b[i] = i;
    }
}