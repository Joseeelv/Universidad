#ifndef Grecoland_HPP_
#define Grecoland_HPP_

// **Enunciado:** El archipiélago de Grecoland (Zuelandia) está formado únicamente por dos islas, Fobos y Deimos, que tienen \(N_1\) y \(N_2\) ciudades, respectivamente, de las cuales \(C_1\) y \(C_2\) ciudades son costeras (obviamente \(C_1 \leq N_1\) y \(C_2 \leq N_2\)). Se dispone de las coordenadas cartesianas \((x, y)\) de todas y cada una de las ciudades del archipiélago.  

// El huracán Isadore acaba de devastar el archipiélago, con lo que todas las carreteras y puentes construidos en su día han desaparecido. En esta terrible situación, se pide ayuda a la ONU, que acepta reconstruir el archipiélago (es decir, volver a comunicar todas las ciudades del archipiélago) siempre que se haga al mínimo coste.  

// De cara a poder comparar costes de posibles reconstrucciones, se asume lo siguiente:  

// 1. El coste de construir cualquier carretera o cualquier puente es proporcional a su longitud (distancia euclídea entre las poblaciones de inicio y fin de la carretera o del puente).  
// 2. Cualquier puente que se construya siempre será más caro que cualquier carretera que se construya.  

// Para calcular los costes de **viajar** entre cualquier ciudad del archipiélago, se considerará lo siguiente:  

// 1. El coste directo de viajar, es decir, la utilización de una carretera o de un puente, coincidirá con su longitud (distancia euclídea entre las poblaciones origen y destino de la carretera o del puente).  

// En estas condiciones, implementa un subprograma que calcule el coste mínimo de viajar entre dos ciudades de Grecoland, origen y destino, después de haberse reconstruido el archipiélago, dados los siguientes datos:  

// 1. Lista de ciudades de Fobos representadas mediante sus coordenadas cartesianas.  
// 2. Lista de ciudades de Deimos representadas mediante sus coordenadas cartesianas.  
// 3. Lista de ciudades costeras de Fobos.  
// 4. Lista de ciudades costeras de Deimos.  
// 5. Ciudad origen del viaje.  
// 6. Ciudad destino del viaje.  

// **Nota:** Este ejercicio pertenece a la **Práctica 8, Ejercicio 7** de **Grafos.AA**.


/*
El enunciado nos dice que Grecoland está formado por dos islas Fobos y Deimos, cada una con un tamaño determinado. Estas islas tienen ciudades costeras y no costeras (siendo el número de costeras menor que el de las no costeras). Además, estas dos islas están destruidas por lo que tendremos que reconstruirlas.

Tenemos las coordenadas cartesianas (x, y) de todas las ciudades.

Las Islas se conectan a través de puentes, este coste es proporcional a la distancia euclídea entre las ciudades que unen las islas. Además, los puentes son más caros que las carreteras.

Tenemos que realizar un programa donde dadas las ciudades de Origen y Destino, las Islas con sus ciudades costeras y no costeras tengamos que calcular el coste mínimo de viajar entre dos ciudades cualesquiera del archipiélago.

Por tanto, para poder reconstruir la carreteras de las islas haré uso de un algoritmo que me devuelva un árbol generador de coste mínimo, en este caso Kruskal.
También haré uso de Dijkstra para calcular el coste mínimo de ir desde esa ciudad Origen a cualquier Destino.
*/

#include <iostream>
#include <cmath>
#include "materiales/alg_grafoPMC.h"

typedef std::pair<size_t, size_t> Ciudad;
typedef double tCoste;

// Distancia euclídea entre dos ciudades
tCoste DistanciaEuclidea(Ciudad Origen, Ciudad Destino) {
    return sqrt(pow((double)Origen.first - Destino.first, 2) + pow((double)Origen.second - Destino.second, 2));
}

tCoste PuentesGrecoland(
    const std::vector<size_t> &CiudadesCosterasFobos,
    const std::vector<size_t> &CiudadesCosterasDeimos,
    const std::vector<Ciudad> &CiudadesFobos,
    const std::vector<Ciudad> &CiudadesDeimos,
    size_t Origen, size_t Destino)
{
    using namespace std;
    size_t N1 = CiudadesFobos.size(), N2 = CiudadesDeimos.size();
    GrafoP<tCoste> Fobos(N1), Deimos(N2);

    // Carreteras internas
    for (size_t i = 0; i < N1; i++)
        for (size_t j = i + 1; j < N1; j++)
            Fobos[i][j] = Fobos[j][i] = DistanciaEuclidea(CiudadesFobos[i], CiudadesFobos[j]);

    for (size_t i = 0; i < N2; i++)
        for (size_t j = i + 1; j < N2; j++)
            Deimos[i][j] = Deimos[j][i] = DistanciaEuclidea(CiudadesDeimos[i], CiudadesDeimos[j]);

    Fobos = Kruskall(Fobos);
    Deimos = Kruskall(Deimos);

    // Unimos ambas islas en Grecoland
    GrafoP<tCoste> Grecoland(N1 + N2);

    for (size_t i = 0; i < N1; i++)
        for (size_t j = 0; j < N1; j++)
            Grecoland[i][j] = Fobos[i][j];

    for (size_t i = 0; i < N2; i++)
        for (size_t j = 0; j < N2; j++)
            Grecoland[i + N1][j + N1] = Deimos[i][j];

    // Añadimos los puentes entre costeras
    const tCoste factorPuente = 4.0;
    for (size_t i : CiudadesCosterasFobos)
        for (size_t j : CiudadesCosterasDeimos) {
            tCoste puente = factorPuente * DistanciaEuclidea(CiudadesFobos[i], CiudadesDeimos[j]);
            Grecoland[i][j + N1] = Grecoland[j + N1][i] = puente;
        }

    // Reconstruimos puentes mínimos
    Grecoland = Kruskall(Grecoland);

    vector<tCoste> costes;
    vector<size_t> vertices;
    costes = Dijkstra(Grecoland, Origen, vertices);
    return costes[Destino];
} 


/*
Para llevar a cabo este ejercicio he hecho uso de los siguientes métodos de los grafos

  GrafoP<tCoste> GrafoP(size_t n);
    Post -> Crea un grafo ponderado de tamaño n

  size_t numVert() const;
    Post -> Devuelve el número de vértices de un grafo
  
  vector<tCoste>& operator[](vertice v);
    Post -> Devuelve un vector con los costes mínimos de las aristas adyacentes al vértice v

  GrafoP<tCoste> Kruskall(const GrafoP<tCoste> &G);
    Post -> Devuelve un árbol generador de coste mínimo.

  vector<tCoste> Dijskra(const GrafoP<tCoste> &G, typename GrafoP<tCoste>::vertice Origen,  vector<typename GrafoP<tcoste>::vertice> &P);
    Post -> Devuelve dos vectores, uno con los costes mínimos de ir desde el origen a cualquier destino y otro con los vértices por donde discurre el camino.
*/



#endif // !