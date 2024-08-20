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
struct Casilla{
    size_t x_, y_, z_;
};

typedef std::pair<vector<size_t>,size_t> Camino_Coste;

//Función que nos convierte una casilla en un vértice del grafo
size_t CasillatoVertice(size_t i, size_t j, size_t k, size_t N){
    return (i* (N*N) + j*N + k);
}

Camino_Coste Laberinto3D(size_t N, vector<Casilla> &paredes, Casilla Origen, Casilla Destino){
  //Creamos el grafo para poder calcular el coste
  GrafoP<size_t>Laberinto(N*N*N);
  //Vamos a rellenar el grafo con los movimientos que podemos realizar
  for(size_t i = 0; i < N; i++)
    for(size_t j = 0; j < N; j++)
      for(size_t k = 0; k < N; k++){
        //Primero almacenamos la casilla actual
        size_t actual = CasillatoVertice(i,j,k,N);
        //Ahora vamos a rellenar con los posible movimientos
        if(i+1 < N)
          Laberinto[actual][CasillatoVertice(i+1,j,k,N)] = 1;
        if(i-1 >= 0)
          Laberinto[actual][CasillatoVertice(i-1,j,k,N)] = 1;
        if(j+1 < N)
          Laberinto[actual][CasillatoVertice(i,j+1,k,N)] = 1;
        if(j-1 >= 0)
          Laberinto[actual][CasillatoVertice(i,j-1,k,N)] = 1;
        if(k+1 < N)
          Laberinto[actual][CasillatoVertice(i,j,k+1,N)] = 1;
        if(k-1 >= 0)
          Laberinto[actual][CasillatoVertice(i,j,k-1,N)] = 1;
      }
  //ahora vamos a colocar las paredes, la ponemos a infinito porque no se puede acceder
  for(auto& p : paredes){
    for(size_t i = 0; i < Laberinto.numVert(); i++){
      Laberinto[i][CasillatoVertice(p.x_,p.y_,p.z_,N)] = Laberinto[CasillatoVertice(p.x_,p.y_,p.z_,N)][i] = GrafoP<size_t>::INFINITO;
    }
  }
  //Ahora teniendo nuestro grafo con las casillas que podemos acceder y las paredes del mismo, vamos a calcular el coste mínimo de ir desde la casilla origen, a la casilla destino.
  size_t casilla_origen = CasillatoVertice(Origen.x_,Origen.y_,Origen.z_,N);
  size_t casilla_destino = CasillatoVertice(Destino.x_,Destino.y_,Destino.z_,N);
  //Declaramos los vectores de vértices y costesminimos para poder hacer uso de Dijkstra
  vector<size_t>Vertices(Laberinto.numVert()),CostesMinimos(Laberinto.numVert());
  CostesMinimos = Dijkstra(Laberinto,casilla_origen,Vertices);

  //Vamos a obtener el camino y el coste minimo de ir desde el origen al destino
  return Camino_Coste{Vertices,CostesMinimos[casilla_destino]};
}
#endif // !Laberinto3D_HPP

