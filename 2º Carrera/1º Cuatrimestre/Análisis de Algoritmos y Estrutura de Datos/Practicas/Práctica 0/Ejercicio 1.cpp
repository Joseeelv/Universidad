//1 y 2. Cual es el resultado para una temperatura 10,27 y 40.
#include <iostream>

using namespace std;

void muestra_temperatura(int );
int main(){
    int t=40;

    muestra_temperatura(t);
    return 0;
}
void muestra_temperatura(int temp){

    cout << "La temperatura es: " << temp << " grados" ;

    if(20 < temp && temp < 30)
        cout << " (normal)";
    else
        cout << " (anormal)";
    cout << endl;
}