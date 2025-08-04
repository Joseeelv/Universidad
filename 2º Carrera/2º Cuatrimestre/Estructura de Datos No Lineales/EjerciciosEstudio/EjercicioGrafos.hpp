#include "../alg_grafoPMC.h" // Update the path as needed to the correct location of alg_grafoPMC.h

// CIUDADES REBELDES
/*
  Tenemos un grafo ponderdo y dirigido (ya que solo podemos acceder hacia un sentido), además tenemos un conjunto de ciudades tomadas por los rebeldes y un conjunto de carreteras cortadas por los rebeldes (es decir, el coste de ir a esas ciudades es infinito y el coste de las carreteras cortadas es infinito). Finalmente, tenemos una ciudad capital que debe de ser el nodo origen y destino de todos los caminos.

  Para poder resolver este problema, haremos uso de los algoritmos Dikjstra y DijkstraInv, que nos permite calcular los caminos de coste mínimo de pasar solamente por la Capital y luego crearemos una matriz de costes mínimos que es lo que devolveremos.
*/

#include <iostream>
#include "Materiales/alg_grafoPMC.h"
#include "Materiales/matriz.h"
#include <vector>
#include <utility> // Para std::pair

//Definimos los tipos de datos a usar, representaremos una ciudad como un entero sin signo.
typedef std::pair<size_t,size_t> Carretera;
typedef matriz<size_t>CostesViajes;

CostesViajes CiudadesRebeldes(GrafoP<size_t> &G, const vector<size_t> &CiudadesRebeldes, const vector<Carretera> &CarreterasRebeldes, size_t Capital){
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
  matriz<size_t>CosteMinimos(G.numVert(), G.numVert(), GrafoP<size_t>::INFINITO);

  for(size_t i = 0; i < G.numVert(); i++){
    for(size_t j = 0; j < G.numVert(); j++){
      if(i==j){
        CosteMinimos[i][j] = 0; // El coste de ir a la misma ciudad es 0
      }
      else if(CostesMinimosDI[i] != GrafoP<size_t>::INFINITO && CostesMinimosD[j] != GrafoP<size_t>::INFINITO){
        // Si el coste de ir a la capital desde i y el coste de ir a j desde la capital es finito, entonces podemos calcular el coste mínimo
        CosteMinimos[i][j] = CostesMinimosDI[i] + CostesMinimosD[j];
      }
  }
}
  return CosteMinimos;
}

// ZUELANDIA TÓXICA
/*
  Partimos de que tenemos la capital de Zuelandia y un grafo ponderado.
  Nos pide devolver todos los caminos de que no pasen por la capital, es decir, que no usen la capital como nodo intermedio.
  Para ello, heremos uso del algoritmo Floyd, que nos permite calcular los caminos de coste mínimo de cada par de vértices del grafo.
*/

matriz<typename GrafoP<size_t>::vertice> ZuelandiaToxica(const GrafoP<size_t> &G, size_t CZuelandia){
  // Primero vamos a crear una copia del grafo para no modificar el original
  GrafoP<size_t> GrafoToxico(G);
  size_t nVertices = G.numVert();

  // Ejecutamos Floyd en el grafo ya modificado
  matriz<typename GrafoP<size_t>::vertice> caminos(nVertices);
  matriz<size_t> CostesMinimos = Floyd(GrafoToxico, caminos);

  // Para cada par de vértices, comprobamos si el camino pasa por la capital como nodo intermedio
  for (size_t i = 0; i < nVertices; ++i) {
    for (size_t j = 0; j < nVertices; ++j) {
      if (i != CZuelandia && j != CZuelandia) {
        // Comprobamos si el camino de i a j pasa por la capital
        size_t k = caminos[i][j];
        bool pasaPorCapital = false;
        while (k != GrafoP<size_t>::INFINITO && k != i) {
          if (k == CZuelandia) {
            pasaPorCapital = true;
          }
          k = caminos[i][k];
        }
        if (pasaPorCapital) {
          CostesMinimos[i][j] = GrafoP<size_t>::INFINITO;
          caminos[i][j] = GrafoP<size_t>::INFINITO;
        }
      }
    }
  }
  return caminos;
}

//LABERINTO 3D

struct Casilla{
  size_t x_, y_, z_;
};


size_t CasillaToNodo(const Casilla& c, size_t N) {
  // Convertir coordenadas 3D a un índice 1D
  return c.x_ * N * N + c.y_ * N + c.z_;
}

size_t Laberinto3D(size_t N, const std::vector<Casilla>&Piedras, Casilla Entrada, Casilla Salida){
  GrafoP<size_t> Laberinto(N*N*N); // Grafo 3D con N^3 vértices
  size_t nvertices = Laberinto.numVert();
  //Ponemos todos los movimientos posibles en el laberinto
  Casilla inicial = {0,0,0};
  for(size_t i = 0; i < N; i++){
    for(size_t j = 0; j < N; j++){
      for(size_t k = 0; k < N; k++){
        //Posición actual
        size_t actual = CasillaToNodo({i,j,k},N);
        //Ahora vamos a rellenar con los posible movimientos
        if(j+1 < N){ //Arriba
          Laberinto[actual][CasillaToNodo({i,j+1,k},N)] = Laberinto[CasillaToNodo({i,j+1,k},N)][actual] = 1;
        }
        if(j > 0){ //Abajo
          Laberinto[actual][CasillaToNodo({i,j-1,k},N)] = Laberinto[CasillaToNodo({i,j-1,k},N)][actual] = 1;
        }
        if(i+1 < N){ //Derecha
          Laberinto[actual][CasillaToNodo({i+1,j,k},N)] = Laberinto[CasillaToNodo({i+1,j,k},N)][actual] = 1;
        }
        if(i > 0){ //Izquierda
          Laberinto[actual][CasillaToNodo({i-1,j,k},N)] = Laberinto[CasillaToNodo({i-1,j,k},N)][actual] = 1;
        }
        if(k+1 < N){ //Adelante
          Laberinto[actual][CasillaToNodo({i,j,k+1},N)] = Laberinto[CasillaToNodo({i,j,k+1},N)][actual] = 1;
        }
        if(k > 0){ //Atrás
          Laberinto[actual][CasillaToNodo({i,j,k-1},N)] = Laberinto[CasillaToNodo({i,j,k-1},N)][actual] = 1;
        }
      }
    } 
  }
  //Ahora ponemos todas las piedras en el laberinto, es decir, ponemos a infinito los caminos que pasan por las piedras
  for(const Casilla& piedra: Piedras){
    size_t nodoPiedra = CasillaToNodo(piedra,N);
    for(size_t i = 0; i < nvertices; i++){
      Laberinto[i][nodoPiedra] = Laberinto[nodoPiedra][i] = GrafoP<size_t>::INFINITO; // Hacemos inaccesible la piedra
    }
  }

  //Ahora vamos a calcular el camino más corto desde la entrada hasta la salida
  size_t nodoEntrada = CasillaToNodo(Entrada, N);
  size_t nodoSalida = CasillaToNodo(Salida, N);
  std::vector<size_t> VerticesD(nvertices), CostesMinimos = Dijkstra(Laberinto, nodoEntrada, VerticesD);
  return CostesMinimos[nodoSalida];
}

#define N 8 // Definimos el tamaño del laberinto, en este caso 8x8x8
typedef std::pair<size_t,size_t> Casilla;

size_t CasillaToNodo(const Casilla&c, size_t N){
  return c.first*N+c.second;
}

size_t Caballo(size_t N, const Casilla& Entrada, const Casilla& Salida){
  //Creamos el grafo
  GrafoP<size_t>L(N*N);
  size_t nvertices = L.numVert();
  //Ponemos todos los movimientos posibles del caballo
  for(size_t i = 0; i < N; i++){
    for(size_t j = 0; j < N; j++){
      size_t actual = CasillaToNodo({i,j},N);
      if(i+1 < M && j-2 >= 0){
        size_t nuevo = CasillaToNodo({i+1,j-2},N);
        L[actual][nuevo] = L[nuevo][actual] = 1;
      }
      if(if(i+2 < M && j-1 >= 0)){
        size_t nuevo = CasillaToNodo({i+2,j-1},N);
        L[actual][nuevo] = L[nuevo][actual] = 1;
      }
      if(i+2 < M && j+1 < N){
        size_t nuevo = CasillaToNodo({i+2,j+1},N);
        L[actual][nuevo] = L[nuevo][actual] = 1;
      }
      if(i+1 < M && j+2 < N){
        size_t nuevo = CasillaToNodo({i+1,j+2},N);
        L[actual][nuevo] = L[nuevo][actual] = 1;
      }
      if(i-1 >= 0 && j+2 < N){
        size_t nuevo = CasillaToNodo({i-1,j+2},N);
        L[actual][nuevo] = L[nuevo][actual] = 1;
      }
      if(i-1 >= 0 && j+2 < N){
        size_t nuevo = CasillaToNodo({i-1,j+2},N);
        L[actual][nuevo] = L[nuevo][actual] = 1;
      }
      if(i-2 >= 0 && j-1 >= 0){
        size_t nuevo = CasillaToNodo({i-2,j-1},N);
        L[actual][nuevo] = L[nuevo][actual] = 1;
      }
      if(i-1 >= 0 && j-2 >= 0){
        size_t nuevo = CasillaToNodo({i-2,j-1},N);
        L[actual][nuevo] = L[nuevo][actual] = 1; 
      }

  //Ahora que tenemos todos los movimientos posibles del caballo, calculamos el camino más corto
  size_t origen = CasillaToNodo(Entrada, N);
  size_t destino = CasillaToNodo(Salida, N);
  std::vector<size_t> VerticesD(nvertices), CostesMinimos = Dijkstra(L, origen, VerticesD);
  return CostesMinimos[destino];
}