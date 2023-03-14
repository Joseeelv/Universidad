#ifndef TREN_H
#define TREN_H

#include <cassert>
#include "PilaD.h"
/*Ejercicio de examen

*Definicion: Secuencia de elementos de tipo vagon, con un elemento que será
vagon activo. La secuencia empieza con el priemer elemento y acaba con el ultimo

*Operaciones del TAD TREN:

    Tren(); "constructor de tren"
        Postcondiciones: Crea un tren vacío
    
    void desplazarIzq();
        Precondiciones: Tren no vacio al menos 1 elemento
        Postcondiciones: Desplaza el tren hacia la izquierda

    void desplazarDrch();
        Precondiciones: Tren no vacío
        Postcondiciones: Desplaza el tren hacia la derechar
    
    void eliminar_vagon();
        Precondiciones: Tren no está vacio
        Postcondiciones: Eliminar un vagon del tren
    
    const vagon& observar_vagon() const;
        Precondiciones: Tren no vacio
        Postcondiciones: devuelve el valor del vagon
    
    bool vacio() const; 
        Precondiciones: Tren no vacio
        Postcondiciones: devuelve verdadero si el tren está vacio


        //suponemos que el tipo vagon ya nos lo dan hecho
*/

//IMPLEMENTACION DEL TAD

class tren{
    public:
        tren();//constructor
        void desplazarIzq();
        void desplazarDrch();
        void eleminar_vagon();
        const vagon& observar_vagon() const;
        bool vacio() const;
        ~tren();//destructor
    private:
        PilaD<vagon> I; //pila dinamica de tipo vagon (izquierda)
        pilaD<vagon> D; //la de la derecha
        //el vagon activo siempre será el que se encuentre en el tope
};

//constructor
tren::tren(){}

//desplazar a la izq
void tren::desplazarIzq(){
    assert(!vacio());//comprobamos que la pila no está vacia
    vagon aux=D.tope(); //el vagon auxiliar tomará el valor del vagon tope de la derecha
    D.pop();//eliminamos el vagon de la derecha
    if(!D.vacia()){
        I.push(aux);
    }else{
        D.push(tope());
    }
}

void tren::desplazarDrch(){
    assert(!vacio());
    if(!I.vacia()){ //si la izq no está vacia la pila D toma el valor del aux (el tope de I)
    vagon aux=I.tope();
    I.pop();
    D.push(aux)
}

void tren::eleminar_vagon(){
    assert(!D.vacio());//precondicion
    D.pop();
    if(D.vacio()){
        if(!I.vacio()){
            D.push(I.tope);
            I.pop();
        }
   }
}

const vagon& tren::observar_vagon(){ //vagon activo es decir el de la derecha
    assert(!vacio()); //tren no vacio

    return(D.tope());
}

bool tren::vacio(){
    bool aux (!I.vacia() && !D.vacia());

    return aux;
}

//destructor
tren::~tren(){
    //llamamos a los destructores de los ojetos utilizados
    I.~PilaD;
    D.~PilaD;
}
#endif