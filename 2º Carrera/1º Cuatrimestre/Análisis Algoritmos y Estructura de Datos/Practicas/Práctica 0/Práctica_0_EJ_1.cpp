#include <iostream>

using namespace std; /* Se usa para cargar la biblioteca donde
se almacenan todas las funciones*/

const int N=100; /*Declaración de una constante en c++*/
int N=100; /*Declaración de una variable con valor inicial 100 en c++*/


/*Declaración de una funcion definida en linea "inline", no se pueden declarar funciones 
recursivas ya que no se puede comprobar la condicion de parada.
Se aconsejan funciones muy cortas para asi no tener que escribirlas muchas veces mejorando asi el codigo
objeto*/
inline double cuadrado(double x) {return (x*x);}

/*Se pueden declarar variables dentro de la condcion de los bucles, pero puede ser una mala
práctica por falta de legibilidad/entendimineto del programa*/

/* Usamos * para acceder a la variable apuntada por el puntero
   Usamos & para acceder al puntero de una varable "operador de referencia"
   En la declaracion de la función cuando ponemos "&" dicho parámetro se pasa por referencia
   esto equivale al "*" de C.
   El "&" de C++ != "&" de C.
*/

/*
   La sobrecarga se produce cuando el nombre de una función puede significar 
   cosas distintas, se pueden diferenciar en el nº, tipo y orden de los parámetros a la hora de la 
   declaración.
*/

/*
   Las clases nos sirven para agrupar datos de diferente tipos, y es una abstracción
   conjunta de datos y operaciones.
   Son como las estructuras de C.
   Se usa el "." para el acceso a un miembro de datos P.EJ: Nacimiento.d "Dia de nacimiento"
   Los miembros PÚBLICOS "public" son visibles desde el exterior, sin embargo, los Privados "private" NO.
   STRUCT = CLASS
   En las clases por defecto los elementos son Privados, en las estructuras por defecto son
   Públicos.

   Las clases contienen un construtor, un destructor, funciones observadoras y funciones 
        Constructor --> Crea nuevos objetos, son funciones cuyo nombre coincide con el nombre de la clase
        Destructor --> Elimina objetos de la memoria, son funciones identicas a las del constructor con la diferencia que
        en el inicio de la declaración lleva el operador 

*/