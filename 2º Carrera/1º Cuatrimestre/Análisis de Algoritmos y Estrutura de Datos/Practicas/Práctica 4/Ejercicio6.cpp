/*Se desea implementar una funci�n que simule el juego del solitario de las dos cartas. Los
elementos que intervienen en este juego son:
Mazo: Contiene (boca abajo) las cartas por colocar.
Mont�n de descartes: Contiene las cartas (boca arriba) en proceso de colocaci�n.
Bases: Cuatro, una por palo, en las que se van colocando las cartas (boca arriba) de
cada palo, en orden creciente.
Objetivo: Colocar la totalidad de las cartas sobre sus bases correspondientes.*/

#include <iostream>
#include "solitario.h"
#include <stdlib.h>
using namesapce std;

bool solitario(tMazo mazo){
	//Solo se es accesible a la carta que est� m�s arriba del monton del mazo
	tCarta* mano = new tCarta[2];
	tBase oros,copas,bastos,espadas; // 4 bases con 4 palos diferentes (cartas que iran boca arriba)
	tMonton monton; //contiene las cartas boca arriba
	
	/*el juego del solitario coge parejas de cartas del mazo en el caso de que sean pares, si
	  si es impar solo coge la restante quedando asi invertido el orden de las cartas (la que est� primera
	   junto con su pareja "la segunda" y est�s al darles la vuelta la primera queda por debajo de la segunda*/
	
	bool fin;
	
	do{
		fin =1;
		int i=0;//inicializamos un contador
		while(i<2 && !mazo.vacia()){
			mano[i]=mazo.pop(); //sacamos del mazo las cartas y las guardamos en la "mano".
			i++;
		}
		monton.push(mano[0]);
		monton.push(mano[1]);
		
	/*Tras llevar dos cartas al mont�n de descartes, se accede a la carta de la cima de
	  este mont�n (la de arriba) y se intenta colocar sobre la base que le corresponda.
	  Se contin�a pasando cartas del mont�n de descartes a sus bases correspondientes
	  mientras sea posible. En este instante, se vuelven a extraer dos cartas del mazo y a
	  llevarlas al mont�n de descartes, inici�ndose de nuevo el ciclo.*/	
	
	bool colocar = 1; //se puede colocar�?
	while(!monton.vacia() && colocar){
		tCarta cartaux = monton.tope(); //la carta que se coge es la que est� m�s arriba "tope".
		
		//para ver en que monton se coloca lo realizamos mediante un menu
		
		switch(monton.tope.palo){
			case OROS: 
					if(oros.vacia() && cartaux.fig == AS){
					  	oros.push(monton.pop());//la primera figura que se mete es la del as
					  	fin=0;
					}
					else{
						if(!oros.vacia() && oros.tope().fig+1==cartaux.fig){ //colocar otra figura que no sea el as
							oros.push(monton.pop());
							fin =0;
						}
						else colocar = 0; //no se puede colocar
					}
				break;
			case COPAS:
						if(copas.vacia() && cartaux.fig==AS){
							copas.push(monton.pop());
							fin=0;
						}
						else{
							if(!copas.vacia() && copas.tope().fig+1==cartaux.fig){
								copas.push(monton.pop());
								fin=0;
							}
							else colocar =0;
						}
				break;
			case BASTOS:
						if(bastos.vacia() && cartaux.fig==AS){
							bastos.push(monton.pop());
							fin=0;
						}
						else{
							if(!bastos.vacia() && bastos.tope().fig +1 == cartaux.fig){
								bastos.push(monton.pop());
								fin=0;
							}
							else colocar = 0;	
						}
				break;
			case ESPADAS:
						if(espadas.vacia() && cartaux.fig==AS){
							espadas.push(monton.pop());
							fin=0;
						}
						else{
							if(!espadas.vacia() && espadas.tope().fig + 1 == cartaux.fig){
								espadas.push(monton.pop());
								fin =0;
							}
							else colocar = 0;
						}
				break; 
			}
		}
		
	/*Cuando se agoten las cartas que hay en el mazo, se vuelven las cartas del mont�n
	 de descartes al mazo, sin barajar (simplemente, se les da la vuelta y se devuelven al
	 mazo, con lo que el orden se invierte), y se repite de nuevo el proceso de extracci�n
	 de parejas del mazo.*/
	
	if(mazo.vacia()){
		while(!monton.vacia()){
		mazo.push(monton.pop());
		}
	}
	if(mazo.vacia() && monton.vacia()) fin = 1; //fin de la partida "condicion de la victoria"
	
  }while(!fin);//se termina el juego cuando se cumple la condicion de parada

	/*El juego termina con �xito si se consigue situar todo el mazo sobre las bases, o con
	  fracaso cuando se realicen todas las extracciones del mazo sin haber conseguido situar
	  ninguna carta sobre las bases.*/
	  
		//si devuelve 1 se termina con exito, si devuelve 0, no
		bool res;
		if(mazo.vacia() && monton.vacia()) res=1;
		else res =0; 
				
}
