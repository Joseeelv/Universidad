//Funciones del TAD que realizan operaciones
#ifndef Operaciones_H
#define Operaciones_H
#include "PilaD.h"

class ModText{
	public:
		explicit ModText(); //constructor de la clase
		Modtext(const &ModText);//constructor de copia
		
		void avanzarCursor(ModText& texto);
		void retrasarCursor(ModText& texto);
		
		void finlinea(ModText& texto);
		void iniciolinea(ModText& texto);
		
		void borraCaractercursor(ModText& texto);
		void borrarCaracteranterior(ModText& texto);
		
		void insertarcaracter(ModText& texto, char c);
		void sobreescribir(ModText& texto, char c);	
	private:
		PilaD<char>P,Q; //P es la parte superior y Q la inferior
};

void ModText::avanzarCursor(ModText& texto){
	texto.P.push(texto.Q.pop());
}

void ModText::retrasarCursor(ModText& texto){
	texto.Q.push(texto.P.pop());
}

void ModText::finlinea(ModText& texto) {
	while(!texto.Q.vacia()){
		texto.P.push(texto.Q.pop());
	}
}

void ModText::iniciolinea(ModText& texto){
	while(!texto.P.vacia()){
		texto.Q.push(texto.P.pop());
	}
}

void ModText::borraCaractercursor(ModText& texto){
	texto.Q.pop();
}

void ModText::borrarCaracteranterior(ModText& texto){
	texto.P.pop();
}

void ModText::insertarcaracter(ModText& texto, char c){
	texto.Q.push(c);
}

void ModText::sobreescribir(ModText& texto, char c){
	texto.Q.pop();
	texto.Q.push(c);
}
#endif //OpTAD.h
