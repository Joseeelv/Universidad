/*
Jose Luis Venega Sánchez
Practica 0 de POO
*/
#include "cadena.hpp"
#include <iostream>
#include <cstring> // cstring != string 0_0

//----IMPLEMENTACION DE LOS CONSTRUCTORES----
//constructor
Cadena::Cadena(size_t tam, char caracter):s_{new char[tam+1]}, tam_{tam}{
    while(unsigned i = 0 < tam_){
        s_[i] = caracter;
        s_[tam_] = '\0';
        i++;
    }
}
//constructor de copia
Cadena::Cadena(const Cadena& cadena):s_{new char[cadena.tam_+1]},tam_{cadena.tam_}{
    strcpy(s_,cadena.s_); //copiamos una cadena con el tamaño y el contenido
}
//constructor a partir de una cadena
Cadena::Cadena(const char* cadena):s_{new char[strlen(cadena)+1]}, tam_{strlen(cadena)}{
    strcpy(s_,cadena);//copiamos la cadena
}
//----IMPLEMENTACION DEL OPERADOR DE ASIGNACION
Cadena& Cadena::operator=(const Cadena& cadena){
    if(this != &cadena){ //evitamos la autoasignacion
        delete[] s_; //eliminamos la cadena original
        s_=new char[cadena.tam_+1]; //creamos una nueva cadena
        tam_ = cadena.tam_;
        strcpy(s_,cadena.s_);
    }
    return *this; //devolvemos la misma cadena
}

//----IMPLEMENTACION CONCATENACION ----
//operador +=
Cadena& Cadena::operator+=(const Cadena& cadena){
    char* auxiliar = new char[tam_+1]; //creamos una cadena auxiliar 
    strcpy(auxiliar,s_);//copiamos en cadena auxiliar la cadena original
    tam_ += cadena.tam_; //aumentamos el tamaño cadena original añadiendole el de la cadena a sumar
    delete[] s_; //eliminamos la cadena original
    s_ = new char[tam_+1]; //creamos una nueva cadena

    strcpy(s_,auxiliar); //copiamos la cadena original anterior en la nueva
    strcat(s_,cadena.s_);//concatenamos las cadenas (original + nueva)

    delete[] auxiliar; //eliminamos la cadena auxiliar
    return *this; //devolvemos la cadena concatenada 
}
//operador +
Cadena operator+(const Cadena& a, const Cadena& b){
    Cadena auxiliar(a); //creamos una cadena uxiliar con el contenido de la cadena a
    return auxiliar += b; //devolvemos la suma de las cadenas usando el operador sobrecargado +=
}

//----IMPLEMENTACION OPERADORES LÓGICOS----
bool operator ==(const Cadena& a, const Cadena& b){
    return (strcmp(a,b)==0);
}
bool operator !=(const Cadena& a, const Cadena& b){
    //si son diferentes devuelve un valor !=0
    return !(strcmp(a,b));
}
bool operator <(const Cadena& a, const Cadena& b){
    return a<b;
}
bool operator >(const Cadena& a, const Cadena& b){
    //si a>b <--> b<a
    return b<a;
}
bool operator <=(const Cadena& a, const Cadena& b){
    // a <= b <--> !(b<a)
    return !(b<a);
}
bool operator >=(const Cadena& a, const Cadena& b){
    //a>=b <--> !(a<b)
    return !(a<b);
}
//hacemos uso del operador sobrecargado "<" al igual que en la clase fecha

//----IMPLEMENTACION METODOS AT---- 
char& Cadena::at(size_t i){
    //comprobamos que i no se pasa del tamaño
    if(i>tam_){
        throw std::out_of_range("ERROR AT(): FUERA DE RANGO");
    }
    else return s_[i]; //devuelve el valor del indice
}
const char& Cadena::at(size_t i)const{
    if(i>tam_){
        throw std::out_of_range("ERROR AT(): FUERA DE RANGO");
    }
    else return s_[i]; //devuelve el valor del indice
}

//----IMPLEMENTACION METODO SUBCADENA----
Cadena Cadena::substr(size_t i, size_t tam) const{
    //comprobamos que no se sale de rango la cadena
    if(i+tam > tam_ || tam > tam_ || i > tam_){
        throw std::out_of_range("ERROR: EL TAMAÑO Y EL INDICE FUERA DE RANGO");
    }
    else{
        Cadena cad(tam); //creamos una cadena cuyo tamaño es el introducido anteriormente
        //procedemos a guardar los caracteres que empiezan en i y tiene tamaño tam
        strncpy(cad.s_,s_+i,tam);
        cad.s_[tam]='\0';//el tamaño termina con el caracter terminador
        return cad; //devolvemos la cadena
    }
}
//----IMPLEMENTACION DEL DESTRUCTOR----
Cadena::~Cadena(){
    delete[] s_;
    tam_ =0;
}

