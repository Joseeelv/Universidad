//CR0METRO NECESARIO DEL EJERCICIO 8

#ifndef __CRONOMETRO_H
#define __CRONOMETRO_H
#include <ctime>

using std::clock;
using std::clock_t;

const double pps = CLOCKS_PER_SEC;

class cronometro{
    public:
        cronometro(): activo(false){}
        void activar (){
            activo=true;
            t0=clock();
        }
        void parar(){
            if (activo){
                t1=clock();
                activo=false;
            }
        }
        double tiempo() const { return ((activo ? clock() : t1) - t0) / pps;}
    private:
        bool activo; //estado del cronometro
        clock_t t0,t1; //t0 tiempo inicial / t1 tiempo final
};

/*NOTAS A TENER EN CUENTA:
    La funcion clock() devuelve el tiempo en pulsos. Para poder obtener el tiempo
    en segundos es necesario dividir por los pulsos por segundos obtenidos "pps".

    Esta cantidad está definida en la macro CLOCKS_PER_SEC cuyo tipo deberá ser un 
    entero o un double.

    Para poder hacer explicita una posible conversion de CLOCKS_PER_SEC a double podemos
    hacerlo de diversas maneras, pero como estamos en C++ vamos a hacerlo de la siguiente manera:
        static_cast<double>(CLOCKS_PER_SEC).
*/
#endif