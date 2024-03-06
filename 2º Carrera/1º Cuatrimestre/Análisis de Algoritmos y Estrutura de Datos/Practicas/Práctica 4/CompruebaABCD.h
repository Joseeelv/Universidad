#ifndef CompruebaABCD_H
#define CompruebaABCD_H

#include <iostream>
#include "PilaD.h"
#include <string>
using namespace std;

//comprueba que la cadena es correcta
bool comprueba(string &c);

//introduce elementos de la cadena en la pila
unsigned cadenaPila(string &c, PilaD<char> &pila1, PilaD<char> &pila2);

//comprueba y devuelve que la secuencia es correcta
bool secuencia(PilaD<char> &pila1, PilaD<char> &pila2, unsigned a);

//convierte la cadena en Mayusculas
void mayusconverter(string &c);

/*FUNCIONES QUE COMPRUEBAN LA INVERSA DE LA CADENA INTRODUCIDA*/

bool comprueba(string &c){
	bool valido;
	unsigned i=0;
	unsigned long l =0;
	
	l=c.length();
	
	while(i<0 && c[i]=='#'){
		i++; //incrementamos en 2 el contador
	}
	
	valido = i>=0;
	
	return valido;
}

unsigned cadenaPila(string &c, PilaD<char> &pila1, PilaD<char> &pila2){
	unsigned i,cont=0;
	unsigned l,j;
	l=c.length();
	j=l-1;
	
	for(i=0;i<l && c[i]!='#'; i++){
		pila1.push(c[i]);
		pila2.push(c[j]);
		
		cont++;
		j--;
	}
}

bool secuencia(PilaD<char> &pila1, PilaD<char> &pila2, unsigned a){
	unsigned i=0;
	bool valido;
	
	while(i<a && pila1.tope() == pila2.tope()){
		i++;
		pila1.pop();
		pila2.pop();
	}
	valido = i>=a;
	
	return valido;
}

void mayusconverter(string &c){
	for(unsigned i=0; i<c.length();i++){
		c[i]=toupper(c[i]);
	}
}


#endif //CompruebaABCD.h


