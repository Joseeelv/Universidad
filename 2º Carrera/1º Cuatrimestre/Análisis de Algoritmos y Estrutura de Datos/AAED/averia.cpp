#include "ListaEnla.hpp"
#include <string>
#include <cassert>

using namespace std;

struct reserva{
    string id_pasajero;
    string id_vuelo;
    int numAsiento;
};

struct vuelo{
    string id_vuelo;
    int reservasMax;
    listaEnla<reserva> R;
    int horaSalida;

    listaEnla<reserva>::posicion buscaReserva(string idp);

};

class Averia{
    public:
        Averia(){}
        void nuevoVuelo(vuelo v);
        bool existeVuelo(string idv);
        void registrarReserva(string id_p, string id_v);
        bool existePasajero(string id_p, string id_v);
        listaEnla<vuelo>::posicion buscar(string id_v);
        int numReservas(listaEnla<vuelo>::posicion p);
        bool vueloLLeno(string id_v);
        int numAsiento(string idp, string idv);
        void eliminarVuelo(string idv);
        listaEnla<vuelo> listaVuelos() const;
    private:
        listaEnla<vuelo> V;
};

bool Averia::existeVuelo(string idv){
    listaEnla<vuelo>::posicion p;
    bool flag = false;
    for(p=V.primera(); p!=V.fin() && flag!=true; p = V.siguiente(p)){
        if(idv.compare(V.elemento(p).id_vuelo)==0) flag = true;
    }

    return flag;
}

int Averia::numReservas(listaEnla<vuelo>::posicion p){
    assert(existeVuelo(V.elemento(p).id_vuelo));
    
    listaEnla<reserva>::posicion p2=V.elemento(p).R.primera();
    int i;
    
    for(i = 0; p2!=V.elemento(p).R.fin(); i++, p2=V.elemento(p).R.siguiente(p2));
    return i;
}

listaEnla<vuelo>::posicion Averia::buscar(string id_v){
    listaEnla<vuelo>::posicion p;
    bool flag = false;
    
    for(p=V.primera(); p!=V.fin() && flag != true; p = V.siguiente(p)){
        if(id_v.compare(V.elemento(p).id_vuelo)==0){
            flag = true;
        }
    }

    if(flag) return V.anterior(p);
    else return p;
}

bool Averia::existePasajero(string id_p, string id_v){
    assert(existeVuelo(id_v));
    
    listaEnla<vuelo>::posicion pv = buscar(id_v);
    listaEnla<reserva>::posicion pr;
    bool flag = false;

    for(pr = V.elemento(pv).R.primera(); pr != V.elemento(pv).R.fin() && flag != true; pr = V.elemento(pv).R.siguiente(pr)){
        if (id_p.compare(V.elemento(pv).R.elemento(pr).id_pasajero)==0) flag = true;
    }

    return flag;
}

void Averia::nuevoVuelo(vuelo v){
    assert(!existeVuelo(v.id_vuelo));
    listaEnla<vuelo>::posicion p;
    for(p = V.primera(); p!=V.fin() && V.elemento(p).horaSalida<v.horaSalida; p=V.siguiente(p));
    V.insertar(v, p);
}

void Averia::registrarReserva(string id_p, string id_v){
    listaEnla<vuelo>::posicion p = buscar(id_v);
    assert(existeVuelo(id_v) && !existePasajero(id_p, id_v) && numReservas(p)<V.elemento(p).reservasMax);
    
    reserva nueva;

    nueva.id_pasajero=id_p;
    nueva.id_vuelo=id_v;
    nueva.numAsiento = numReservas(p)+1;
    
    V.elemento(buscar(id_v)).R.insertar(nueva, V.elemento(buscar(id_v)).R.fin());
}

bool Averia::vueloLLeno(string idv){
    return numReservas(buscar(idv))==V.elemento(buscar(idv)).reservasMax;
}

int Averia::numAsiento(string idp, string idv){
    assert(existeVuelo(idv));

    int asiento=0;
    if(existePasajero(idp, idv)){
        asiento = V.elemento(buscar(idv)).R.elemento(V.elemento(buscar(idv)).buscaReserva(idp)).numAsiento;
    }

    return asiento;
}

void Averia::eliminarVuelo(string idv){
    assert(existeVuelo(idv));

    V.eliminar(buscar(idv));
}

listaEnla<vuelo> Averia::listaVuelos()const{
    return V;
}