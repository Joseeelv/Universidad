#ifndef POSTFIJO_HPP
#define POSTFIJO_HPP
#include <iostream>
#include "pilaenla.h"
#include <string.h>
using namespace std;

struct  Variable{
    char nombre_;
    size_t valor_;
    Variable(char nombre=' ', size_t valor = 0): nombre_ (nombre),valor_(valor){}
};

size_t findIndice(const Variable v[], char nombre){
    int p=-1;
    for(size_t i=0; v[i].nombre_!='\0'; i++){
        if(v[i].nombre_ == nombre){
            p=i;
        }
    }
    return p;
}

int getResultadoExpresion(const string& expresion, const Variable v[]){
    //Creamos la pila para almacenar la expresión
    Pila<size_t>pila;
    for(char c : expresion){
        if(isalpha(c)){ //es una variable
            int indice = findIndice(v,c);
            if(indice != -1){
                pila.push(v[indice].valor_);
            }
        }else if(c=='+' || c=='-' || c=='*' || c=='/'){ //es un operador artimetico
            int operando2 = pila.tope(); pila.pop();
            int operando1 = pila.tope(); pila.pop();
            int resultado=0.0; //variable donde vamos a almacenar el resultado
            switch(c){
                case '+': resultado = operando1+operando2;
                            break;
                case '-': resultado = operando1-operando2;
                            break;
                case '*': resultado = operando1*operando2;
                            break;
                case '/': resultado = operando1 / operando2;
                            break;
            }
            pila.push(resultado);
        }
    }
    return pila.tope();
}

#endif // !POSTFIJO_HPP