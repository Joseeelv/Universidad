#include <cassert>
#include <iostream>
#include "polinomio.h"
using namespace std;

polinomio::polinomio(unsigned gradoMax){
    gMax= gradoMax; //se guarda el grado maximo del polinomio
    monomio = gradoMax +1 ;
    coef = new double[monomio];

    for(unsigned i=0; i<=monomio;i++){
        coef[i]=0;
    } 
}

unsigned polinomio::grado(){
    unsigned gradoAct;
    for(unsigned i=0; i<=monomio; i++){
        if(coef[i] !=0) gradoAct = i;
    }

    return gradoAct -1 ;
}

double polinomio::coeficiente (unsigned n) const{
    if(n>gMax) return 0;
    else return coef[n]
}

void polinomio::coeficiente(unsigned n, double c){
    assert(n<=gMax);
    coef[n] = c;
}

void polinomio::imprime() const{
    unsigned gradoAct;
    for(unsigned i=0; i<=monomio; i++){
        if(coef[i]!=0) gradoAct=i;
    }

    cout<<"Polinomio de grado: "<<gradoAct<<endl;

    for(unsigned i=gradoAct; i>=0, i--){
        cout<<coef[i]<<"x^"<<i<<" ";
    }
    cout<<coef[0]<<endl;
}

//implementacion de las sobrecarga de operadores

polinomio operator + (const polinomio& p1, const polinomio& p2){
    unsigned gMax, gMin; //declaramos variables para el grado max y min del polinomio

    if(p1.grado()>p2.grado()){
        gMax=p1.grado();
        gMin=p2.grado();
    }
    else{
        gMax=p2.grado();
        gMin=p1.grado();
    }
    
    polinomio suma(gMax);

    for(unsigned i=0; i<=gMax; i++){
        if(i<=gMin) suma.coeficiente(i,p1.coeficiente(i)+p2.coeficiente(i));
        else suma.coeficiente(i,p1.coeficiente(i));
    }
    return suma;
}

polinomio operator - (const polinomio& p1, const polinomio& p2){
    //parecido al operadot +

    unsigned gMax, gMin; //declaramos variables para el grado max y min del polinomio

    if(p1.grado()>p2.grado()){
        gMax=p1.grado();
        gMin=p2.grado();
    }
    else{
        gMax=p2.grado();
        gMin=p1.grado();
    }
    
    polinomio resta(gMax);

    for(unsigned i=0; i<=gMax; i++){
        if(i<=gMin) resta.coeficiente(i,p1.coeficiente(i)-p2.coeficiente(i));
        else resta.coeficiente(i,p1.coeficiente(i));
    }
    return resta;
}

polinomio operator * (const polinomio& p1, const polinomio& p2){
    polinomio p(p1.grado()+p2.grado()); //sumamos los grados de los polinomio

    for(unsigned i=0;i<= p1.grado();i++){
        for(unsigned j=0;j<=p2.grado();j++){
            p.coeficiente((p1.grado()-i + p2.grado()-j),
                p.coeficiente(p1.grado()-i+p2.grado()-j)+ p1.coeficiente(p1.grado()-i)*p2.coeficiente(p2.grado()-j));
        }
    }
    return p; //devolvemos el polinomio resultado de la multiplicacion
}

