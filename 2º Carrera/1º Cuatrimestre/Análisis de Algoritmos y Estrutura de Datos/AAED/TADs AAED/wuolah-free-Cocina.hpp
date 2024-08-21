#ifndef _COCINA_HPP_
#define _COCINA_HPP_
#include"lista_doble.h"
#include<cassert>
#include<iostream>

/*Especificacion*/
/*Cocina(double Tam):
	·Precondicion:-------.
	·Postcondicion:Crea una cocina vacia.
*/
/*bool cabe(const Mueble& M,double pos)const:
	·Precondicion:-------.
	·Postcondicion:Devuelve true si el mueble cabria en la pos dada, false si no.
*/
/*void insertar(const Mueble& M,double pos):
	·Precondicion:EL mueble puede ser insertado.
	·Postcondicion:Inserta el mueble en la cocina.
*/
/*Mueble iesimoVer(size_t i)const:
	·Precondicion:Debe existir el mueble iesimo.
	·Postcondicon:Devuelve el mueble i-esimo.
*/
/*void iesimoErase(size_t i):
	·Precondicion:-------.
	·Postcondicion:Eliminar el mueble i-esimo si existiese.
*/
/*void moverIzq(size_t i);
	·Precondicion:-------.
	·Postcondicion:Mover a la izquierda el mueble i-esimo hasta pegarlo a otro muble o la pared, si el i-esimo existiese.
*/
/*~Cocina();
	·Precondicion:-------.
	·Postcondicion:Destruye la cocina.
*/

struct Mueble{
	double DPIzq_;
	double Tam_;
	//Constructor para definit muebles.
	Mueble(double Tam=0,double DPIzq=0):Tam_(Tam),DPIzq_(DPIzq){}
	//Cambiar DPizq_
	void cambiarDPIzq(double nuevo){this->DPIzq_=nuevo;}
};

//Por comodidad.
typedef typename Lista<Mueble>::posicion posicion;

class Cocina{
public:
	Cocina(double Tam);
	bool cabe(const Mueble& M,double pos)const;
	void insertar(Mueble& M,double pos);
	Mueble iesimoVer(size_t i)const;
	void iesimoErase(size_t i);
	void moverIzq(size_t i);
	~Cocina(){};
private:
	double Tam_;
	Lista<Mueble> Mu;
	size_t numMuebles()const;
};

//Constructor:
Cocina::Cocina(double Tam):Tam_(Tam){}

//Funcion cabe:
bool Cocina::cabe(const Mueble& M,double pos)const
{
	if(M.Tam_+pos>Tam_)
	{
		//Si no cabe directamente.
		return false;
	}
	for(posicion p=Mu.primera();p!=Mu.fin();p=Mu.siguiente(p))
	{
		if(pos==Mu.elemento(p).DPIzq_)
		{
			//Si encuentra una posicion donde sea == a la DPIzq de un mueble, devuelve false.
			return false;
		}
		if(pos<Mu.elemento(p).DPIzq_ && M.Tam_+pos>Mu.elemento(p).DPIzq_)
		{
			//Si el mueble empieza antes de DPIzq de un mueble ya acaba despues, devuelve false.
			return false;
		}
		if(pos>Mu.elemento(p).DPIzq_ && pos<Mu.elemento(p).DPIzq_+Mu.elemento(p).Tam_)
		{
			//Si el mueble empieza despues de DPIzq de un mueble pero antes de DPIzq+Tam del mueble, devuelve false.
			return false;
		}
		if(pos<Mu.elemento(p).DPIzq_ && M.Tam_+pos>Mu.elemento(p).DPIzq_+Mu.elemento(p).Tam_)
		{
			return false;
		}

	}
	return true;
}

//Funcion insertar:
void Cocina::insertar(Mueble& M,double pos)
{
	//Nos aseguramos de que el mueble quepa.
	assert(cabe(M,pos));
	M.cambiarDPIzq(pos);
	//Mantendremos el orden al insertar el nuevo mueble.
	bool x=false;

	//Si esta vacia.
	if(Mu.primera()==Mu.fin())
	{
		Mu.insertar(M,Mu.primera());
	}else
	{
		for(posicion p=Mu.primera();p!=Mu.fin() && x==false;p=Mu.siguiente(p))
		{
			if(M.DPIzq_<Mu.elemento(p).DPIzq_)
			{
				x=true;
				Mu.insertar(M,p);
			}
		}
		//Si no se ha insertado es porque es el mayor.
		if(x==false)
		{
			Mu.insertar(M,Mu.fin());
		}
	}
}

//Funcion iesimoVer:
Mueble Cocina::iesimoVer(size_t i)const
{
	//Comprobamos que exista el mueble i-esimo.
	std::cout << numMuebles() << std::endl;
	assert(i<=numMuebles());
	size_t j=0;
	for(posicion p=Mu.primera();p!=Mu.fin();p=Mu.siguiente(p)){
		j++;
		if(j==i)
		{
			return Mu.elemento(p);
		}
	}
}

//Funcion iesimoErase:
void Cocina::iesimoErase(size_t i)
{
	size_t j=0;
	for(posicion p=Mu.primera();p!=Mu.fin();p=Mu.siguiente(p)){
		j++;
		if(j==i)
		{
			Mu.eliminar(p);
		}
	}
}

//Funcion moverIzq:
void Cocina::moverIzq(size_t i)
{
	size_t j=0;
	for(posicion p=Mu.primera();p!=Mu.fin();p=Mu.siguiente(p)){
		j++;
		if(j==i)
		{
			if(p==Mu.primera())
			{
				//Si es el primero lo pegamos a la pared.
				Mu.elemento(p).cambiarDPIzq(0);
			}else
			{
				//Si no, lo pegamos al anterior.
				posicion p1=Mu.anterior(p);
				Mu.elemento(p).cambiarDPIzq(Mu.elemento(p1).DPIzq_+Mu.elemento(p1).Tam_);
			}
		}
	}
}

//Funciones privadas:
//Funcion numMuebles()const:
//Devuelve el numero de muebles en la cocina.
size_t Cocina::numMuebles()const
{
	size_t i=0;
	for(posicion p=Mu.primera();p!=Mu.fin();p=Mu.siguiente(p))
		i++;
	return i;
}

#endif