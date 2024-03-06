#ifndef HIPERMERCADO_HPP
#define HIPERMERCADO_HPP
#include <iostream>
#include "listavec.h"
#include <cassert>
struct Caja{
    Caja(bool estado=false, size_t cajero=0, double recaudacion=0.0):abierta_(estado),idCajero_(cajero),recaCaja_(0.0){}
    bool abierta_;
    double recaCaja_;
    size_t idCajero_;
};

class Hipermercado{
    public:
        Hipermercado():lc(Lista<Caja>(ncajas_)),recaTotal_(0.0){
            for(unsigned i =0; i<ncajas_;i++){
                lc.insertar(Caja(),lc.fin());
            }
        }
        void setCaja(size_t, size_t);
        double cierraCaja(size_t);
        void getDinero(double,size_t);
        void cambiaCajero(size_t,size_t);
        double cambiaTurno();
        double cierraHipermercado();
    private:
        const static size_t ncajas_ = 50;
        double recaTotal_;
        Lista<Caja>lc;
        Lista<Caja>::posicion buscaCaja(size_t );
};
typedef Lista<Caja>::posicion posicion;

//Nos creamos un método auxiliar para buscar la caja
Lista<Caja>::posicion Hipermercado::buscaCaja(size_t idcaja){
    posicion p = lc.fin();
    if(lc.vacia()){return p;}
    if(idcaja <= ncajas_){
       p = lc.primera();
        size_t i = 0;
        while(p!=lc.fin() && i == idcaja){
                i++;
                p = lc.siguiente(p);
        }
    }
    return p;
}

void Hipermercado::setCaja(size_t idcaja, size_t cajero){
    if(idcaja <= ncajas_){
        posicion p = buscaCaja(idcaja);
        if( p!= lc.fin()){
            lc.elemento(p).idCajero_ = cajero;
            lc.elemento(p).abierta_ = true;
            lc.elemento(p).recaCaja_ = 0.0;
        }
    }
}
double Hipermercado::cierraCaja(size_t caja){
    posicion p = buscaCaja(caja);
    if(p==lc.fin()){
        return 0.0;
    }
    lc.elemento(p).idCajero_ = 0;
    lc.elemento(p).abierta_ = false;
    recaTotal_ = recaTotal_ + lc.elemento(p).recaCaja_;
    return lc.elemento(p).recaCaja_;
}
void Hipermercado::getDinero(double dinero, size_t caja){
    posicion p = buscaCaja(caja);
    if(p!=lc.fin()){
        lc.elemento(p).recaCaja_ += dinero;
    }
}
void Hipermercado::cambiaCajero(size_t caja,size_t cajero){
    posicion p = buscaCaja(caja);
     if(p!=lc.fin()){
        lc.elemento(p).idCajero_ = cajero;
    }

}

double Hipermercado::cambiaTurno(){
    double dineroTurno=0.;
    posicion p = lc.primera();
    for(;p!=lc.fin();p=lc.siguiente(p)){
        dineroTurno += lc.elemento(p).recaCaja_;;
    }
    return dineroTurno;
}
double Hipermercado::cierraHipermercado(){
    posicion p = lc.primera();
    double dinero =0.0;
    while(p!=lc.fin()){
        dinero += lc.elemento(p).recaCaja_;
        lc.elemento(p).abierta_=false;
        lc.elemento(p).recaCaja_=0.0;
        lc.elemento(p).idCajero_ =0;
        p = lc.siguiente(p);
    }
    return dinero;
}

#endif // hipermercado.hpp