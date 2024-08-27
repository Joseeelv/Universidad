/*Un repartidor de una empresa de distribucion de bebidas tiene que visitar a todos sus clientes cada dias.Pero, al comentar su jornada de trabajo, no conoce que cantidad de bebidas
tiene que servir cada cliente, por lo que no puede planificar una ruta optima para visitarlos a todos. Por tanto, nuestro repartidor decide llevar
a cabo la siguiente estrategia: 
    -El camión parte del almacen con la máxima carga permitida rumbo a su cliente más próximo
    - El repartidor descarga las cajas de bebidas que le pide el cliente. si no tiene suficientes cajas en el camion, le entrega todas las que tiene. Este cliente terminara de ser servido en algun otro momento a lo largo del dia cuando la estratefia de reparto vuelva a llevar al repartidor hasta él
    - Después de servir a un cliente:
    - Si quedan bebidas en el camion, el repartidor consulta su sistema de navegacion basado en el GPS para conocer la ruta que le lleva hasta su cliente más proximo pendiente de ser servido.
    - Si no quedan bebidas en el camion, vuelve al almacén por el camino más corto y otra vez carga el camión completamente
    - Despues de cargar el camión, el repartidor consulta su sistema de navegacion y se va por el camino mas corto a visitar al cliente pendiente de ser servido más proximo Implementa un subprograma que calcule y devuelva, la distancia total recorrida en un dia por nuestro repartidor a partir de lo siguiente :
    - Grafo representado mediante la matriz de costes con las distancias de los caminos directos entre los clientes y entre ellos y la central
    - Capacidad máxima del camión ( cantidad de cajas de bebidas)
    - Asumiremos que existe una funcion int Pedido() que devuelve el numero de cajas que quedan por servir al cliente en el que se encuentra el repartidor
NOTA: Es absolutamente necesario definir todos los tipos de datos implicados en la resolucion del problema, así como los prototipos de las operaciones utilizadas de los TADS conocidos y tambien los prototipos de los algoritmos de grafo utilizados de los estudiados en las asignaturas*/

#include <iostream>
#include "grafoPMC.h"
#include "alg_grafoPMC.h"


//Contamos con un método axuliar llamado Pedido, que nos devuelve el pedido de un nodo del grafo
size_t Pedido(size_t cajas);

//Función auxiliar que comprueba si un cliente ha sido abastecido o no
bool visitados(const vector<bool>abastecidos){
  for(size_t i = 0; i < abastecidos.size(); i++)
    if(!abastecidos[i])
      return true;
    return false;
}

//Función auxiliar que nos devolverá el vértice que se une a él con la arista de menor coste, es decir, el cliente más cercano
size_t VerticeMasCercano(matriz<size_t> &M, size_t vertice){
  size_t minimo = 0;
  for(size_t i = 0; i < M.dimension(); i++){
    if(M[vertice][i] < minimo)
      minimo = M[vertice][i];
  }
  return minimo;
}
size_t DistanciaRepartidor(GrafoP<size_t> &G, size_t CapacidadMax, size_t AlmacenCentral){
  //Declaramos las matrices de vértices y CosteMínimo para poder calcular Floyd
  matriz<size_t>vertices,CostesMinimos;
  CostesMinimos = Floyd(G,vertices);
  //A partir de esta matriz ya podemos calcular los costes de ir desde el almacen repartiendo.

  size_t CajasCamion = CapacidadMax; // variable que contiene el número de cajas actuales del camión
  size_t nparadas = G.numVert(); //el número de vértices del grafo equivale al número de clientes a abastecer
  //Ahora nos creamos un vector de boolanos que nos dirán que clientes están abastecidos y cuales no
  vector<bool>ClientesAbastecidos(G.numVert(),false); //todos a falso.
  size_t DistanciaTotal = 0;
  size_t VerticeActual = AlmacenCentral;
  size_t VerticeAux; //vertice al que iremos desde el central

  //Vamos a ir recorriendo nuestro grafo (hasta que el vector de bool esté entero a true) y calculando el coste
  while(!visitados(ClientesAbastecidos)){
    VerticeAux = VerticeMasCercano(CostesMinimos,VerticeActual); //conseguimos el vértice más cercano
    DistanciaTotal += CostesMinimos[VerticeActual][VerticeAux]; //Sumamos el coste de ir a dicho vertice
    if(CajasCamion <= Pedido(VerticeActual)){ //Al abastecer al cliente  nos quedamos sin cajas:
      Pedido(VerticeActual) -= CajasCamion; //Abastecemos (no del todo) --> volvemos al alamcen --> terminamos de abastecer
      DistanciaTotal += CostesMinimos[VerticeActual][AlmacenCentral];
      //Estamos en el almacen de nuevo, recargamos
      VerticeActual = AlmacenCentral;
      //Rellenamos el camion
      CajasCamion = CapacidadMax;
    }
    else{
      size_t CajasAux = Pedido(VerticeActual); //Guardamos el número de cajas abastecer para actualizar el camión más tarde
      Pedido(VerticeActual) -= CajasCamion; //Abastecemos al cliente
      CajasCamion -= CajasAux; //Actualizamos el número de Cajas del camión con el del pedido
      //hemos abastecido exitosamente el cliente, lo indicamos en el vector de visitados
      ClientesAbastecidos[VerticeActual] = true;      
    }
  } 
  //Devolvemos la distancia que recorrer el camión
  return DistanciaTotal;
}
