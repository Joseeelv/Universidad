/*2. Escriba una función que determine y devuelva si una secuencia de caracteres de entrada es de la forma A#B#C#D . . ., donde A, B, C, D,. . . son de la forma X&Y, que a su vez
están separados por el caráter ‘#’.*/
#include "CompruebaABCD.h"
using namespace std;

int main(){
	PilaD<char> pila1,pila2;
	string cadena;
	unsigned cont=0;
	
	cout<<"Introduce una cadena separado por el caracter '#': ";
	cin>>cadena;
	
	//convertimos la cadena a mayusculas
	mayusconverter(cadena);
	
	if(comprueba(cadena)){
		cont=cadenaPila(cadena,pila1,pila2);
		
		if(secuencia(pila1,pila2,cont)) cout<<"La cadena se corresponde con la secuencia pedida"<<endl;
		else cout<<"La cadena no se corresponde con la secuenca"<<endl;
	}
	else cout<<"ERROR, SECUENCIA NO ESPERADA"<<endl;
	
	//llamamos al destructor para asi eliminar los datos introducidos
	pila1.~PilaD();
	pila2.~PilaD();
	
	return 0;
}
