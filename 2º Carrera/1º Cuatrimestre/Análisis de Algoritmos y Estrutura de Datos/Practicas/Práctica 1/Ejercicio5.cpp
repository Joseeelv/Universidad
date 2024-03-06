/*5. Escriba un programa que genere 10 000 000 de permutaciones pseudoaleatorias de los 6
primeros números naturales e imprima cuántas de ellas están ordenadas*/
#include<iostream>
#include<algorithm>
using namespace std;

bool compara(int [],int []); //declaramos la funcion que comprueba si está ordenado o no el vector
int main(){
    int vi[]={2,6,5,3,1,4}; //vector a ordenar
    int vf[]={1,2,3,4,5,6};//resultado de ordenar el vector
    int n=10,i=0;//sea n el numero de permutaciones e i el contador del bucle
    int nOrdenadas=0;//numero de veces que permuta el vector
    
    while(i<n){
        if(compara(vi,vf)) nOrdenadas++;
        random_shuffle(vi,vi+n);//permuta el vector
        i++;//incrementamos el contador vector
    }
    cout<<"El vector esta ordenado: "<<nOrdenadas<<" veces"<<endl;
    return 0;

}

bool compara(int vi[], int vf[]){
    for(int i=0;i<6;i++){
     if(vi[i]!=vf[i]) return false;
    }
    return true;

}