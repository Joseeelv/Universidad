/*1. Utilizando rand(), escriba una función que genere un número pseudoaleatorio entero en el
intervalo discreto [a, b]*/

#include <iostream>

using namespace std;

int random(int ,int ); //declaramos la funcion que nos da el numero random.

int main(){
    int a=0,b=0,r=0; //siendo el intervalo [a,b] y
    cout<<"Introduce un numero: ";
    cin>>a;

    cout<<"Introduce otro numero: ";
    cin>>b;

    r=random(a,b);
    cout<<"El numero aleatorio en el intervalo ["<<a<<" , "<<b<<"] es: "<<r<<endl;
    return 0;
}

int random(int a, int b){
    int n;
    n=a+rand()%((b-a)+1);
    return n;
}