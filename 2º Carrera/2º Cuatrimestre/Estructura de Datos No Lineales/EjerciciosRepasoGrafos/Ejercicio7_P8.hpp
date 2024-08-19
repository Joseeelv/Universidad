// El archipiélago de Grecoland (Zuelandia) está formado únicamente por dos islas,
//  Fobos y Deimos, que tienen N1 y N2 ciudades, respectivamente, de las cuales C1 y C2
//  ciudades son costeras (obviamente C1 ≤ N1 y C2 ≤ N2 ). Se dispone de las coordenadas
//  cartesianas (x, y) de todas y cada una de las ciudades del archipiélago. El huracán
//  Isadore acaba de devastar el archipiélago, con lo que todas las carreteras y puentes
//  construidos en su día han desaparecido. En esta terrible situación se pide ayuda a la
//  ONU, que acepta reconstruir el archipiélago (es decir volver a comunicar todas las
//  ciudades del archipiélago) siempre que se haga al mínimo coste.
//  De cara a poder comparar costes de posibles reconstrucciones se asume lo
//  siguiente:
//       1. El coste de construir cualquier carretera o cualquier puente es proporcional a su
//  longitud (distancia euclídea entre las poblaciones de inicio y fin de la carretera o
//  del puente).
//       2. Cualquier puente que se construya siempre será más caro que cualquier carretera
//  que se construya.
//  De cara a poder calcular los costes de VIAJAR entre cualquier ciudad del
//  archipiélago se considerará lo siguiente:
//       1. El coste directo de viajar, es decir de utilización de una carretera o de un puente,
//  coincidirá con su longitud (distancia euclídea entre las poblaciones origen y
//  destino de la carretera o del puente).
//  En estas condiciones, implementa un subprograma que calcule el coste mínimo
//  de viajar entre dos ciudades de Grecoland, origen y destino, después de haberse
//  reconstruido el archipiélago, dados los siguientes datos:
//       1. Lista de ciudades de Fobos representadas mediante sus coordenadas cartesianas.
//       2. Lista de ciudades de Deimos representadas mediante sus coordenadas
//  cartesianas.
//       3. Lista de ciudades costeras de Fobos.
//       4. Lista de ciudades costeras de Deimos.
//       5. Ciudad origen del viaje.
//       6. Ciudad destino del viaje


#include <iostream>
#include "alg_grafoPMC.h"
#include <cmath>
#include <iterator>
#include <algorithm>

//Definimos los tipos de datos a usar
typedef std::pair<size_t,size_t> ciudad;

//Función que nos calcula la distancia euclidea entre dos ciudades
size_t DistanciaEuclidea(ciudad a, ciudad b){
  return sqrt(pow(a.first-b.first,2) + pow(a.second-b.second,2));
}

size_t Grecoland(vector<ciudad> &ciudadesFobos, vector<ciudad> &ciudadesDeimos, vector<ciudad> &costerasFobos, vector<ciudad> &costerasDeimos, size_t Origen, size_t Destino){
  //Vamos a crearnos los 2 grafos para luego crearnos el supergrafo
  GrafoP<size_t> GrafoFobos(ciudadesFobos.size()), GrafoDeimos(ciudadesDeimos.size());
  //Vamos rellenar el Grafo de Fobos con sus carreteras
  for(size_t i = 0; i < ciudadesFobos.size(); i++)
    for(size_t j = i+1; j < ciudadesFobos.size(); j++)
      GrafoFobos[i][j] = GrafoFobos[j][i] = DistanciaEuclidea(ciudadesFobos[i],ciudadesFobos[j]);

  //Rellenamos el Grafo de Deimos con sus carreteras
  for(size_t i = 0; i < ciudadesDeimos.size(); i++)
    for(size_t j = i+1; j < ciudadesDeimos.size(); j++)
      GrafoDeimos[i][j] = GrafoDeimos[j][i] = DistanciaEuclidea(ciudadesDeimos[i],ciudadesDeimos[j]);
    
  //Ahora vamos a obtener el árbol generador de coste mínimo de ambos grafos para tener todos su ciudades (vértices) conectados con el menor número de arista y menor coste.
  GrafoFobos = Kruskall(GrafoFobos);
  GrafoDeimos = Kruskall(GrafoDeimos);

  //Ahora vamos a crearnos un super grafo para poder unir con puentes las ciudades costeras con menor coste de Fobos y Deimos.
  GrafoP<size_t> GrafoGrecoland(ciudadesFobos.size() + ciudadesDeimos.size());
  //Vamos a rellenar el grafo con los costes de ambas islas 
  for(size_t i = 0; i < ciudadesFobos.size(); i++)
    for(size_t j = 0; j < ciudadesFobos.size(); j++)
      GrafoGrecoland[i][j] = GrafoFobos[i][j];

  for(size_t i = 0; i < ciudadesDeimos.size(); i++)
    for(size_t j = 0; j < ciudadesDeimos.size(); j++)
      GrafoGrecoland[i+ciudadesFobos.size()][j+ciudadesFobos.size()] = GrafoDeimos[i][j]; 

  //Tenemos el supegrafo (Grecoland) relleno, ahora vamos a obtener los puentes con menor coste
  for(size_t i = 0; i < ciudadesFobos.size(); i++)
    for(size_t j = 0; j < ciudadesDeimos.size(); j++){
      //vamos a quedarnos con las ciudades que son costeras para poder crear los puentes
      if(find(costerasFobos.begin(),costerasFobos.end(),ciudadesFobos[i]) != costerasFobos.end() &&
         find(costerasDeimos.begin(),costerasDeimos.end(),ciudadesDeimos[j]) != costerasDeimos.end()){
          //Si ambas son costeras, las unimos con un puente que también es la distancia euclidea
          size_t CostePuente = DistanciaEuclidea(ciudadesFobos[i],ciudadesFobos[j]);
          GrafoGrecoland[i][j+ciudadesFobos.size()] = GrafoGrecoland[j+ciudadesFobos.size()][i] = CostePuente;
        }
    }
  //Tenemos los puentes, vamos a quedarnos con los de menor coste con Kruskall
  GrafoGrecoland = Kruskall(GrafoGrecoland);
  //Ahora como tenemos un origen y un destino, queremos calcular el coste mínimo de viajar desde dicho origen a cualquier ciudad del archipielago, para ello vamos a declarar los vectores de vértices y coste mínimo para hacer uso de Dijkstra
  vector<size_t>vertices(GrafoGrecoland.numVert());
  vector<size_t>CosteMinimo = Dijkstra(GrafoGrecoland,Origen,vertices);
  return CosteMinimo[Destino];
}


