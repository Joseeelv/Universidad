#ifndef _ESCALONADA_HPP_
#define _ESCALONADA_HPP_
#include"lista_doble.h"
#include<iostream>
#include<cassert>
#include<limits>

/*Especificacion:*/
/*Escalonada(const Salto& S):
	·Precondicion:-------.
	·Postcondicion:Crea un Escalonada vacio.
*/
/*void insertar(const Salto& S):
	·Precondicion:El punto de inicio debe estar definido en nuestra funcion.
	·Postcondicion:Inserta el salto en la Funcion.
*/
/*void eliminar(double P):
	·Precondicion:El punto debe estar definido en nuestra funcion.
	·Postcondicion:Eliminar el Salto en ese punto.
*/
/*double valorPunto(double P):
	·Precondicion:El punto debe estar definido en nuestra funcion.
	·Postcondicion:Devuelve el valor de la funcion en el punto P.
*/
/*double valorMax():
	·Precondicion:-------.
	·Postcondicion:Devuelve el valor maximo de la Funcion.
*/
/*doule valorMin():
	·Precondicion:--------.
	·Postcondicion:Devuelve el valor minimo de la Funcion.
*/
/*void traslacion(double x,double y):
	·Precondicion:-------.
	·Postcondicion:Realiza la traslacion de la funcion.
*/
/*~Escalonada():
	·Precondicion:-------.
	·Postcondicion:Destruye la funcion.
*/

struct Salto{
	double xi,yi;
	Salto(double x=0.0,double y=0.0):xi(x),yi(y){}
};

//Por comodidad:
typedef typename Lista<Salto>::posicion posicion;

class Escalonada{
public:
	Escalonada(const Salto& S);
	void insertar(const Salto& S);
	void eliminar(double P);
	double valorPunto(double P)const;
	double valorMax()const;
	double valorMin()const;
	void traslacion(double x,double y);
	void ver()const;
	~Escalonada(){}
private:
	Lista<Salto> Saltos;
};

//Constructor:
Escalonada::Escalonada(const Salto& S)
{
	//Insertamos en la lista el Salto a partid del cual partira.
	Saltos.insertar(S,Saltos.primera());
}

//Funcion insertar:
void Escalonada::insertar(const Salto& S)
{
	//Nos aseguramos de que el punto este definido.
	assert(S.xi>=Saltos.elemento(Saltos.primera()).xi);
	bool ok=false;
	for(posicion p=Saltos.primera();p!=Saltos.fin() && ok==false;p=Saltos.siguiente(p))
	{
		//Si comienzan en el mismo sitio.
		if(Saltos.elemento(p).xi==S.xi)
		{
			Saltos.eliminar(p);
			Saltos.insertar(S,p);
			ok=true;
		}
		//Si es estrictamente mayor, la insertamos ahi.
		if(Saltos.siguiente(p)!=Saltos.fin())
		{
			if(Saltos.elemento(p).xi<S.xi && Saltos.elemento(Saltos.siguiente(p)).xi>S.xi)
			{
				p=Saltos.siguiente(p);
				Saltos.insertar(S,p);
				ok=true;
			}
		}else
		{
			if(Saltos.elemento(p).xi<S.xi)
			{
				p=Saltos.siguiente(p);
				Saltos.insertar(S,p);
				ok=true;
			}
		}
	}
}

//Funcion eliminar:
void Escalonada::eliminar(double P)
{
	//Nos aseguramos de que el punto este definido.
	assert(P>=Saltos.elemento(Saltos.primera()).xi);
	//No debe solo quedar una posicion.
	assert(Saltos.primera()!=Saltos.fin());
	bool ok=false;
	posicion p;
	for(p=Saltos.primera();p!=Saltos.fin() && ok==false;p=Saltos.siguiente(p))
	{
		if(Saltos.siguiente(p)!=Saltos.fin())
		{
			if(Saltos.elemento(p).xi<=P && Saltos.elemento(Saltos.siguiente(p)).xi>P)
			{
				Saltos.eliminar(p);
				ok=true;
			}
		}else
		{
			if(Saltos.elemento(p).xi<=P)
			{
				goto fin;

			}
		}
	}
	fin:
	if(ok==false)
	{
		Saltos.eliminar(p);
	}
}

//Funcion valorPunto:
double Escalonada::valorPunto(double P)const
{
	//Nos aseguramos de que el punto este definido.
	assert(P>=Saltos.elemento(Saltos.primera()).xi);
	//Si esta definido procedemos.
	for(posicion p=Saltos.primera();p!=Saltos.fin();p=Saltos.siguiente(p))
	{
		//Si es el 'ultimo' Salto.
		if(Saltos.siguiente(p)==Saltos.fin())
		{
			return Saltos.elemento(p).yi;
		}else
		{
			if(P>=Saltos.elemento(p).xi && P<Saltos.elemento(Saltos.siguiente(p)).xi)
			{
				return Saltos.elemento(p).yi;
			}
		}
	}
}

//Funcion valorMax:
double Escalonada::valorMax()const
{
	double max=std::numeric_limits<double>::min();
	for(posicion p=Saltos.primera();p!=Saltos.fin();p=Saltos.siguiente(p))
	{
		if(Saltos.elemento(p).yi>max)
		{
			max=Saltos.elemento(p).yi;
		}
	}
	return max;
}

//Funcion valorMin:
double Escalonada::valorMin()const
{
	double min=std::numeric_limits<double>::max();
	for(posicion p=Saltos.primera();p!=Saltos.fin();p=Saltos.siguiente(p))
	{
		if(Saltos.elemento(p).yi<min)
		{
			min=Saltos.elemento(p).yi;
		}
	}
	return min;
}

//Funcion traslacion:
void Escalonada::traslacion(double x,double y)
{
	for(posicion p=Saltos.primera();p!=Saltos.fin();p=Saltos.siguiente(p))
	{
		Saltos.elemento(p).xi=Saltos.elemento(p).xi+x;
		Saltos.elemento(p).yi=Saltos.elemento(p).yi+y;
	}
}

//Funcion observadora:
void Escalonada::ver()const
{
	for(posicion p=Saltos.primera();p!=Saltos.fin();p=Saltos.siguiente(p))
	{
		std::cout << "xi: " << Saltos.elemento(p).xi << "  yi: " << Saltos.elemento(p).yi << std::endl;
	}
}


#endif