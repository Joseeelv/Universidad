#ifndef _TREN_HPP_
#define _TREN_HPP_
#include"pila_enla.h"
#include<cassert>

/*Especificacion:*/
/*Tren():
	·Precondicion:-------.
	·Postcondicion:Crea un Tren vacio.
*/
/*void moverIzqda():
	·Precondicion:-------.
	·Postcondicion:Mueve el tren de la derecha un paso a la izquierda, si no hay vagon derecho no hace nada.
*/
/*void moverDrcha():
	·Precodicion:--------.
	·Postcondicion:Mueve el tren de la izquierda un paso a la derecha, si no hay vagon izquierdo no hace nada.
*/
/*void eliminarActivo():
	·Precondicon:Tren no vacio.
	·Postcondicion:Se suprime el vagon activo y se convierte en activo el que esta inmediatamente a su derecha. Si este no existe, activa el de su izquierda,
	 si tampoco eziste, el tren queda vacio.
*/
/*void insertarActivo(const vagon& v):
	·Precondicion:-------.
	·Postcondicion:Inserta un nuevo vagon activo desplazando al antiguo a la derecha.
*/
/*vagon vagonActivo()const:
	·Precondicion:Tren no vacio.
	·Postcondicion:Devuelve el vagon activo.
*/
/*bool vacio()const:
	·Precondicion:-------.
	·Postcondicion:Devuelve true si esta vacio, false si no lo esta.
*/

class Tren{
public:
	Tren();
	void moverIzqda();
	void moverDrcha();
	void eliminarActivo();
	void insertarActivo(const vagon& v);
	int vagonActivo()const;
	bool vacio()const;
private:
	Pila<vagon> Izqda;
	Pila<vagon> Drcha;

};

//Constructor:
Tren::Tren(){}

//Funcion moverIzqda:
void Tren::moverIzqda()
{
	//Si la pila derecha esta vacia no hace nada.
	if(!Drcha.vacia())
	{
		Izqda.push(Drcha.tope());
		Drcha.pop();
		//Si una vez realizada la operacion derecha esta vacia, da marcha atras.
		if(!Drcha.vacia())
		{
			Drcha.push(Izqda.tope());
			Izqda.pop();
		}
	}
}

//Funcion moverDrcha:
void Tren::moverDrcha()
{
	//Si la pila izquierda esta vacia no hace nada.
	if(!Izqda.vacia())
	{
		Drcha.push(Izqda.tope());
		Izqda.pop();
	}
}

//Funcion eliminarActivo:
void Tren::eliminarActivo()
{
	assert(!Drcha.vacia());
	Drcha.pop();
	if(Drcha.vacia())
	{
		moverDrcha();
	}
}

//Funcion insertarActivo:
void Tren::insertarActivo(int v)
{
	Drcha.push(v);
}

//Funcion vagonActivo:
vagon Tren::vagonActivo()const
{
	assert(!Drcha.vacia());
	return Drcha.tope();
}

//Funcion vacio:
bool Tren::vacio()const
{
	//Izqda podra estar vacia, la que indica si definitivamente el tren esta vacio es la Drcha, luego solo assert derecha.
	if(Drcha.vacia())
	{
		return true;
	}
	else
	{
		return false;
	}
}

#endif