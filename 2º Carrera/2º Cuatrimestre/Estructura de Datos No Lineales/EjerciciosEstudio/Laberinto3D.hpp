#ifndef Laberinto3D_HPP
#define Laberinto3D_HPP

/*
Partimos de que tenemos una matriz de dimensión N*N*N, donde tenemos la casilla de entra y de salida. Solo nos podemos mover en las siguientes direcciones(Arriba, Abajo, Derecha, Izquierda, Adelante y atrás). Además, tenemos un conjunto de paredes que nos impide movernos entre dos casillas.

Nos piden calcular el camino más corto y el coste ir desde la casilla de entrada hasta la casilla de salida, por tanto, haré uso de Dijkstra para obtener así el coste mínimo de ir desde ese origen al destino.
*/

#include <iostream>
#include "Materiales/grafoPMC.h"

//Definimos los tipos de datos a usar
typedef std::pair<std::vector<size_t>,size_t>ResultadoLaberinto;

struct Casilla{
  size_t x, y, z;
};

size_t CasillaToVertice(size_t x, size_t y, size_t z, size_t N){
  return (x*(N*N) + y*N + z);
}

ResultadoLaberinto Laberinto3D(size_t N, vector<Casilla>&Paredes, Casilla CEntrada, Casilla CSalida){
  //Primero de todo tenemos que contruir el grafo,
  GrafoP<size_t>GLaberinto(N*N*N);
  size_t tama = GLaberinto.numVert();
  //Ahora relleamos el grafo con los posibles movimientos
  for(size_t i = 0; i < tama; i++){
    for(size_t j = 0; j < tama; j++){
      for(size_t k = 0; k < tama; k++){
        //Nos quedamos con la casilla actual 
        size_t actual = CasillaToVertice(i,j,k,N);
        if(i+1 < N){ //Hacia derecha
          GLaberinto[actual][CasillaToVertice(i+1,j,k,N)] = GLaberinto[CasillaToVertice(i+1,j,k,N)][actual] = 1;
        }
        if(i-1 >= 0){ //Hacia derecha
        GLaberinto[actual][CasillaToVertice(i-1,j,k,N)] = GLaberinto[CasillaToVertice(i-1,j,k,N)][actual] = 1;
        }
        if(j+1 < N){ //Hacia abajo
          GLaberinto[actual][CasillaToVertice(i,j+1,k,N)] = GLaberinto[CasillaToVertice(i,j+1,k,N)][actual] == 1;
        }
        if(j-1 >= 0){ //Hacia arriba
          GLaberinto[actual][CasillaToVertice(i,j-1,k,N)] = GLaberinto[CasillaToVertice(i,j-1,k,N)][actual] = 1;
        }
        if(k+1 < N){ //Hacia atrás
          GLaberinto[actual][CasillaToVertice(i,j,k+1,N)] = GLaberinto[CasillaToVertice(i,j,k+1,N)][actual] = 1;
        }
        if(k-1 >= 0){ //Hacia delante
          GLaberinto[actual][CasillaToVertice(i,j,k-1,N)] = GLaberinto[CasillaToVertice(i,j,k-1,N)][actual] = 1;
        }
      }
    }
  }

  //Ya que tenemos relleno el grafo con todos los posibles movimientos, podemos poner las paredes
  size_t inf = GrafoP<size_t>::INFINITO;
  for(Casilla& p : Paredes){
    for(size_t i = 0; i < tama; i++){
      GLaberinto[i][CasillaToVertice(p.x,p.y,p.z,N)] = GLaberinto[CasillaToVertice(p.x,p.y,p.z,N)][i] = inf;
    }
  }

  //Finalmente podemos hacer uso de Dijkstra para calcular el camino y coste mínimo de ir desde a entrada hacia la salida
  size_t Entrada = CasillaToVertice(CEntrada.x,CEntrada.y,CEntrada.z,N);
  size_t Salida = CasillaToVertice(CSalida.x,CSalida.y,CSalida.z,N);

  vector<size_t>Vertices(tama),CostesMinimos(tama);
  CostesMinimos = Dijkstra(GLaberinto,Entrada,Vertices);

  //Ahora recuperamos el camino
  vector<size_t>Camino;
  size_t actual = Salida;
  while(actual != Entrada){
    Camino.push_back(actual);
    actual = Vertices[actual];
  }
  Camino.push_back(Entrada);
  std::reverse(Camino.begin(), Camino.end());

  //Obtenemos el coste del Camino
  size_t coste = CostesMinimos[Salida];
  return{Camino, coste}; //Devolvemos el camino con su longitud (coste);
}

#endif // !Laberinto3D_HPP
