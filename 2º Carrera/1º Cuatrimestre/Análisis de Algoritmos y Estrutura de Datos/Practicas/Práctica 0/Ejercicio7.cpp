//7. ¿Qué problema hay con el siguiente programa?

#include <iostream>

//using namespace std;
int main(){
    //using namesapace std;
    std::cout<< "HOLA." << std::endl;
}

/*ERRORES:
    Para poder ejecutar un programa que contenga "cout,cin,endl, ..., debemos de 
    declarar la salida/entrada estándar de datos. Esto se puede hacer de dos maneras:
        1. Lo declaramos en la funcion main o como global mediante --> using namespace std,
        2. También podemos declararlo poniendo std:: delante de cout,cin, endl...
        3.           
          
          
          
*/