#ifndef COCINA_HPP
#define COCINA_HPP

#include <iostream>
#include "listadoble.h"

struct Mueble{
            double ancho_,pos_;
            Mueble(double a = 0, double p =0):pos_(p),ancho_(a){}
};
class Cocina{
    public:
        Cocina(double l):longitud_(l){}
        bool colocarse(double,double);
        void setMueble(double,double);
        const Mueble& getMueble(unsigned)const;
        void eliminaMueble(unsigned);
        void MovMueble(unsigned);
    private:
        double longitud_;
        Lista<Mueble>cocina;
};
typedef Lista<Mueble>::posicion posicion;

bool Cocina::colocarse(double a, double pos){
    //Para colocarse debe de caber en la longitud de la cocina
    //y que no haya otro mueble colocado en su posicion
    Mueble mueble(a,pos);
    if(mueble.pos_ + mueble.ancho_ > longitud_) return false;
    posicion p = cocina.primera();
    //vamos a recorrer la lista de muebles para ver si es colocable
    for( ; p!=cocina.fin() && mueble.pos_ + mueble.ancho_ <= cocina.elemento(p).pos_ ;p=cocina.siguiente(p)){
        //si es mayor que el mueble anterior no se puede colocar
        if(mueble.pos_ >= cocina.elemento(cocina.anterior(p)).pos_ + cocina.elemento(cocina.anterior(p)).ancho_)return false;
    }
    return true; //es colocable

}

void Cocina::setMueble(double ancho ,double pos){
    Mueble m(ancho,pos);
    //ahora vamos a buscar donde se va a insertar
    posicion p = cocina.primera();
    for( ;p!=cocina.fin() && m.pos_ + m.ancho_ <= cocina.elemento(p).pos_ ;p=cocina.siguiente(p)){
        cocina.insertar(m,p);
    }
}

const Mueble& Cocina::getMueble(unsigned id)const{
    posicion p = cocina.primera();
    if(id <= cocina.tama()){ //existe el id
        for(unsigned i = 0; i+1 < id;i++){ //buscamos el id
            p = cocina.siguiente(p); //guardamos la posicion
        }
    }
    return cocina.elemento(p); //devolvemos el mueble
}

void Cocina::eliminaMueble(unsigned id) {
    // Comprobamos que está en la cocina
    if (id <= cocina.tama()) {
        posicion p = cocina.primera();
        // Si estamos eliminando el primer elemento, actualizamos el puntero
        if (id == 1) {
            cocina.eliminar(p);
        } else {
            for (unsigned i = 0; i + 1 < id; i++) {
                p = cocina.siguiente(p);
            }
            cocina.eliminar(p);
        }
    }  
}

void Cocina::MovMueble(unsigned id){
    //Comprobamos que existe
    if(id<=cocina.tama()){
        posicion p = cocina.primera();
        //Vamos a moverlo hacia la pared si está en el primero
        if(id == 1){cocina.elemento(p).pos_=0;}
        else {//está en otra posicion -> se pega al de su izquierda
            for(unsigned i=0; i<=id ;i++){
                p=cocina.siguiente(p);
            }
            cocina.elemento(p).pos_= cocina.elemento(cocina.anterior(p)).pos_ + cocina.elemento(cocina.anterior(p)).ancho_;
        }
    }
}
#endif // !COCINA_HPP