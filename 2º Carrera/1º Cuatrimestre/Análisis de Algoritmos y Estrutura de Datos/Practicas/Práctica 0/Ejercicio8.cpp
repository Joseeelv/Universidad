/*8. Escriba un programa que calcule el cuadrado de un double leído de la entrada estándar e
imprima el número de veces que puede repetir dicho cálculo durante un segundo. Emplee
una función que se expanda en línea para obtener el cuadrado de un número.
*/

#include <iostream>
#include "cronometro.h"

inline double cuadrado(double n) { return (n*n);} //siendo n nuestro numero introducido.

int main(){
    int contador=0,resultado=0; 
    cronometro cronometro;
    double n; //nuestro numero a calcular el cuadrado

    std::cout<<"Introduce el numero para calcular su cuadrado: ";
    std::cin>>n;

    cronometro.activar(); //activamos el cronometro, funcion definida en "cronometro.h".

    while(cronometro.tiempo() < 1){ //el bucle se realiza mientras que el tiempor del cronometro
                                    //sea menor que 1 ya que nos dice el enunciado en 1 segundo.
        resultado=cuadrado(n);//llamada a la funcion inline    
        contador++;//aumentamos en 1 el contador;
    }
     
    //Mostramos por pantalla los resultados obtenidos.
    std::cout<<"El resultado es: " << resultado << std::endl; 
    std::cout<<"Se repite: "<< contador << " veces"<< std::endl;
    std::cout<<"En: " <<  cronometro.tiempo() << " " << " segundos" << std::endl;

    return 0;
}