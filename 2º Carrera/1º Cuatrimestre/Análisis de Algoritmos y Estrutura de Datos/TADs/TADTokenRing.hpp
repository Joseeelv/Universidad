#ifndef TOKENRING_HPP
#define TOKENRING_HPP
#include "listaenla.hpp"
#include <cstring>

typedef size_t Trama; //tipo ya definido por el enunciado

class TokenRing{
    public:
        TokenRing(const char*);
        void setComputador(const char*);
        void deletComputador();
        void pasaToken();
        const char* getToken();
        void pasaTrama(const char* , const char*);
    
    private:
        struct Computador{
            char idC_[9];
            bool tiene_token;
            Trama trama;
            explicit Computador(const char* identificador = " "):tiene_token(false){
                strncpy(idC_,identificador,sizeof(idC_));
            }
        };
        Lista<Computador>computadores_; //lista de computadores
        typedef Lista<Computador>::posicion posicion;
        posicion buscarComputador(const char* );
        static const size_t Nmax=25;
        
};
TokenRing::posicion TokenRing::buscarComputador(const char * nombre){
    posicion p = computadores_.fin();
    if(p==computadores_.fin()){return p;}//devuelve nulo
    else{
        while(p!=computadores_.fin()){
            if(strcmp(nombre,computadores_.elemento(p).idC_)!=0){
                p = computadores_.siguiente(p);
            }
        }
        return p;
    }
}

TokenRing::TokenRing(const char* nombre_computador){
    //vamos a inicializar la red con el numero máximo de computadores (25)
    Computador pc (nombre_computador);
    pc.tiene_token=true;
    computadores_.insertar(pc,computadores_.primera());
}

void TokenRing::setComputador(const char* nombre){
    if(computadores_.tama() < Nmax){ //hay hueco para insertar
        posicion p = buscarComputador(nombre);
        if(p!=computadores_.fin()){ //no se ha encontrado un computador con ese nombre, se puede insertar
            Computador pc(nombre);
            computadores_.insertar(pc,computadores_.fin());
        }
    }
}

void TokenRing::deletComputador(){
    if(!computadores_.vacia()){
        if(computadores_.elemento(computadores_.primera()).tiene_token) pasaToken();
        computadores_.eliminar(computadores_.primera());
    }
}

const char* TokenRing::getToken() {
    posicion p = computadores_.primera();
    while (p != computadores_.fin() && !computadores_.elemento(p).tiene_token) {
        p = computadores_.siguiente(p);
    }
    if(p!=computadores_.fin())return computadores_.elemento(p).idC_;
    else return nullptr;
}

void TokenRing::pasaToken() {
    const char* nombre = getToken();
    if (nombre != nullptr) {
        posicion p = buscarComputador(nombre);
        computadores_.elemento(p).tiene_token = false;
        p = computadores_.siguiente(p);
        if(p==computadores_.fin()){
            computadores_.elemento(computadores_.primera()).tiene_token=true;
        }
        computadores_.elemento(p).tiene_token=true;
    }
}

void TokenRing::pasaTrama(const char* pc1, const char* pc2){
    //para pasar la trama el computador pc1 debe de tener activo el token,
    //pasarle la trama y luego pasar el token
    posicion p = buscarComputador(pc1);
    if(p!=computadores_.fin() && computadores_.elemento(p).tiene_token==true){
        posicion q = buscarComputador(pc2);
        if(q!=computadores_.fin()){
         computadores_.elemento(q).trama = computadores_.elemento(p).trama;
         pasaToken();
        }
    }
}
#endif //tokenring.hpp

