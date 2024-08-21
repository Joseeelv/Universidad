#ifndef CiudadesRebeldes_HPP
#define CiudadesRebeldes_HPP

/*
Se necesita hacer un estudio de las distancias mı́nimas necesarias para viajar entre dos ciudades cualesquiera de un paı́s llamado Zuelandia.

El problema es sencillo pero hay que tener en cuenta unos pequeños detalles:
  a) La orografı́a de Zuelandia es un poco especial, las carreteras son muy estrechas y por tanto solo permiten un sentido de la circulación.
  
  b) Actualmente Zuelandia es un paı́s en guerra. Y de hecho hay una serie de ciudades del paı́s que han sido tomadas por los rebeldes, por lo que no pueden ser usadas para viajar.

  c) Los rebeldes no sólo se han apoderado de ciertas ciudades del paı́s, sino que también han cortado ciertas carreteras, (por lo que estas carreteras no pueden ser usadas).

  d) Pero el gobierno no puede permanecer impasible ante la situación y ha exigido que absolutamente todos los viajes que se hagan por el paı́s pasen por la capital del mismo, donde se harán los controles de seguridad pertinentes.

Dadas estas cuatro condiciones, se pide implementar un subprograma que dados el grafo (matriz de costes) de Zuelandia en situación normal, la relación de las ciudades tomadas por los rebeldes, la relación de las carreteras cortadas por los rebeldes y la capital de Zuelandia, calcule la matriz de costes mı́nimos para viajar entre cualesquiera dos ciudades zuelandesas en esta situación.*/

#include <iostream>
#include "alg_grafoPMC.h"

//Definimos los tipos de datos a usar
//Nuestras ciudades serán representadas mediante size_t
typedef std::pair<size_t,size_t>Carretera;
typedef matriz<size_t> CostesViajes;

CostesViajes ZuelandiaRebelde(GrafoP<size_t> &G, vector<size_t> &CiudadesRebeldes, vector<Carretera> &CarreterasRebeldes, size_t Capital){
  //Como no podemos acceder a las ciudades rebeldes, vamosa cortarlas
  for(auto &ciudad : CiudadesRebeldes){
    for(size_t i = 0; i < G.numVert(); i++){
      G[i][ciudad] = GrafoP<size_t>::INFINITO;
    }
  }
  //Ahora vamos a cortar las carreteras que están tomadas por los rebeldes
  for(const auto &carretera : CarreterasRebeldes){
    G[carretera.first][carretera.second] = G[carretera.second][carretera.first] = GrafoP<size_t>::INFINITO;
  }
  
  //Ahora nos quedamos solamente con los caminos que vayan a la capital
  for(size_t i = 0; i < G.numVert(); i++)
    if(i != Capital)
      for(size_t j = 0; j < G.numVert(); j++)
        if(j != Capital) //si los dos son distinto de la capital, no hay camino
          G[i][j] = G[j][i] = GrafoP<size_t>::INFINITO;
  
  //Ahora vamos a calcular los caminos y costes mínimos de viajar entre cada par de ciudades, para ello vamos a declarar las matrices de costes y vértices para hacer uso de Floyd
  matriz<size_t>CostesMinimos(G.numVert()),Vertices(G.numVert());
  return CostesMinimos = Floyd(G,Vertices); 
}



#endif // !CiudadesRebeldes_HPP
