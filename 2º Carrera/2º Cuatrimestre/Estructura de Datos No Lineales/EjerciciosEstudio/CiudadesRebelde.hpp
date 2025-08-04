#ifndef CiudadesRebeldes_HPP
#define CiudadesRebelde_HPP
// Enunciado: Se necesita hacer un estudio de las distancias mínimas necesarias para viajar entre dos ciudades cualesquiera de un país llamado Zuelandia.

// El problema es sencillo, pero hay que tener en cuenta unos pequeños detalles:

// a) La orografía de Zuelandia es un poco especial, las carreteras son muy estrechas y, por tanto, solo permiten un sentido de la circulación.

// b) Actualmente, Zuelandia es un país en guerra. De hecho, hay una serie de ciudades del país que han sido tomadas por los rebeldes, por lo que no pueden ser usadas para viajar.

// c) Los rebeldes no solo se han apoderado de ciertas ciudades del país, sino que también han cortado ciertas carreteras (por lo que estas carreteras no pueden ser usadas).

// d) Pero el gobierno no puede permanecer impasible ante la situación y ha exigido que absolutamente todos los viajes que se hagan por el país pasen por la capital del mismo, donde se harán los controles de seguridad pertinentes.

// Dadas estas cuatro condiciones, se pide implementar un subprograma que, dados el grafo (matriz de costes) de Zuelandia en situación normal, la relación de las ciudades tomadas por los rebeldes, la relación de las carreteras cortadas por los rebeldes y la capital de Zuelandia, calcule la matriz de costes mínimos para viajar entre cualesquiera dos ciudades zuelandesas en esta situación.

/*
Partimos de que tenemos un grafo (matriz de costes) ponderado y dirigido (solo se puede ir en una dirección), también contamos con una serie de Carreteras (unión de dos Ciudades) y Ciudades tomadas por los rebeldes.

Todos los viajes que se realicen deben de pasar por la Capital.

Sabiendo esto, haré uso de los siguiente algoritmos:
  - Floyd -> para calcular todas las distancias mínimas para viajar entre dos ciudades cualesquiera.
*/

#include <iostream>
#include "Materiales/alg_grafoPMC.h"
#include "Materiales/matriz.h"
#include <vector>
#include <utility> // Para std::pair

//Definimos los tipos de datos a usar, representaremos una ciudad como un entero sin signo.
typedef std::pair<size_t,size_t> Carretera;
typedef matriz<size_t>CostesViajes;

CostesViajes ZuelandiaRebeldes(GrafoP<size_t> &G, const vector<size_t> &CiudadesRebeldes, const vector<Carretera> &CarreterasRebeldes, size_t Capital){
  //Como tenemos ciudades que no pueden ser accesibles, vamos a modificar el grafo, haciendo que el coste de estas sea infinito.
  for(size_t &ciudadrebelde : CiudadesRebeldes){
    for(size_t i = 0; i < G.numVert(); i++){
      G[i][ciudadrebelde] = GrafoP<size_t>::INFINITO;
    }
  }

  //Ahora vamos a hacer inaccesibles dichas carreteras
  for(Carretera &carreterarebelde : CarreterasRebeldes)
    G[carreterarebelde.first][carreterarebelde.second] = GrafoP<size_t>::INFINITO;

  //Ahora vamos a obligar que todos los viajes se lleven a cabo por la Capital
  vector<size_t>VerticesD(G.numVert()),VerticesDI(G.numVert()),CostesMinimosD = Dijkstra(G,Capital,VerticesD),CostesMinimosDI = DijkstraInv(G,Capital,VerticesDI);

  //Ya teniendo tanto las ciuades rebeldes como la carreteras rebeldes indicadas en el grafo, y todos los viajes cruzan la capital, vamos a poder calcular los costes mínimos de los caminos entre cada par de vértices del grafo,es decir floyd, para ello, creamos las matrices de costes mínimos y vértices.
  matriz<size_t>Vertices(G.numVert()),CosteMinimosF = Floyd(G,Vertices);

  for(size_t i = 0; i < G.numVert(); i++){
    for(size_t j = 0; j < G.numVert(); j++){
      if(i==j){
        CosteMinimosF[i][j] = 0; // El coste de ir a la misma ciudad es 0
      }
      else if(CostesMinimosDI[i] != GrafoP<size_t>::INFINITO && CostesMinimosD[j] != GrafoP<size_t>::INFINITO){
        // Si el coste de ir a la capital desde i y el coste de ir a j desde la capital es finito, entonces podemos calcular el coste mínimo
        CosteMinimosF[i][j] = CostesMinimosDI[i] + CostesMinimosD[j];
      }
  }
}
  return CosteMinimosF;
}

/*
Para llevar a cabo este ejercicio he hecho uso de los siguiente métodos de los grafos:

  size_t GrafoP<tCoste>::INFINITO;
    Post -> Devuelve el máximo valor permitido
  
  size_t numVert() const;
    Post -> Devuelve el número de vértices de grafo

  vector<tCoste>& operator[](vertice v);
    Post -> Devuelve un vector de con los costes de las aristas adyacentes al vértice v.
  
  matriz<tCoste> Floyd(const GrafoP<tCoste> &G, matriz<typename GrafoP<tCoste>::vertice> &P);
    Post -> Devuelve dos matrices, una con los costes mínimos de entre todos los vértices del grafo y otra con los vertices por donde pasan los caminos.
*/
#endif //CiudadesRebeldes.hpp

