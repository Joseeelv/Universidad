#ifndef _DICCIONARIO_HPP_
#define _DICCIONARIO_HPP_
#include<iostream>
#include<cstring>
#include<cassert>
#include"lista_doble.h"

/*Especificacion:*/
/*Diccionario():
	·Precondicion:-------.
	·Postcondicion:Crea un Diccionario vacio.
*/
/*void insertarInglesa(const PInglesa& PI):
	·Precondicion:La palabra no esta insertada.
	·Postcondicion:Inserta la palabra.
*/
/*void insertarTraduccion(const PInglesa& PI,const PEspanola& PE):
	·Precondicion:La palabra inglesa esta insertada y esa traduccion no existe.
	·Postcondicion:Inserta la traduccion PE de la PI.
*/
/*void eliminarTraduccion(const PInglesa& PI,const PEspanola& PE):
	·Precondicion:La palabra inglesa esta insertada y esa traduccion existe.
	·Postcondicion:Elimina la traduccion PE de la PI.
*/
/*void verTraducciones(const PInglesa& PI)const:
	·PrecondicionLa PI eesta insertada.
	·Postcondicion:Imprime la traducciones, si esta vacia no imprime nada.
*/

struct PEspanola{
	std::string palabra_;
	PEspanola(std::string palabra=""):palabra_(palabra){}
	inline operator const char*()const{return palabra_.c_str();}
};

struct PInglesa{
	std::string palabra_;
	Lista<PEspanola> Traducciones;
	PInglesa(std::string palabra=""):palabra_(palabra){}
	inline operator const char*()const{return palabra_.c_str();}
};

//Por comodidad.
typedef typename Lista<PInglesa>::posicion posicion;
typedef typename Lista<PEspanola>::posicion posicion1;

class Diccionario{
public:
	Diccionario();
	void insertarInglesa(const PInglesa& PI);
	void insertarTraduccion(const PInglesa& PI,const PEspanola& PE);
	void eliminarTraduccion(const PInglesa& PI,const PEspanola& PE);
	void verTraducciones(const PInglesa& PI)const;
	void verInglesas()const;
	~Diccionario(){}
private:
	Lista<PInglesa> PInglesas;
};

//Constructor:
Diccionario::Diccionario(){}

//Funcion insertarInglesa:
void Diccionario::insertarInglesa(const PInglesa& PI)
{
	//Nos aseguramos que no este insertada.
	assert(PInglesas.buscar(PI)==PInglesas.fin());
	//Insertamos.
	PInglesas.insertar(PI,PInglesas.fin());
}

//Funcion insertarTraduccion:
void Diccionario::insertarTraduccion(const PInglesa& PI,const PEspanola& PE)
{
	//Nos aseguramos que la palabra exista.
	assert(PInglesas.buscar(PI)!=PInglesas.fin());
	//No aseguramos que no exista esa traduccion.
	posicion p=PInglesas.buscar(PI);
	assert(PInglesas.elemento(p).Traducciones.buscar(PE)==PInglesas.elemento(p).Traducciones.fin());
	//Insertamos.
	PInglesas.elemento(p).Traducciones.insertar(PE,PInglesas.elemento(p).Traducciones.fin());
}

//Funcion eliminarTraduccion:
void Diccionario::eliminarTraduccion(const PInglesa& PI,const PEspanola& PE)
{
	//Nos aseguramos que la palabra exista.
	assert(PInglesas.buscar(PI)!=PInglesas.fin());
	//No aseguramos que exista esa traduccion.
	posicion p=PInglesas.buscar(PI);
	assert(PInglesas.elemento(p).Traducciones.buscar(PE)!=PInglesas.elemento(p).Traducciones.fin());
	//Eliminamos.
	posicion1 p1=PInglesas.elemento(p).Traducciones.buscar(PE);
	PInglesas.elemento(p).Traducciones.eliminar(p1);
}

//Funcion verTraducciones:
void Diccionario::verTraducciones(const PInglesa& PI)const
{
	//Nos aseguramos que la palabra existe.
	assert(PInglesas.buscar(PI)!=PInglesas.fin());
	posicion p=PInglesas.buscar(PI);
	std::cout << "Traducciones para la palabra: " << PI.palabra_ << std::endl;	
	for(posicion1 p1=PInglesas.elemento(p).Traducciones.primera();p1!=PInglesas.elemento(p).Traducciones.fin();p1=PInglesas.elemento(p).Traducciones.siguiente(p1))
	{
		if(PInglesas.elemento(p).Traducciones.siguiente(p1)!=PInglesas.elemento(p).Traducciones.fin())
		{
			std::cout << PInglesas.elemento(p).Traducciones.elemento(p1).palabra_ << ", ";
		}else
		{
			std::cout << PInglesas.elemento(p).Traducciones.elemento(p1).palabra_ << ".";
		}
	}
	std::cout << std::endl;
}

//Funcion verInglesas:
void Diccionario::verInglesas()const
{
	std::cout << "Palabras inglesas del diccionario:"<< std::endl;
	for(posicion p=PInglesas.primera();p!=PInglesas.fin();p=PInglesas.siguiente(p))
	{
		if(PInglesas.siguiente(p)!=PInglesas.fin())
		{
			std::cout << PInglesas.elemento(p).palabra_ << ", ";
		}else
		{
			std::cout << PInglesas.elemento(p).palabra_ << ".";
		}
	}
	std::cout << std::endl;
}

#endif