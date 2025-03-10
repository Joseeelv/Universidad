#ifndef Laberinto3D_HPP
#define Laberinto3D_HPP
/*
    Se dispone de un laberinto de NxNxN casillas del que se conocen las casillas de entrada y salida del mismo.
    Si te encuentras en una casilla sólo puedes moverte en las siguientes seis direcciones (arriba, abajo, derecha, izquierda, adelante, atrás).
    Por otra parte, entre algunas de las casillas hay una pared que impide moverse entre las dos casillas que separa dicha pared (en caso contrario no sería un verdadero laberinto).

    Implementa un subprograma que dados:

    - N (dimensión del laberinto),
    - la lista de paredes del laberinto,
    - la casilla de entrada, y
    - la casilla de salida,

    calcule el camino más corto para ir de la entrada a la salida y su longitud.
*/

#include <iostream>
#include <cmath>
#include <algorithm>
#include "alg_grafoPMC.h"
//Definimos los tipos de datos a usar

typedef std::pair<vector<size_t>,size_t> Camino_Coste;
typedef struct Casilla{
  size_t x, y, z;
};

Camino_Coste Laberinto3D(size_t N, vector<Casilla> &paredes, Casilla Entrada, Casilla Salida){
  //Primero de todo creamos el grafo no dirigido.
  GrafoP<size_t> GLaberinto(N*N*N);
  //Rellenamos el laberinto con los movimientos
  for(size_t i = 0; i < N; i++){
    for(size_t j = 0; j < N; j++){
      for(size_t k = 0; k < N; k++){
        //Nos quedamos con la casilla actual
        size_t casilla_actual = CasillaToVertice(i,j,k,N);
        if(i+1 < N){ //Derecha
          GLaberinto[casilla_actual][CasillaToVertice(i+1,j,k,N)] = GLaberinto[CasillaToVertice(i+1,j,k,N)][casilla_actual] = 1;
        }
        if(i-1 >= 0){ //Izquierda
          GLaberinto[casilla_actual][CasillaToVertice(i-1,j,k,N)] = GLaberinto[CasillaToVertice(i-1,j,k,N)][casilla_actual] = 1;
        }
        if(j+1 < N){ //Abajo
          GLaberinto[casilla_actual][CasillaToVertice(i,j+1,k,N)] = GLaberinto[CasillaToVertice(i,j+1,k,N)][casilla_actual] = 1;
        }
        if(j-1 >= 0){//Arriba
          GLaberinto[casilla_actual][CasillaToVertice(i,j-1,k,N)] = GLaberinto[CasillaToVertice(i,j-1,k,N)][casilla_actual] = 1;
        }
        if(k+1 < N){ //Atrás
          GLaberinto[casilla_actual][CasillaToVertice(i,j,k+1,N)] = GLaberinto[CasillaToVertice(i,j,k+1,N)][casilla_actual] = 1; 
        }
        if(k-1 >= 0){ //Delante
          GLaberinto[casilla_actual][CasillaToVertice(i,j,k-1,N)] = GLaberinto[CasillaToVertice(i,j,k-1,N)][casilla_actual] = 1;
        }
      }
    }
  }
  //Ahora rellenamos el grafo con las piedras
  for(Casilla &pared : paredes){
    for(size_t i = 0; i < GLaberinto.numVert(); i++){
      GLaberinto[i][CasillaToVertice(pared.x,pared.y,pared.z,N)] = GLaberinto[CasillaToVertice(pared.x,pared.y,pared.z,N)][i] = GrafoP<size_t>::INFINITO;
    }
  }

  //Ya tenemos el grafo con las casillas accesibles y no accesibles, por lo que vamos a proceder a obtener el camino y coste mínimo de ir desde la entrada hacia la salida.
  size_t CEntrada = CasillaToVertice(Entrada.x,Entrada.y,Entrada.z, N);
  size_t CSalida = CasillaToVertice(Salida.x, Salida.y, Salida.z, N);
  
  vector<size_t>Vertices(GLaberinto.numVert()),CostesMinimos(GLaberinto.numVert());
  CostesMinimos = Dijkstra(GLaberinto,CEntrada,Vertices);
  size_t Coste = CostesMinimos[CSalida]; //Coste del camino

  //Ahora vamos a obtener el camino 
  vector<size_t>Camino; //Camino Salida-Entrada
  size_t actual = CSalida;
  while(actual != CEntrada){
    Camino.push_back(actual);
    actual = Vertices[actual];
  }
  Camino.push_back(CEntrada);
  std::reverse(Camino.begin(), Camino.end()); //Camino Entrada-Salida.

  return {Camino, Coste}; //Devolvemos el camino y su coste mínimo.
}

//Función que dada una casilla nos devuelve un vértice
size_t CasillaToVertice(size_t i, size_t j, size_t k, size_t N){
  return (i*(N*N) + j*N + k);
}
#endif // !Laberinto3D_HPP

