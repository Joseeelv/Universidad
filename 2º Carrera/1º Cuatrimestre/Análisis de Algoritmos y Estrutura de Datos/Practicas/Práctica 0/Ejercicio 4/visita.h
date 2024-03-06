//4. El siguiente programa se compone de una cabecera y dos módulos:
#ifndef __VISITA_H
#define __VISITA_H

//CABECERA
#include <iostream>

int Visitas ;
void visita(const char* arg);

#endif
/*
    Vemos que en este .h no define el .h, ni lo abre y ni lo cierra, es decir faltarian las lineas
    2, 3 y 11. 

    En el módulo principal "char argv" no varía por tanto es una constante.
    Tambien vemos que faltan las llaves en el bucle condicional while
*/