#include "ListaEnla.hpp"
#include <cassert>
#include <string>

using namespace std;

struct sala{
    size_t nSala;
    listaEnla<string> Eventos;
};

class Cartelera{
    public:
        Cartelera(){}
        void insertarSala(size_t nsala);
        void insertarEvento(size_t nsala, string evento);
        void eliminarSala(size_t nsala);
        void eliminarEvento(size_t nsala, string evento);
    private:
        listaEnla<sala>::posicion buscarSala(size_t nsala);
        listaEnla<string>::posicion buscarEvento(string id, listaEnla<sala>::posicion p);
        listaEnla<sala> C;
};

listaEnla<sala>::posicion Cartelera::buscarSala(size_t nsala){
    listaEnla<sala>::posicion p = C.primera();

    while(p != C.fin()){
        if(C.elemento(p).nSala == nsala){
            break;
        }
        p = C.siguiente(p);
    }
    return p;
}

listaEnla<string>::posicion Cartelera::buscarEvento(string id, listaEnla<sala>::posicion ps){
    listaEnla<string>::posicion pe = C.elemento(ps).Eventos.primera();
    
    while(pe != C.elemento(ps).Eventos.fin()){
        if(C.elemento(ps).Eventos.elemento(pe) == id){
            break;
        }
        pe = C.elemento(ps).Eventos.siguiente(pe);
    }
    return pe;
}

void Cartelera::insertarSala(size_t nsala){
    listaEnla<sala>::posicion p = buscarSala(nsala);
    if(p == C.fin()){
        sala s;
        s.nSala = nsala;
        C.insertar(s, C.fin());
    }
}

void Cartelera::insertarEvento(size_t nsala, string evento){
    listaEnla<sala>::posicion ps = buscarSala(nsala);
    if(ps != C.fin()){
        listaEnla<string>::posicion pe = buscarEvento(evento, ps);
        if(pe == C.elemento(ps).Eventos.fin()){
            C.elemento(ps).Eventos.insertar(evento, pe);
        }
    }
}

void Cartelera::eliminarSala(size_t nsala){
    listaEnla<sala>::posicion p = buscarSala(nsala);
    if(p != C.fin()){
        C.eliminar(p);
    }
}

void Cartelera::eliminarEvento(size_t nsala, string evento){
    listaEnla<sala>::posicion ps = buscarSala(nsala);
    if(ps != C.fin()){
        listaEnla<string>::posicion pe = buscarEvento(evento, ps);
        if(pe != C.elemento(ps).Eventos.fin()){
            C.elemento(ps).Eventos.eliminar(pe);
        }
    }
}