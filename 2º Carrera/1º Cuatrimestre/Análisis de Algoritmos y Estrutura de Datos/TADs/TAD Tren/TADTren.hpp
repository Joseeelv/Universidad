/*
Tren(); //ctor
Pre:
Post: Crea Tren vacio.

void ToLeft();
Pre:
Post: desplaza tren a la izquierda -> vagon activo a la derecha

void Toright();
Pre:
Post: desplaza tren a la derecha -> vagon activo a la izquierda

void EliminaVagonA();
Pre:Tren no vacio
Post:Elimina vagon activo

void InsertaVagonA();
Pre:
Post: Añade un vagon activo, los demas a la drch.

void ObservarVagonA() const;
Pre: Tren no vacio
Post: Devuelve vagon activo

bool vacio() const;
Pre:
Post: Devuelve True si el tren está vacio, si no false
*/

#include <iostream>
#include "../pilaenla.h"//pila enlazada

template <typename vagon> class Tren{
    public:
        Tren(){}; //ctor por defecto
        void ToLeft();
        void ToRight();
        void EliminaVagonA();
        void InsertarVagonA(vagon v );
        const vagon ObservarVagonA() const;
        bool vacio() const;
        ~Tren();
    private:
        Pila<vagon>VagonI, VagonD;
        vagon Activo; //vagon aux para mover el vagon activo
};

template <typename vagon> void Tren<vagon>:: ToLeft(){
    if(!VagonD.vacio()){
        VagonI.push(Activo); //desplazo el activo a la izquierda 
        Activo = VagonD.tope(); //el nuevo activo es el vagon de la drch.
        VagonD.pop();
    }
   
}

template <typename vagon> void Tren<vagon>:: ToRight(){
    if(!VagonI.vacio()){
        VagonD.push(Activo);
        Activo = VagonI.tope(); //el nuevo activo es el vagon de la drch.
        VagonI.pop();
    } 
}

template <typename vagon> void Tren<vagon>:: EliminaVagonA(){
    if(!VagonD.vacio()){
        Activo = VagonD.tope();
        VagonD.pop();
    }
    if(VagonD.vacio() && !VagonI.vacio()){
        Activo = VagonI.tope(); 
        VagonI.pop();
    }
}

template <typename vagon> void Tren<vagon>:: InsertarVagonA(vagon v){
    VagonD.push(Activo);
    Activo = v;
}

template <typename vagon> const vagon Tren<vagon>:: ObservarVagonA() const {return Activo;}

template <typename vagon> bool vacio(){
    return (vagonI.vacia() && Activo = ' ' && VagonD.vacia());
}

