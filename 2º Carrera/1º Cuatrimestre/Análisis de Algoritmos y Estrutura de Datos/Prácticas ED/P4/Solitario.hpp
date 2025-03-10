/*
Jose Luis Venega Sánchez
Ejercicio 6 Práctica 4
------------------------
Especificación
*/
#ifndef SOLITARIO_HPP
#define SOLITARIO_HPP
#include "pilavec.h" //incluimos la estructura Pila

//definimos el tamaño de nuestro TAD
unsigned const N = 40;

//definimos la figura de las cartas
typedef enum Figuras {AS, DOS, TRES, CUATRO, CINCO, SEIS, SIETE, SOTA, CABALLO, REY};
typedef enum Palos {OROS, COPAS, ESPADAS, BASTOS};


//Creamos la estructura carta (formada por un palo y una figura)
typedef struct{
    Figuras figura;
    Palos palo;
}tCarta;
//Cremamos las pilas de Mazo, Base y Monton de cartas

bool Solitario(tCarta* baraja, Figuras* base);
#endif //Solitario.hpp