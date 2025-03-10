#ifndef LineasAereas_HPP_
#define LineasAereas_HPP_

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

#include <iostream>
#include <cmath>
#include <vector>
#include "Materiales/alg_grafoMA.h"
#include "Materiales/alg_grafoPMC.h"
#include "Materiales/apo.h"
//Primero de todo voy a definir los tipos de datos a usar así como las funciones auxiliares

typedef std::pair<size_t, size_t> Ciudad; // Ciudad con coordenadas x, y

struct Isla {
  std::vector<Ciudad> CiudadesIsla; // Conjunto de ciudades de la isla
  matriz<size_t> CostesIslas; // Costes mínimos de viajar entre cualquier ciudad de la isla
};

typedef std::vector<Isla> Archipielago; // El archipiélago Tumbuctú es un conjunto de Islas

struct LineaAerea {
  size_t Origen, Destino;
  size_t CosteLA;
};

typedef std::vector<LineaAerea> LineasAereas; // Conjunto de líneas aéreas a devolver

// Función que calcula la distancia entre dos ciudades de distinta isla
size_t DistanciaEuclidea(Ciudad A, Ciudad B) {
  return sqrt(pow(A.first - B.first, 2) + pow(A.second - B.second, 2));
}

// Función auxiliar que me devuelve una matriz de coste mínimo de una Isla
matriz<size_t> CalculaCostesIsla(const std::vector<Ciudad>& ciudades) {
  // Creamos el grafo que será la isla
  GrafoP<size_t> GIsla(ciudades.size());
  // Rellenamos el grafo con las ciudades de la isla
  for (size_t i = 0; i < ciudades.size(); i++) {
    for (size_t j = i + 1; j < ciudades.size(); j++) {
      GIsla[i][j] = GIsla[j][i] = DistanciaEuclidea(ciudades[i], ciudades[j]);
    }
  }

  // Ahora que tenemos el grafo relleno, haré uso de Floyd para quedarme con los costes mínimos de viajar por la isla
  matriz<size_t> VerticesF(GIsla.numVert()), CostesMinimos(GIsla.numVert());
  return CostesMinimos = Floyd(GIsla, VerticesF);
}

// Función que me calcula las líneas aéreas del archipiélago
LineasAereas Tumbuctu2(const Grafo& MA, const std::vector<Ciudad>& Ciudades) {
  // Primero de todo, voy a crear las Islas, como dije antes, cada representante será la "Capital de la Isla" y todas aquellas ciudades que estén ligadas a ese representante, irá a esa Isla.
  Particion P(MA.numVert());
  for (size_t i = 0; i < MA.numVert(); i++) {
    for (size_t j = i + 1; j < MA.numVert(); j++) {
      if (MA[i][j] == true) { // Hay camino directo entre el par de vértices
        if (P.encontrar(i) != P.encontrar(j)) {
          P.unir(P.encontrar(i), P.encontrar(j));
        }
      }
    }
  }

  // Ya tenemos creados los subconjuntos de las ciudades con su representante, ahora vamos a insertarlos en las Islas correspondientes
  Isla islaux;
  Archipielago archipielagoAux;
  size_t representante_actual = P.encontrar(0);
  for (size_t i = 0; i < Ciudades.size(); i++) {
    if (P.encontrar(representante_actual) == P.encontrar(i)) {
      islaux.CiudadesIsla.push_back(Ciudades[i]);
    } else { // Cambiamos de representante y de isla
      // Primero guardamos los cambios en la isla anterior
      islaux.CostesIslas = CalculaCostesIsla(islaux.CiudadesIsla);
      // Guardamos la isla en el archipiélago
      archipielagoAux.push_back(islaux);
      // Asignamos la nueva isla limpiando las ciudades de islaux anterior ya previamente guardada
      islaux.CiudadesIsla.clear();
      islaux.CiudadesIsla.push_back(Ciudades[i]); // insertamos la nuevas islas
      representante_actual = P.encontrar(i);
    }
  }
  // Guardamos la última isla
  islaux.CostesIslas = CalculaCostesIsla(islaux.CiudadesIsla);
  archipielagoAux.push_back(islaux);

  // Ya tenemos creadas las islas, ahora vamos a crear el APO para obtener las líneas aéreas de menor coste
  size_t n = archipielagoAux.size();
  Apo<LineaAerea> A(n * (n - 1) / 2);
  for (size_t i = 0; i < n; i++) {
    for (size_t j = 0; j < n; j++) {
      // Solo una línea aérea por cada par de islas, por tanto, tenemos que comprobar que los representantes sean diferentes
      if (P.encontrar(i) != P.encontrar(j)) // Distintas islas, se inserta en el APO
        A.insertar({Ciudades[i], Ciudades[j], DistanciaEuclidea(Ciudades[i], Ciudades[j])});
    }
  }

  // Ahora, construido el APO, vamos sacando desde la raíz (el de menor coste) por cada par de islas.
  matriz<bool> IslasConectadas(n, false); // Creamos una matriz para comprobar si están o no conectadas ya las islas
  LineasAereas vector_LA(n * (n - 1) / 2); // tiene que tener el tamaño del APO
  size_t indice = 0;
  while (!A.vacio() && indice < (n * (n - 1) / 2)) {
    LineaAerea MenosCostosa = A.cima();
    // Ahora comprobamos que el origen y destino de la línea aérea sean de diferente isla
    if (P.encontrar(MenosCostosa.Origen) != P.encontrar(MenosCostosa.Destino) && !IslasConectadas[MenosCostosa.Origen][MenosCostosa.Destino]) {
      IslasConectadas[MenosCostosa.Origen][MenosCostosa.Destino] = true;
      IslasConectadas[MenosCostosa.Destino][MenosCostosa.Origen] = true;
      vector_LA[indice] = MenosCostosa;
      indice++;
    }
  }
  return vector_LA;
}

/*
Para la creación de este subprograma he hecho uso de los siguientes métodos relacionados con los grafos:
*/

#endif // !LineasAereas_HPP_
