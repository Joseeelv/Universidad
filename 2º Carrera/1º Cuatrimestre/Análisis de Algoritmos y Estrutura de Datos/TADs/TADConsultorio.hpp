#ifndef CONSULTORIO_HPP
#define CONSULTORIO_HPP

#include <iostream>
#include "listaenla.hpp"
#include "colaenla.hpp"

class Consultorio{
    public:
        //Métodos del TAD
        Consultorio(){}
        void setMedico(size_t);
        void deletMedico(size_t);
        void setPaciente(size_t, size_t);
        size_t getPaciente(size_t);
        void deletPaciente(size_t);
        bool getListaespera(size_t);

    private:
        struct Medico{
            Medico(size_t i=0):idM_(i){}
            size_t idM_;
            Cola<size_t>pacientes; //Cola de pacientes
        };
        Lista<Medico> consultorio; //lista de medicos del consultorio
        Lista<Medico>::posicion findMedico(size_t);
};
Lista<Consultorio::Medico>::posicion Consultorio::findMedico(size_t id){
    //Vamos a buscar al médico
    Lista<Medico>::posicion p = consultorio.primera();
    while(consultorio.elemento(p).idM_!=id){
        p = consultorio.siguiente(p);
    }
    return p;
}
void Consultorio::setMedico(size_t id){
        Medico med(id);
        consultorio.insertar(med,consultorio.fin());
}

void Consultorio::deletMedico(size_t id){
    consultorio.eliminar(findMedico(id));
}

void Consultorio::setPaciente(size_t id, size_t pac){
    consultorio.elemento(findMedico(id)).pacientes.push(pac);
}
size_t Consultorio::getPaciente(size_t id){
    return consultorio.elemento(findMedico(id)).pacientes.frente();
}

void Consultorio::deletPaciente(size_t id){
    consultorio.elemento(findMedico(id)).pacientes.pop();
}

bool Consultorio::getListaespera(size_t id){
    return !(consultorio.elemento(findMedico(id)).pacientes.vacia());
}
#endif // !CONSULTORIO_HPP
