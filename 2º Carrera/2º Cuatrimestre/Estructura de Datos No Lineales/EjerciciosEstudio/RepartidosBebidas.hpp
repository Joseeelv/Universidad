#ifndef RepartidorBebidas_HPP
#define RepartidorBebidas_HPP

// **Enunciado:** Un repartidor de una empresa de distribución de bebidas tiene que visitar  
// a todos sus clientes cada día. Pero, al comenzar su jornada de trabajo, no conoce qué  
// cantidad de bebidas tiene que servir a cada cliente, por lo que no puede planificar una  
// ruta óptima para visitarlos a todos. Por tanto, nuestro repartidor decide llevar a cabo  
// la siguiente estrategia:  

// - El camión parte del almacén con la máxima carga permitida rumbo a su cliente  
//   más próximo.  
// - El repartidor descarga las cajas de bebidas que le pide el cliente. Si no tiene suficientes  
//   cajas en el camión, le entrega todas las que tiene. Este cliente terminará  
//   de ser servido en algún otro momento a lo largo del día cuando la estrategia de  
//   reparto vuelva a llevar al repartidor hasta él.  

// Después de servir a un cliente:  
// - Si quedan bebidas en el camión, el repartidor consulta su sistema de navegación  
//   basado en el GPS para conocer la ruta que le lleva hasta su cliente  
//   más próximo pendiente de ser servido.  
// - Si no quedan bebidas en el camión, vuelve al almacén por el camino más  
//   corto y otra vez carga el camión completamente.  

// Después de cargar el camión, el repartidor consulta su sistema de navegación y  
// se va por el camino más corto a visitar al cliente pendiente de ser servido más  
// próximo.  

// **Implementa un subprograma que calcule y devuelva la distancia total recorrida en un  
// día por nuestro repartidor a partir de lo siguiente:**  
// - Grafo representado mediante la matriz de costes con las distancias de los caminos  
//   directos entre los clientes y entre ellos y la central.  
// - Capacidad máxima del camión (cantidad de cajas de bebidas).  
// - Asumiremos que existe una función `int Pedido()` que devuelve el número de cajas  
//   que quedan por servir al cliente en el que se encuentra el repartidor.  

// **NOTA:** Es absolutamente necesario definir todos los tipos de datos implicados en la  
// resolución del problema, así como los prototipos de las operaciones utilizadas de los  
// TADs conocidos y también los prototipos de los algoritmos de grafo utilizados de los  
// estudiados en las asignaturas.


/*
Partimos de que tenemos un grafo ponderado (matriz de costes) con las distancias de los caminos que puede recorrer el camión, así como la capacidad máxima del camión, la posición del almacen y una funcion Pedido() que son las botellas que pide cada cliente del camión.

Nos piden crear un subprograma que devuelva la distancia mínima total recorrida por el camión por tanto haré uso de Dijkstra para ir obteniendo el coste de ir desde el vértices donde se encuentra  el camión hasta su próximo destino.

*/

#include <iostream>
#include "Materiales/alg_grafoPMC.h"

int Pedido(size_t cliente); //Función que nos dan

//Función auxiliar que me comprueba si siguen habiendo clientes sin ser abastecidos
bool ClientesPendientes(const vector<bool> &ClientesAbastecidos){
  for(size_t i = 0; i < ClientesAbastecidos.size(); i++){
    if(!ClientesAbastecidos[i]){
      //No se ha abastecido, devuelve True
      return true;
    }
  }
  return false; //si todos han sido abastecidos, devuelve false
}

//Función que me devuelve el vértice con menor coste de ir desde ese origen
size_t VerticeMasCercano(const matriz<size_t> &M, const vector<bool> &clientes, size_t vertice){
  //El vertice más cercano será aquel cuyo coste sea menor:
  size_t minimo = GrafoP<size_t>::INFINITO;
  size_t verticeMasCercano;
  for(size_t i = 0; i < M.dimension(); i++){ //recorro toda la matriz
    if(!clientes[i] && M[vertice][i] < minimo){ //compruebo si no ha sido abastecido y si su coste es menor que el minimo
      minimo = M[vertice][i]; //guardamos el coste como el mínimo y el vertice
      verticeMasCercano = i;
    }
  }
  return verticeMasCercano;
}

size_t DistanciaCamion(const GrafoP<size_t> &G, size_t almacen, size_t capacidadMax){
  //Primero de todo voy a declarar varios tipos de datos a usar
  size_t cajasCamion = capacidadMax;
  size_t actual = almacen;
  size_t siguiente_cliente = -1;
  size_t distanciaTotal = 0;
  size_t N = G.numVert();
  std::vector<bool>ClientesAbastecidos(N,false);
  
  //Ahora, hago uso de Floyd para calcular el coste mínimo de entre todos los pares de vértices
  matriz<size_t>Vertices(N),CostesMinimos(N);
  CostesMinimos = Floyd(G,Vertices);

  while(ClientesPendientes(ClientesAbastecidos)){
    //obtenemos el siguiente cliente (vértice)
    siguiente_cliente = VerticeMasCercano(CostesMinimos, ClientesAbastecidos, actual);
    size_t pedidoCliente = Pedido(siguiente_cliente);
    distanciaTotal += CostesMinimos[actual][siguiente_cliente]; //Guardamos la distancia de ir al nuevo cliente
    if(cajasCamion <= pedidoCliente){
      //Si el camión tiene menos cajas no lo abastecemos, tenemos que volver al almacen a reponer
      pedidoCliente -= cajasCamion;
      cajasCamion = 0;
      ClientesAbastecidos[siguiente_cliente] = false;
      distanciaTotal += CostesMinimos[siguiente_cliente][almacen];
      cajasCamion = capacidadMax;
      actual = almacen;
    }
    else{ //Lo abastece y quedan cajas en el camion
      cajasCamion -= Pedido(siguiente_cliente);
      ClientesAbastecidos[siguiente_cliente] = true;
      actual = siguiente_cliente; //avanzamos al siguiente cliente
    }
  }
  distanciaTotal += CostesMinimos[actual][almacen]; //Guardamos la distancia de ir desde el último cliente hasta el almacen
  
  return distanciaTotal;
}

#endif // !RepartidorBebidas_HPP