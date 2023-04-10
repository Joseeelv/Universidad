/*
Jose Luis Venega Sánchez
Practica 0 de POO
*/
#include "cadena.hpp"
#include <iostream>
#include <cstring> // cstring != string 0_0
#include <stdexcept>
//----IMPLEMENTACION DE LOS CONSTRUCTORES----
//constructor
Cadena::Cadena(size_t tam, char caracter):s_{new char[tam+1]}, tam_{tam}{
    while(tam-->0){
        s_[tam] = caracter;
    }
    s_[tam_] = '\0';

}
//constructor de copia
Cadena::Cadena(const Cadena& cadena):s_{new char[cadena.tam_+1]},tam_{cadena.tam_}{
    strcpy(s_,cadena.s_); //copiamos una cadena con el tamaño y el contenido
}
//constructor a partir de una cadena
Cadena::Cadena(const char* cadena):s_{new char[strlen(cadena)+1]}, tam_{strlen(cadena)}{
    strcpy(s_,cadena);//copiamos la cadena
}

//constructor de movimiento
Cadena::Cadena(Cadena&& cadena): s_{cadena.s_}, tam_{cadena.tam_}{
    cadena.tam_=0;//tamaño a 0 se invoca al destructor
    cadena.s_ = new char[1]; //contiene un unico elemento
    cadena[0] = '\0';// cadena vacía
}

//cadena de bajo nivel
Cadena::operator const char* () const noexcept{
    const char* cad= s_;
    return cad;
}

//----IMPLEMENTACION DEL OPERADOR DE ASIGNACION
Cadena& Cadena::operator =(const Cadena& cadena){ //por copia
    if(this != &cadena){ //evitamos la autoasignacion
        delete[] s_; //eliminamos la cadena original
        s_=new char[cadena.tam_+1]; //creamos una nueva cadena
        tam_ = cadena.tam_;
        strcpy(s_,cadena.s_);
    }
    return *this; //devolvemos la misma cadena
}
Cadena& Cadena::operator =(Cadena&& cadena){ //asignar una cadena por movimiento "no constante"
    if(this != &cadena)
    {//evitamos la autoasignacion
        delete[] s_;//eliminamos la cadena de caracteres anterior
        tam_ = cadena.tam_; //el tamaño de la cadena a mover
        s_ = cadena.s_; //asignamos la cadena a mover
        cadena.tam_=0; //tamaño a 0
        cadena.s_ = new char[1];
        cadena[0] = '\0';//cadena vacía
    }
    return *this; //devolvemos cadena
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
    // if(a.length()!= b.length()) return false; //si las longs de las cadenas 
    //                                          //son difrentes sale falso
    // else{
    //     //comprobamos que los caracteres son los mismos
    //     for(unsigned i=0; i<a.length() && b.length(); i++){
    //         a.at(i)==b.at(i);
    //     }
    // }
    return (strcmp(&a[0], &b[0])==0); //si las cadenas son iguales devuelve 0
}
bool operator !=(const Cadena& a, const Cadena& b){
    return!(a==b);//a través de la sobrecarga de "==" comprobamos
                  //que no sean iguales las cadenas
   
}
bool operator <(const Cadena& a, const Cadena& b){
    return (strcmp(&a[0], &b[0])<0);//
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
    if(i<tam_){
        return s_[i]; //devuelve el valor del indice
    }
    else throw std::out_of_range("ERROR AT(): FUERA DE RANGO");

}

const char& Cadena::at(size_t i)const{
    if(i<tam_){
        return s_[i]; //devuelve el valor del indice
        
    }
    else throw std::out_of_range("ERROR AT(): FUERA DE RANGO");
}

//----IMPLEMENTACION METODO SUBCADENA----
Cadena Cadena::substr(size_t i, size_t tam) const{
    //comprobamos que no se sale de rango la cadena
    if(i+tam > tam_|| tam > tam_ || i > tam_){
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

//----IMPLEMENTACION OPERADOR DE EXTRACCION----
std::ostream& operator <<(std::ostream& os, const Cadena& cadena) noexcept{
    //salida por pantalla de la cadena
        os<<cadena.operator const char* ();
        return os;
}

//----IMPLEMENTACION OPERADOR DE INSERCCION----
std::istream& operator >>(std::istream& is,  Cadena& cadena){
    //Entrada por teclado de la cadena
    char cadenita[33]=""; //cadena de bajo nivel de 30 caracteres, siendo el 31 '\0'
    is.width(33);
    is >> cadenita;
    cadena = cadenita;
    return is;
}
//----IMPLEMENTACION DEL DESTRUCTOR----
Cadena::~Cadena(){
    delete[] s_;
    tam_ =0;
}


//ya se realizó todo lo pedido en la P0
/*
----PRÁCTICA 1----
    (✅) Implementar los operadores de extraccion e insercion
    (✅) Implementar los constructores de movimiento

----PRRÁCTICA 2----
*/
