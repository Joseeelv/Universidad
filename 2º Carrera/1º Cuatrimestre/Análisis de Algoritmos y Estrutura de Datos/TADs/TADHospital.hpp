#ifndef HOSPITAL_HPP
#define HOSPITAL_HPP
#include <iostream>
#include "listavec.h"
#include <cassert>

class Hospital{
    public:
        Hospital(size_t , size_t);
        void setPaciente(size_t,size_t );
        void Alta(size_t );
        void Muerte(size_t);
        inline size_t getPacientesUCI()const{return UCI.tama();}
        inline size_t getPacientesPlanta()const{return Planta.tama();};
        size_t getPacientesGravedad(size_t)const;
        //Dtor predeterminado

    private:
        struct Paciente{
            size_t cod_,gravedad_;
            Paciente(size_t codigo=0, size_t gravedad=0):cod_(codigo), gravedad_(gravedad){}
        };
        Lista<Paciente>UCI,Planta;
        typedef Lista<Paciente>::posicion posicion;
        posicion buscaPacienteUCI(size_t);
        posicion buscaPacientePlanta(size_t);
        posicion MenosGraveUCI()const;
        posicion MenosGravePlanta()const;
};
//Métodos privados de la clase
Hospital::posicion Hospital::buscaPacienteUCI(size_t codigo){
    posicion p = UCI.primera();
    while(p!=UCI.fin() && UCI.elemento(p).cod_ != codigo){
        p=UCI.siguiente(p);
    }
    return p;
}

Hospital::posicion Hospital::buscaPacientePlanta(size_t codigo){
    posicion p = Planta.primera();
    while(p!=Planta.fin()&& Planta.elemento(p).cod_ != codigo){
        p = Planta.siguiente(p);
    }
    return p;
}

Hospital::posicion Hospital::MenosGraveUCI()const{
    size_t menos_grave = 0; //guardará la gravedad más leve
    posicion p = UCI.primera();
    posicion pmg = UCI.primera();
    while(p!=UCI.fin()){
        if(UCI.elemento(p).gravedad_ > menos_grave){
            menos_grave = UCI.elemento(p).gravedad_;
            pmg = p;
        }
        p = UCI.siguiente(p);
    }
    return pmg; //devolvemos la posicion del paciente menos grave 
}

Hospital::posicion Hospital::MenosGravePlanta()const{
    size_t menos_grave = 0;
    posicion p = Planta.primera();
    posicion pmg = Planta.primera();
    while(p!=Planta.fin()){
        if(Planta.elemento(p).gravedad_>menos_grave){
            menos_grave = Planta.elemento(p).gravedad_;
            pmg =p;
        }
        p = Planta.siguiente(p);
    }
    return pmg;
}
Hospital::Hospital(size_t nPacUci, size_t npacPlanta):UCI(nPacUci), Planta(npacPlanta){}

void Hospital::setPaciente(size_t codigo, size_t gravedad){
    assert(gravedad>=1 && gravedad <=9); //comprobamos que la gravedad sea válida
    Paciente pac(codigo,gravedad);
    if(pac.gravedad_ <= 5 ){ //UCI
        //Comprobamos que la uci no esté llena
        if(UCI.tama() < UCI.tamaMax()){
            UCI.insertar(pac,UCI.fin());
        }else{ //UCI llena, menos grave a la planta
            posicion p = MenosGraveUCI(); //guardamos la posicion del menos grave
            if(Planta.tama() == Planta.tamaMax()){//Planta llena, elimino el menos grave.
                posicion q = MenosGravePlanta();
                Planta.eliminar(q);
            }
            Planta.insertar(UCI.elemento(p),Planta.fin()); //insertamos en la planta
            UCI.eliminar(p); //eliminamos de la uci
            //insertamos nuevo paciente en la uci
            UCI.insertar(pac,UCI.fin());
        }
    }else//Planta
        //Compruebo que la planta no esté llena
        if(Planta.tama() == Planta.tamaMax()){
            posicion p = MenosGravePlanta();
            Planta.eliminar(p); //se elimina el menos grave
        }
        Planta.insertar(pac,Planta.fin());
}
void Hospital::Alta(size_t codigo){
    //SOlo se le da el alta al paciente de la planta
    posicion p = buscaPacientePlanta(codigo);
    Planta.eliminar(p);
}

void Hospital::Muerte(size_t codigo){
    posicion p = buscaPacienteUCI(codigo);
    if(p == UCI.fin()){
        posicion q = buscaPacientePlanta(codigo);
        Planta.eliminar(q);
    }else UCI.eliminar(p);//lo mete en la morgue = lo eliminas del hospital
}
size_t Hospital::getPacientesGravedad(size_t gravedad)const{
    assert(gravedad >= 1 && gravedad <= 9);
    size_t contador = 0;
    if(gravedad <= 5){ //Buscamos UCI
        posicion p = UCI.primera();
        while(p!=UCI.fin()){
            if(UCI.elemento(p).gravedad_ == gravedad) contador++;
            p = UCI.siguiente(p);
        }
    }else{
        posicion p =Planta.primera();
        while(p!=Planta.fin()){
            if(Planta.elemento(p).gravedad_ == gravedad) contador++;
            p = Planta.siguiente(p);
        }
    }
    return contador;
}
#endif
