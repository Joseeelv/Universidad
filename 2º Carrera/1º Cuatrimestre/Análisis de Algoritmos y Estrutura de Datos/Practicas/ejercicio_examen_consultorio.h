#ifndef CONSULTORIO_H
#define CONDULTORIO_H
#include <cassert>
#include "ColaD.h"
#include "ListaE.h"
/*
Especificacion: Un consultorio es una secuencia de medicos de longitud n>=0 
donde cada medico tiene una cola de pacientes que están en espera. Si n=0 
significa que no hay pacientes y por ende la cola esta vacía

Identificador: Nos sirve para identficar un medico dentro de un consultorio.Los
medicos se ordenan de forma lineal. Todos menos el primero tienen un predecesor y todos 
menos el ultimo tienen un sucesor

Paciente: es una entidad que se asocia a los medicos en una consulta para que sean atendidos

Operaciones del TAD:
    
    consultorio();
    Postcondicion: crea un consultorio vacío

    void altaM();
    Postcondicion: añade un medico a la lista

    void bajaM(int );
    Precondicion: id del medico pertenece al consultorio
    Postcondicion: elimina un mnedico

    void lista_esperaP(int , &paciente);
    Precondicion: id del medico pertenece al consultorio
    Postcondicion: añade al paciente a la lista de espera (lo pone el ultimo de la cola)

    paciente consultarP(int ) const;
    Precondicion: id medico pertenece al consultorio
    Postcondicion: devuelve el valor del paciente

    void atenderP(int );
    Precondicion: Id medico pertenece al consultorio
    Postcondicion: Atiende al paciente(lo pone el primero)

    bool paciente_espera(int ) const;
    Precondicion: id medico pertenece al consultorio
    Postcondicion: devuelve true si tiene a algun paciente en espera si no false
    
Metodos utilizados de otros TADS:
    template <typename T> cola<T>::cola();
    template <typename T> void cola<T>::push(const cola<T>& C);
    template <typename T> void cola<T>::pop();
    template <typename T> const T& cola<T>::frente();
    template <typename T> bool T& cola<T>::vacia();
    template <typename t> cola<T>::~cola();

    template <typename L> lista<L>::lista();
    template <typename L> void lista<L>::insertar(const L& x, posicion p);
    template <typename L> void lista<L>::eliminar(posicion p);
    template <typename L> const L& lista<L>::elemento(posicion p);
    template <typename L> posicion lista<L>::primera();
    template <typename L> posicion lista<L>::siguiente(posicion p);
    template <typename L> lista<L>::~lista();


IMPLEMENTACION:
    Los medicos se representan con colas donde de almacenan los pacientes, mientras
    que los consultorios sera una lista de medicos, es decir, una lista de cola de pacientes

    Como no nos especifica un numero determinado de pacientes por médico y de médicos en sí
    se llevará a cabo una implementación dinamica simplemente enlazada y con cabecera del TAD lista

*/
class consultorio{
    typedef ListaE<medico>::posicion identificador;
    public:
        struct paciente
        {
            int numero;
        };
        consultorio(); //constructor
        void altaM();// da de alta a un medico
        void bajaM(identificador id);//da de baja a un medico
        void lista_espera(identificador id, paciente pac);
        const paciente& consultarP(identificador id) const;
        void atender(identificador id);
        bool paciente_espera(identificador id) const;
        ~consultorio();//destructor

    private:
    struct medico
    {
        ColaD<paciente> cola;
        medico(); //constructor de medico
    };
    ListaE<nodo> C;
};
//IMPLEMENTACION DE LOS METODOS

//Constructor de consultorio

consultorio::consultorio(){} //Consultorio vacío

void consultorio::altaM(){
    C.insertar(new nodo,C.primera()); //Los nuevos medicos se insertan al inicio de la cola
}

void consultorio::bajaM(identificador id){
    C.eliminar(id);
}

void consultorio::lista_espera(identificador id, paciente pac){
    C.elemento(id).cola.push(pac);
}
const paciente& consultorio::consultarP(identificador id) const{
    return(C.elemento(id).cola.frente());
}

void consultorio::atender(identificador id){
    C.elemento(id).cola.pop();
}
bool consultorio::paciente_espera(identificador id) const{
    return C.elemento(id).cola.vacia();
}

consultorio::~consultorio(){
    identificador idini = C.primera;
    while(idini!=C.fin()){ //llamamos al destructor de cada cola
        C.elemento(idini).cola.~Cola();
        idini=C.siguiente(idini);
    }
    C.~lista();//llamamos al destructor de la lista
}
#endif

//metodos de la Cola
// template <typename C> cola<C>::cola();  //Ctor
// template <typename C> void cola<C>::push(const Cola<C>& x); //introducir elemento
// template <typename C> void cola<C>::pop(); // sacar elemento
// template <typename C> const C& cola<C::frente(); //consulatqr elemento frente
// template ztypename C> bool cola<C>::vacia(); //ver si la cola esta vacia o no
// template <typename C> cola<C>::~cola(); //destructor


//metodos de la Lista Enlazada
// template <typename L> Lista<L>::lista(); //ctor
// template <typename L> void Lista<L>::insertar(const L& , posicion p); //insertar elemento en una posicion
// template <typename L> void Lista<L>::eliminar(posicion p); //eliminar la posicion = eliminar elemento
// template <typename L> posicion Lista<L>::primera(); //devuelve la primera posicion de la lista
// template <typename L> posicion Lista<L>::siguiente(posicion p); //avanza una posicion en la lista
// template <tyoename L> cosnt L& Lista<L>::elemento(posicion p); //devuelve el elemento de una posicion concreta
// template <typename L> posicion Lista<L>::anterior(); //devuelve la posicion anterior
// template <typename L> Lista<L>::~lista(); //destructor