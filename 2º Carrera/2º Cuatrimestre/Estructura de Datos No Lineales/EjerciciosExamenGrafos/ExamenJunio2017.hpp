#ifndef Junio2017_HPP
#define Junio2017_HPP
/*
La capital de Zuelandia esta alcanzando niveles de toxicidad muy elevados, por ello se ha decretado el cierre a la ciudad como paso de transito hacia otras ciudades(Para ir de una ciudad a otra no se podrá pasar por C.Zuelandia pero si se podrá ir si es residente de la misma empleandola como ciudad destino u origen).

Implemente un subprograma que dada la capital y un grafo ponderado con los kilómetros de las carreteras existentes entre las ciudades del país, nos devuelva los caminos resultantes de nuestra nueva política “Sin pasar por la capital, por favor”.

Nota importante: Se ha de definir todos los tipos de dato, prototipo de las operaciones empleadas en los TADs y también los prototipos de los grafos vistos en clase que se empleen.
*/

#include <iostream>
#include "alg_grafoPMC.h"

//Definimos los tipos de datos a usar
typedef matriz<size_t> CaminosNoCapital;

CaminosNoCapital Zuelandia(GrafoP<size_t> &G, size_t Capital){
  //Tenemos que calcular los caminos que no pasen por la capital, para ello recorremos el grafo
  size_t CZuelandia = Capital;
  for(size_t i = 0; i < G.numVert(); i++){
    G[CZuelandia][i] = G[i][CZuelandia] = GrafoP<size_t>::INFINITO;
  }

  //Ahora que tenemos que la capital es inaccesible, vamos a calcular todos los caminos de costes mínimos
  //Para ello declaramos las matrices de costes y vértices para realizar Floyd
  matriz<size_t>camino(G.numVert()),CostesMinimos(G.numVert());
  CostesMinimos = Floyd(G,camino);
  return camino;
}



#endif // !Junio2017_HPP
