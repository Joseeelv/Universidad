//Funciones que invierten la sencuencia de numeros respecto a los numeros a y b introducidos
#ifndef Ocurrencia_H
#defina Ocurrencia_H

#include <iostream>
#include "PilaD.h"
#include <string>
using namesapace std;

//Precondicion: la pila tiene que tener un inicio y un fin y debe de contener al menos 2 elementos
//Postcondicion: devuelve una pila cuyos elementos estan invertidos en el intervalo inicio fin "a" "b".
template <typename tElemento> PilaD<tElemento> invSec(tElemento inicio, tElemento fin, PilaD<tElemento> pila);

template <typename tElemento> 
PilaD<tElemento> invSec(tElemento inicio, tElemento fin, PilaD<tElemento> pila){
	pilaD<tElemento> pilaux; //creamos una pila donde se copiará la secuencia invertida
	pilaD<tElemento> pilaF;	//creamos una pila que contendrá el resultado de la inversion
	
	//Recorremos la pila original desde el tope hasta el elemento final que se desea invertir
		while(pila.tope()!=fin){
			pilaF.push(pila.pop()); //mientras no llega al elemento final de la secuencia se copia el elemento en la pila final
		}
		
	//Recorremos la pila origen desde el final hasta el inicio y guarda los elementos en la pila auxiliar
		while(pila.tope() != inicio){
			pilaux.push(pila.pop());
		}	pilaux.push(pila.pop()); //se hace una vez más para almacenar el elemento que está en el inicio
		
	//Copiamos los elementos invertidos en la pila final
		while(!pilaux.vacia()){
			pilaF.push(pilaux.pop());
		}
		
	//Copiamos en la pila original los elementos invertidos
		while(!pila.vacia()){
			pilaF.push(pila.pop());
		}
		
	//Imprimimos la secuencia
		while(!pilaF.vacia()){
			cout<<pilaF.tope()<<" ";
			pila.push(pilaF.pop());
			cout<<endl;
		}
	//Llamamos a los destructores de la pila
	
	pilaF.~PilaD();
	pilaux.~PilaD();
}

#endif //Ocurrencia.h
	
