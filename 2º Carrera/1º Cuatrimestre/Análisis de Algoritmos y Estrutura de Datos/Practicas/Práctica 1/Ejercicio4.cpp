/*4. Escriba un programa que genere 10 000 000 de números pseudoaleatorios de precisión doble
en el intervalo [0, 1] e imprima la media de los valores y = 4 ·√1 −x2correspondientes a
cada número x. Emplee la función del ejercicio anterior.*/

#include<iostream>
#include<math.h>

using namespace std;

int main(){
    double x,y;//siendo x el numero aleatorio e y la media
    int i=0, n=10000000;//siendo i el contador del bucle y n las veces que se repite

    while(i<n){
    x= (double)rand()/RAND_MAX; //numero aleatorio en el intervalo[0,1]

    y+=4*sqrt(1-x*x);
    i++; //aumentamos el contador del bucle
    }

    cout<<"La media es: "<<y<<endl;


    return 0;

}