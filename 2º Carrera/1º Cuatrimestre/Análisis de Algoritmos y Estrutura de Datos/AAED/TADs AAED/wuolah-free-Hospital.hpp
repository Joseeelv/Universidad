#ifndef _HOSPITAL_HPP_
#define _HOSPITAL_HPP_
#include"listavec.h"
#include<iostream>
#include<cassert>

/*Especificacion:*/
/*Hospital(size_t uci,size_t planta):
	·Precondicion:-------.
	·Postcondicion:Crea un Consultorio vacio. Inicializamos los tamanos de las listas.
*/
/*void ingresoPaciente(const Paciente& P):
	·Precondicion:El paciente no debe estar ingresado.
	·Postcondicion:Ingresa al paciente P.

*/
/*void altaPaciente(const Paciente& P):
	·Precondicion:El paciente debe estar ingresado.
	·Postcondicion:El paciente es dado de alta.
*/
/*void pacientesUci()const:
	·Precondicion:-------.
	·Postcondicion:Muestra los pacientes de la Uci.
*/
/*void pacientesPlanta()const:
	·Precondicion:-------.
	·Postcondicion:Muestra los pacientes de la Planta.
*/
/*~Hospital():
	·Precondicion:-------.
	·Postcondicion:Destruye el hospital.
*/

struct Paciente{
	double Id;
	size_t gravedad;
};

//Por comodidad.
typedef typename Lista<Paciente>::posicion posicion;

class Hospital{
public:
	Hospital(size_t uci,size_t planta);
	void ingresoPaciente(const Paciente& P);
	void altaPaciente(const Paciente& P);
	void pacientesUci()const;
	void pacientesPlanta()const;
	~Hospital();
private:
	size_t tamUci,tamPlanta;
	Lista<Paciente> Uci(tamUci);
	Lista<Paciente> Planta(tamPlanta);
};

//Constructor:
Hospital::Hospital(size_t uci,size_t planta):tamUci(uci),tamPlanta(planta){}

//Funcion ingresoPaciente:
void Hospital::ingresoPaciente(const Paciente& P)
{
	//Nos aseguramos de que no este ingresado ya.
	assert(Uci.buscar(P)==Uci.fin());
	assert(Planta.buscar(P)==Planta.fin());
	
	//Dependiendo de la gravedad, va a una lista.
	if(P.gravedad<5){
		posicion p=Uci.fin();
		Uci.insertar(P,p);
	}else
	{
		posicion p=Planta.fin();
		Planta.insertar(P,p);
	}
} 

//Funcion altaPaciente:
void Hospital::altaPaciente(const Paciente& P)
{
	//Nos aseguramos de que este ingresado.
	assert(Uci.buscar(P)!=Uci.fin());
	assert(Planta.buscar(P)!=Planta.fin());

	//Dependiendo de la gravedad, va a una lista.
	if(P.gravedad<5){
		posicion p=Uci.buscar(P);
		Uci.eliminar(p);
	}else
	{
		posicion p=Planta.buscar(P);
		Planta.eliminar(p);
	}
}

//Funcion pacientesUci:
void Hospital::pacientesUci()const
{
	for(posicion p=Uci.primera();p!=Uci.fin();p=Uci.siguiente(p))
	{
		cout << "Id: " << Uci.elemento(p).Id << "Gravedad: " << Uci.elemento(p).gravedad << endl;
	}
}

//Funcion pacientesPlanta:
void Hospital::pacientesPlanta()const
{
	for(posicion p=Planta.primera();p!=Planta.fin();p=Planta.siguiente(p))
	{
		cout << "Id: " << Planta.elemento(p).Id << "Gravedad: " << Planta.elemento(p).gravedad << endl;
	}	
}

#endif