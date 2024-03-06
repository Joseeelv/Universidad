//Clase solitario
#ifndef SOLITARIO_H
#define SOLITARIO_H
#include "pilaD.h"

enum tFigura{AS,DOS,TRES,CUATRO,CINCO,SEIS,SIETE,SOTA,CABALLO,REY};
enum tPalo{OROS,COPAS,BASTOS,ESPADAS};

typedef struct{
	tFigura fig;
	tPalo palo;
}tCarta;

typedef PilaD<tCarta> mazo;
typedef PilaD<tCarta> monton;
typedef PilaD<tCarta> base;

bool solitario(tmazo mazo );

#endif //solitario.h
