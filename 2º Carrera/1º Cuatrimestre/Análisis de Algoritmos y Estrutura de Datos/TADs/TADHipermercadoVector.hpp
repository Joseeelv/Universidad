#ifndef HIPERMERCADO_HPP
#define HIPERMERCADO_HPP
#include <iostream>
#include <vector>
struct Caja{
    Caja(bool estado=false, size_t cajero=0, double recaudacion=0.0):abierta_(estado),idCajero_(cajero),recaCaja_(0.0){}
    bool abierta_;
    double recaCaja_;
    size_t idCajero_;
};

class Hipermercado{
    public:
        Hipermercado():lc(std::vector<Caja>(ncajas_)),recaTotal_(0.0){}
        void setCaja(size_t, size_t);
        double cierraCaja(size_t);
        void getDinero(double,size_t);
        void cambiaCajero(size_t,size_t);
        double cambiaTurno();
        double cierraHipermercado();
    private:
        const static size_t ncajas_ = 50;
        double recaTotal_;
        std::vector<Caja>lc;
};

void Hipermercado::setCaja(size_t idcaja, size_t cajero){
    if(idcaja <= ncajas_){ 
        lc[idcaja].idCajero_ = cajero;
        lc[idcaja].abierta_ = true;
        lc[idcaja].recaCaja_ = 0.0;
    }
}
double Hipermercado::cierraCaja(size_t caja){
    lc[caja].idCajero_ = 0;
    lc[caja].abierta_ = false;
    recaTotal_ = recaTotal_ + lc[caja].recaCaja_;
    return lc[caja].recaCaja_;
}
void Hipermercado::getDinero(double dinero, size_t caja){
    lc[caja].recaCaja_ += dinero;
}
void Hipermercado::cambiaCajero(size_t caja,size_t cajero){
        lc[caja].idCajero_ = cajero;
}

double Hipermercado::cambiaTurno(){
    double dineroTurno=0.;
    for(unsigned i = 0; i<ncajas_; i++){
        dineroTurno += lc[i].recaCaja_;;
    }
    return dineroTurno;
}
double Hipermercado::cierraHipermercado(){
    double dinero =0.0;
    for(unsigned i =0; i<ncajas_;i++){
        dinero += lc[i].recaCaja_;
        lc[i].abierta_=false;
        lc[i].recaCaja_=0.0;
        lc[i].idCajero_ =0;
    }
    return dinero;
}
#endif //hipermercado.hpp