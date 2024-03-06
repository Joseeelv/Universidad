/*3. Utilizando rand(), escriba una función que genere un número pseudoaleatorio de coma
flotante y precisión doble en el intervalo continuo [a, b]*/

#include<iostream>
using namespace std;

void random(int,int);

int main(){
    int a,b;//intervalo [a,b]

    cout<<"Introduce un numero: ";
    cin>>a;

    cout<<"Introduce otro numero: ";
    cin>>b;

    random(a,b);

    return 0;
}
void random(int a, int b){
    double n;
    n= a+double(rand())/(RAND_MAX+(b-a)+1);
    cout<<"El numero aleatorio en el intervalo ["<<a<<" , "<<b<<"] es: "<<n<<endl;
}