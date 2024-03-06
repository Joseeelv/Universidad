#ifndef TREN_HPP
#define TREN_HPP
#include <iostream>
#include "pilaenla.h"

template<typename vagon>
class Tren{
    public:
        Tren(){}
        void toRight();
        void toleft();
        void deleteVagonActivo();
        void setActivo(vagon);
        vagon getActivo()const;
        bool vacio()const;
    private:
        Pila<vagon>Izq,Drch;
        //El vagon activo es Izq.tope();
};

template <typename vagon>
void Tren<vagon>::toRight(){
    //vamos a mover el vagon activo hacia la derecha (tope de la pila izq)
    assert(!vacio());
    if(!Izq.vacia()){
        Drch.push(Izq.tope());
        Izq.pop();
    }if(Izq.vacia()){ //como minimo tiene que haber un elemento
        Izq.push(Drch.tope());
        Drch.pop();
    }
}
template <typename vagon>
void Tren<vagon>::toleft(){
    assert(!vacio());
    if(!Drch.vacia()){
        Izq.push(Drch.tope());
        Drch.pop();
    }
}
template <typename vagon>
void Tren<vagon>::deleteVagonActivo(){
    if(!Izq.vacia()){
        Drch.push(Izq.tope());
        Izq.pop();
    }
    if(!Drch.vacia() && Izq.vacia()){
        Izq.push(Drch.tope());
        Drch.pop();
    }
}

template <typename vagon>
void Tren<vagon>::setActivo(vagon v){
    if (!Izq.vacia()) {
        Drch.push(Izq.tope());
        Izq.pop();
    }
    Izq.push(v);
}

template <typename vagon>
vagon Tren<vagon>::getActivo()const{
    assert(!vacio());
    return Izq.tope();
}

template <typename vagon>
bool Tren<vagon>::vacio()const{
    return Izq.vacia() && Drch.vacia();
}
#endif //Tren.hpp