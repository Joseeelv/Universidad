#include <iostream>
#include "polinomio.h"

using namespace std;

int main(){
    int a;
    polinomio p1(gradomaximo);
    polinomio p2(gradomaximo);

    do{
    cout<<"1) SUMA DE POLINOMIOS"<<endl;
    cout<<"2) RESTA DE POLINOMIOS"<<endl;
    cout<<"3) PRODUCTO DE POLINOMIOS"<<endl;
    cout<<"0) SALIR PROGRAMA"<<endl;
    cout<<"SELECCIONE UNA OPCION: ";
    cin>>a;
    cout<<"HAS SELECCIONADO: "<<a<<endl;

    switch (a)
    {
    case 1:polinomio operator + (p1,p2);
        break;
    case 2: resta_polinomios(p1,p2);
        break;
    case 3:producto_polinomios(p1,p2);
        break;
    default: return 0;
        break;
    }
    }while(a!=0);

    return 0;
}