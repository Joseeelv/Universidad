//3. Que problema hay en este algoritmo?

#include <iostream>
const char* SOS(){ return "... ___ ...";} //UNA SOLUCION 
inline const char* SOS(){ return "... ___ ...";} // OTRA DOLUCION

int main(){
    using namespace std;
    cout << SOS() << endl;
}

//const char* SOS(){ return "... ___ ...";} DONDE ESTABA EL ERROR

/*  De partida nos da error en la linea 5 debido a "SOS()" que supuestamente es una cadena 
    de caracteres constante es "leida" despues de acceder al main y por tanto no se imprime.

    Para solucionarlo debemos de poner dicha declaracion de la constante antes de la funcion
    main, ya que la "lee" antes de imprimirla por pantalla.

    Otra solución seria realizar una funcion inline antes del main que haga que se ejecute antes del main
    

*/