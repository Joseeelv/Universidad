/*4. Implemente el TAD Pila utilizando como representación interna una bicola. Repita el
ejercicio para el TAD Cola*/
#ifndef EJERCICIO4_H
#define EJERCICIO4_H
#include <cassert> 
#include "ejercicio3.h"//tad bicola
//ESPECIFICACIÓN DE LA PILA
template <typename T> class PilaBi
{
    public:
        PilaBi();//constructor 
        PilaBi(const PilaBi<T>& P);//constructor de copia
        PilaBi<T>& operator=(const PilaBi<T>& P);//operador de asignaion

        bool vacia() const; //metodo comprobar pila vacia
        const T& tope() const; //comprueba el tope "ultimo elemento introducido"
        void push(const T& x);//introduce elementos a la pila
        T pop();//elimina elementos de la pila

        ~PilaBi();//destructor de la pilabi

    private:
        void copia(const PilaBI<T>& P);//funcion copiar del cnstr de copia
        bicolaD<T>pila;
};

//constructor
template <typename T> inline PilaBi<T>::PilaBi(){}

//constructor de copia
template <typename T> inline PilaBi<T>::PilaBi(const PilaBi<T>&P){
    copia(P);
}

//operador de asignacion
template <typename T> PilaBi<T>& PilaBi<T>::operator= (const PilaBi<T>& P){
    if(this!= &P){//evitamos la autoasignacion de la pila
        this->~PilaBi();//llamamos al destructor
        copia(P);
    }
    return *this;
}

template <typename T> inline bool PilaBi<T>::vacia() const{
    return(pila.vacia());
}

template <typename T> inline const T& PilaBi<T>::tope()const{
    assert(!vacia());//comprobamos que no está vacía
    return pila.frenteizquierda(); //devolvemos el elemento de la izq --> tope
}

template <typename T> inline void PilaBi<T>::push(const T& x){
    pila.pushizq(x);
}

template <typename T> inline T PilaBi<T>::pop(){
    assert(!vacia());//comprobamos que no está vacía
    T elementoAux = pila.frenteizquierda();
    pila.popizq();
    return elementoAux;
}

//destructor
template <typename T> PilaBi<T>::~PilaBi(){
    pila.~bicolaD();
}

//ESPECIFICACION DE LA COLA

template <typename Telemento> class Colabi{
    public:
        Colabi();//constructor
        Colabi(const Colabi<Telemento>& C);//constructor de copia
        Colabi<Telemento>& operator=(const Colabi<T>& C);//operador de asignacion entre colas

        bool vacia() const;
        const T& frente(const Colabi<Telemento>& C);
        void push(const Colabi<Telemento>& x);
        void pop();

        ~Colabi();//destructor de la clase

    private:
        bicolaD<Telemento> cola;
        void copia(const Colabi<Telemento>& C);
};
//constructor
template <typename Telemento> inline Colabi<Telemento>::Colabi(){}

//constructor de copia
template <typename Telemento> inline Colabi<Telemento>::Colabi(const Colabi<Telemento>& C){
    copia(C);
}

//operador de asignacion entre colas
template <typename Telemento> inline Colabi<Telemento>& Colabi<Telemento>::operator=(const Colabi<Telemento>& C){
    if(this != C){//evitamos la autoasignacion
        this.~bicolaD(); //vaciamos la cola actual
        copia(C);
    }   
    return *this;
}

template <typename Telemento> inline bool Colabi<Telemento>::vacia() const{
    return(cola.vacia());
}

template <typename Telemento> inline const Telemento& Colabi<Telemento>::frente(){
    assert(!vacia());//comprobamos que la cola no está vacía
    return(cola.frenteizquierda());
}

template <typename Telemento> inline void Colabi<Telemento>::push(const Telemento& x){
    cola.push(x);
}

template <typename Telemento> inline void Colabi<Telemento>::pop(){
    assert(!vacias());//comprobamos que la cola no está vacía
    cola.popizq();
}

template <typename Telemento> Colabi<Telemento>::~Colabi(){
    cola.~bicolaD();
}
#endif //ejercicio 4.h
