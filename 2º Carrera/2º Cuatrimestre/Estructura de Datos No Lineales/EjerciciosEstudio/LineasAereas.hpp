
// Enunciado: El archipiélago de Tombuctú₂ está formado por un número desconocido de islas, cada una de las cuales tiene, a su vez, un número desconocido de ciudades, las cuales tienen en común que todas y cada una de ellas dispone de un aeropuerto. Sí que se conoce el número total de ciudades del archipiélago (podemos llamarlo N, por ejemplo).

// Dentro de cada una de las islas existen carreteras que permiten viajar entre todas las ciudades de la isla. No existen puentes que unan las islas y se ha decidido que la opción de comunicación más económica de implantar será el avión.

// Se dispone de las coordenadas cartesianas (x, y) de todas y cada una de las ciudades del archipiélago. Se dispone de un grafo (matriz de adyacencia) en el que se indica si existe carretera directa entre cualesquiera dos ciudades del archipiélago. El objetivo de nuestro problema es encontrar qué líneas aéreas debemos implantar para poder viajar entre todas las ciudades del archipiélago, siguiendo los siguientes criterios:
// Se implantará una y sólo una línea aérea entre cada par de islas.
// La línea aérea escogida entre cada par de islas será la más corta entre todas las posibles.
// Así pues, dados los siguientes datos:

// Lista de ciudades de Tombuctú₂ representada cada una de ellas por sus coordenadas cartesianas.
// Matriz de adyacencia de Tombuctú que indica las carreteras existentes en dicho archipiélago.
// Implementen un subprograma que calcule y devuelva las líneas aéreas necesarias para comunicar adecuadamente el archipiélago siguiendo los criterios anteriormente expuestos.

/*
Sabemos que el archipiélago está formado por un número arbitrario de islas, estas islas tienen un número de ciudades (N) con sus coordenadas (x, y) y todas estas ciudades tienen un aeropuerto.

Dentro de cada isla, cada ciudad está conectada por carreteras pero no existen puentes entre islas, por tanto, el único médio de comunicación entre islas es el avión.

Partimos de un grafo matriz de adyacencia, que indica si hay camino directo entre dos ciudades del archipielago (tenemos que ver si estas ciudades pertenecen a la misma isla o diferentes islas), ya que nuestro objetivo es devolver el número de lineas aereas.

Solo tenemos una conexión entre cada par de islas y esta conexión debe de ser la línea aerea más corta, es decir la que menor distancia euclieda tiene.

Por tanto, para realizar el subprograma haré uso de:
  - TAD APO -> Para obtener la linea aérea de menor coste, este acceso es de coste unitario y el tamaño del APO será = (n(n-1)/2).
  - Floyd -> Para obtener los costes mínimos entre todas las ciudades del archipiélago
  - TAD Partición -> Para asignar a cada isla sus ciudades correspondientes (representante = capital de esa isla).
*/

#ifndef LineasAereas_HPP_
#define LineasAereas_HPP_

#include <iostream>
#include <cmath>
#include <vector>
#include <limits>
#include "Materiales/alg_grafoMA.h"
#include "Materiales/apo.h"
#include "Materiales/particion.h"

typedef std::pair<size_t, size_t> Ciudad;

struct LineaAerea
{
  size_t Origen, Destino;
  double CosteLA;
};

typedef std::vector<LineaAerea> LineasAereas;

// Distancia euclídea entre dos ciudades
double DistanciaEuclidea(const Ciudad &A, const Ciudad &B)
{
  return sqrt(pow(A.first - B.first, 2) + pow(A.second - B.second, 2));
}

LineasAereas Tumbuctu2(const Grafo &MA, const std::vector<Ciudad> &Ciudades)
{
  const size_t N = MA.numVert();
  Particion P(N);

  // Unimos ciudades conectadas por carreteras
  for (size_t i = 0; i < N; ++i)
  {
    for (size_t j = i + 1; j < N; ++j)
    {
      if (MA[i][j])
      {
        P.unir(i, j);
      }
    }
  }

  // Agrupar ciudades por isla (representante)
  std::map<size_t, std::vector<size_t>> ciudades_por_isla;
  for (size_t i = 0; i < N; ++i)
  {
    size_t rep = P.encontrar(i);
    ciudades_por_isla[rep].push_back(i);
  }

  // Obtener representantes únicos para asignar índices a islas
  std::vector<size_t> representantes;
  for (auto it = ciudades_por_isla.begin(); it != ciudades_por_isla.end(); ++it)
  {
    representantes.push_back(it->first);
  }

  const size_t numIslas = representantes.size();

  // Generar APO con todas las posibles líneas aéreas entre islas (mínima entre pares)
  Apo<LineaAerea> APO(numIslas * (numIslas - 1) / 2);

  for (size_t i = 0; i < numIslas; ++i)
  {
    for (size_t j = i + 1; j < numIslas; ++j)
    {
      size_t rep_i = representantes[i];
      size_t rep_j = representantes[j];

      double menorDistancia = std::numeric_limits<double>::max();
      size_t origenOptimo = 0, destinoOptimo = 0;

      for (size_t u : ciudades_por_isla[rep_i])
      {
        for (size_t v : ciudades_por_isla[rep_j])
        {
          double dist = DistanciaEuclidea(Ciudades[u], Ciudades[v]);
          if (dist < menorDistancia)
          {
            menorDistancia = dist;
            origenOptimo = u;
            destinoOptimo = v;
          }
        }
      }

      APO.insertar({origenOptimo, destinoOptimo, menorDistancia});
    }
  }

  // Extraer líneas aéreas más cortas, asegurando una por cada par de islas
  std::set<std::pair<size_t, size_t>> islasConectadas;
  LineasAereas resultado;

  while (!APO.vacio() && islasConectadas.size() < numIslas * (numIslas - 1) / 2)
  {
    LineaAerea la = APO.cima();
    APO.suprimir();

    size_t isla1 = P.encontrar(la.Origen);
    size_t isla2 = P.encontrar(la.Destino);

    if (isla1 != isla2)
    {
      auto par = std::minmax(isla1, isla2);
      if (islasConectadas.count(par) == 0)
      {
        islasConectadas.insert(par);
        resultado.push_back(la);
      }
    }
  }

  return resultado;
}
/*
Para la creación de este subprograma he hecho uso de los siguientes métodos relacionados con los grafos:
*/

#endif // !LineasAereas_HPP_
