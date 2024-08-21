#ifndef CONSULTORIO_HPP__
#define CONSULTORIO_HPP__

#include <iostream>
#include "Lista.hpp"
#include "Cola.hpp"

struct Paciente{
    int numero;
    Paciente(int turno):numero(turno){}
};

struct Medico{
    int id;
    Medico(int identificador):id(identificador){}
    Cola<Paciente>consulta;
};
class Consultorio{
    public:
        Consultorio(){}; //consultorio vacio
        void AltaMedico(int );
        void BajaMedico(int );
        void PacienteEspera(const Paciente&  , int);
        Paciente ConsultaPaciente(int )const;
        void Atender(int);
        bool Pacientes(int) const;
        ~Consultorio();
        //creamos un método específico para comprobar que el médico existe en el consultorio, devuelve TRUE si encuentra el medico en el consultorio
        bool ExisteMedico(int) const;

    private:
    //lista de medicos del consultorio
    Lista<Medico>consultorio;
};
typedef typename Lista<Medico>::posicion posicion;

//Implementacion del método específico del TAD
bool Consultorio::ExisteMedico(int idmed)const{
    //definimos m como la primera posicion de la lista consultoio
    posicion m = consultorio.primera();
    //recorremos toda la lista comprobando si el Medico introducido está en el consultorio
    for (m;m!=consultorio.fin();m=consultorio.siguiente(m)){
        if(consultorio.elemento(m).id == idmed){
            return true;
        }
    }
    return false;
}

void Consultorio::AltaMedico(int idmed){
    //comprobamos que el medico no está en la lista
    if(!ExisteMedico(idmed)){
        consultorio.insertar(idmed,consultorio.fin());
    }
}

void Consultorio::BajaMedico(int idmed){
    //comprobamos que el médico está en la lista
    if(ExisteMedico(idmed)){
        //declaramos m como primera posicion de la lista
        posicion m = consultorio.primera();
        for(m;m!=consultorio.fin();m=consultorio.siguiente(m)){
            consultorio.eliminar(m);
        }
    }
}

void Consultorio::PacienteEspera(const Paciente& pac, int idmed){
    //comprobamos que el medico está en el consultorio
    if(ExisteMedico(idmed)){
        //reccorremos la lista para acceder al medico una vez que hemos comprobado que existe
        posicion m = consultorio.primera();
        for(m;m!=consultorio.fin();m=consultorio.siguiente(m)){
            if(idmed == consultorio.elemento(m).id){ //encontramos el medico y le añadimos el paciente a la cola
                consultorio.elemento(m).consulta.push(pac);
            }
        }
    }
}
Paciente Consultorio::ConsultaPaciente(int idmed)const{
    //comprobamos que exista el medico
    if(ExisteMedico(idmed)){
        //si existe vamos a encontrarlo y devolver el paciente que sera atendido
        //declaramos m como la primera posicion del consultorio
        posicion m = consultorio.primera();
        for(m;m!=consultorio.fin();m=consultorio.siguiente(m)){
            if(consultorio.elemento(m).id == idmed){
                return consultorio.elemento(m).consulta.frente();
            }
        }
    }
}

void Consultorio::Atender(int idmed){
    //comprobamos que existe el medico en el consultorio, si es asi eliminamos el paciente del tope de la cola
    if(ExisteMedico(idmed)){
        posicion m = consultorio.primera();
        for(m;m!=consultorio.fin();m=consultorio.siguiente(m)){
            if(consultorio.elemento(m).id==idmed){
                consultorio.elemento(m).consulta.pop();
            }
        }
    }
}

bool Consultorio::Pacientes(int idmed)const{
    //comprobamos que el medico existe y verificamos que su cola de pacientes no esté vacia
    if(ExisteMedico(idmed)){
        posicion m = consultorio.primera();
        for(m;m!=consultorio.fin();m=consultorio.siguiente(m)){
            if(consultorio.elemento(m).id==idmed){
                consultorio.elemento(m).consulta.vacia();
            }
        }
    }
}

//destructor
Consultorio::~Consultorio(){
    //destruimos la cola de cada Medico y luego la lista de medico
    posicion m = consultorio.primera();
    for(m;m!=consultorio.fin();m=consultorio.siguiente(m)){
        consultorio.elemento(m).consulta.~Cola();
    }
    consultorio.~Lista();
}
#endif