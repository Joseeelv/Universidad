#ifndef COCINA_H
#define COCINA_H

#include <cassert>
#include "ListaE.h”

//creamos la estructura mueble ya que el usuario debe de conocer que mueble quiere introducir

struct mueble{
int pos, anchura;
mueble(int a,int p): anchura(a), pos(p);{} //constructor de mueble
};	
class cocina{
	Public:
cocina(int tam);//constructor
bool colocar_mueble(int anchura, int p);
void añadir_mueble(int anchura, int p);
mueble devolver_mueble(int i) const;
void eliminar_mueble(int p);
void desplazarI(int i);
~cocina(); //destructor


	Private:
		int nMuebles,longitud;
        ListaE<muebles> L;		

};

//constructor
cocina::cocina(int tam):tam(longitud),nMuebles(0){} //crea una cocina vacia de tamaño longitud

bool cocina::colocar_mueble(int anchura, int p){
	typename ListaE<mueble>::posicion pos = L.primera();
	bool valido;
	
	while(L.elemento(pos) < p && p !=L.fin()){
	pos = L.siguiente(pos);
	}

	if(pos+anchura > L.elemento(p) || pos+anchura > longitud){
		valido=false;
	}else{
		pos = L.anterior();
	int distancia = L.elemento(pos).p+L.elemento(pos).anchura;

	if(distancia >p) valido = false; //no cabe por la izq
	else valido = true;
	}
}

void cocina::añadir_mueble(int anchura, int p){
if(L.vacia()){ //cocina está vacía
	L.insertar(mueble(anchura,p), L.primera());
}
else{
typename ListaE<mueble>:: posisicon pos != L.primera();
while(L.elemento(pos).pos < p && pos !=L.fin()){
	pos=L.siguiente(pos);
}
L.insertar(mueble(anchura,p), pos); //lo inserta en la posicion siguiente si la ListaE no está vacia
}
nMuebles ++; //se aumenta el contador el numero de muebles de la cocina
}	

mueble cocina::devolver_mueble(int i) const{
	assert(i>=0 && i<nMuebles); //comprobamos precondicion
	int j=0; 
	typename ListaE<mueble>::posicion pos = L.primera();
	
	while(j<i){
		pos = L.siguiente(pos);
		j++;
	}
	return L.elemento(pos);
}

void cocina::eliminar_mueble(int i){
	assert(i>=0 && i<nMuebles);//comprobamos que la cocina no está vacia
	typename ListaE<mueble>::posicion pos = L.primera();
	int j=0;
	
	while(j<i){
		pos = L.siguiente(pos);
		j++;
	}
	L.eliminar(pos);
	nMuebles -—;
}

void cocina::desplazarI(int i){
	assert(i>=0 && i<nMuebles); //comprobamos que la cocina no está vacia
	typename ListaE<mueble>::posicion pos = L.primera();
	typename ListaE<mueble>:: posición anterior;
	int j=0;

	while(j<i){
	pos=L.siguiente(pos);
	j++;
	}

	if(j==0){ //desplazar primer elemento
	L.elemento(pos).pos =0;
	}
	else{
	anterior= L.anterior(L.elemento(pos));
	int distancia = L.elemento(anterior).pos+L.elemento(anterior).anchura;
	L.elemento(pos).pos = distancia;
	}
}

//destructor
cocina::~cocina(){
	L.~ListaE();
}

#endif
