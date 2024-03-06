/*2. Escriba un programa que simule 10 000 000 de tiradas de un dado. Imprima las frecuencias
relativas que se obtienen para cada una de las caras. Emplee la función del ejercicio anterior.*/

#include <iostream>
using namespace std;

int random (int,int);

int main(){
    int i=0,n=100000;//contador del bucle, n numero de veces que se tira el dado
    int a=1,b=6;//intervalo de las caras de un dado [1,6]
    int r=0; //numero random obtenido
    int f1=0,f2=0,f3=0,f4=0,f5=0,f6=0; ///frecuencia de cada cara
    cout<<"-FRECUENCIAS RELATIVAS DE LAS CARAS DE UN DADO-"<<endl;

    while(i<n){ //condicion para no salir del bucle
        r=random(a,b);

        //cout<<"NUMERO SACADO: "<<r<<endl;

            switch (r)
        {
        case 1: ++f1; //se incrementa en 1 cada vez que salga el numero
            break;
        case 2: ++f2;
            break;
        case 3: ++f3;
            break;
        case 4: ++f4;
            break;
        case 5: ++f5;
            break;
        case 6: ++f6;
            break;
        default:
            break;
        }
        i++; //incrementamos el contador del bucle
    }

    

    cout<<"Las Frecuencias serian: "<<endl;
    cout<<"El numero 1 sale: " <<f1<<endl;
    cout<<"El numero 2 sale: " <<f2<<endl;
    cout<<"El numero 3 sale: " <<f3<<endl;
    cout<<"El numero 4 sale: " <<f4<<endl; 
    cout<<"El numero 5 sale: " <<f5<<endl; 
    cout<<"El numero 6 sale: " <<f6<<endl; 

    
 return 0;
}

int random(int a, int b){
    int valor;//valor obtenido

    valor=a+rand()%((b-a)+1);

    return valor;
}