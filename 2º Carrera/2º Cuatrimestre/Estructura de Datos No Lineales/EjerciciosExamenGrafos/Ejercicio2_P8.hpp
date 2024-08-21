#ifndef LineasAereasTumbuctu2_HPP
#define LineasAereasTumbuctu2_HPP

/*
*El archipiélago de Tombuctú2 está formado por un número desconocido de islas, cada una de las cuales tiene, a su vez, un número desconocido de ciudades, las cuales tienen en común que todas y cada una de ellas dispone de un aeropuerto. Sí que se conoce el número total de ciudades del archipiélago (podemos llamarlo N, por ejemplo).*

*Dentro de cada una de las islas existen carreteras que permiten viajar entre todas las ciudades
de la isla. No existen puentes que unan las islas y se ha decidido que la opción de comunicación
más económica de implantar será el avión.*

*Se dispone de las coordenadas cartesianas (x, y) de todas y cada una de las ciudades del archipiélago. Se dispone de un grafo (matriz de adyacencia) en el que se indica si existe carretera
directa entre cualesquiera dos ciudades del archipiélago. El objetivo de nuestro problema es
encontrar qué líneas aéreas debemos implantar para poder viajar entre todas las ciudades del
archipiélago, siguiendo los siguientes criterios:*

1. Se implantará una y sólo una línea aérea entre cada par de islas.
2. La línea aérea escogida entre cada par de islas será la más corta entre todas las posibles.

*Ası́ pues, dados los siguientes datos:*

- *Lista de ciudades de Tombuctú2 representada cada una de ellas por sus coordenadas
cartesianas.*
- *Matriz de adyacencia de Tombuctú que indica las carreteras existentes en dicho archipiélago.*

*Implementen un subprograma que calcule y devuelva las líneas aéreas necesarias para comunicar adecuadamente el archipiélago siguiendo los criterios anteriormente expuestos.*
*/

/*
  Pasos a seguir:
    1. Creamos las islas con el TAD Particion (subconjuntos) mirando si hay carretera entre ambas ciudades (matriz de adyacencia = 1)
    2. Guardar en cada isla las ciudades con los costes de viajar entre la ciudades.
    3. Crear el archipiélago -> conjunto de islas.
    4. Crear las lineas aéreas recorriendo el archipielago.
    5. Quedarnos con las líneas aéreas menos costosas
    6. Devolver las líneas aéreas.
*/


#include <iostream>
#include <alg_grafoPMC.h>
#include <vector>
#include <cmath>

//Definimos los tipos de datos a usar
typedef std::pair<size_t,size_t> Ciudad; //ciudad con las coordenadas x , y

typedef struct LineaAerea{
  size_t Origen_, Destino_, CosteViaje_;
};

typedef vector<LineaAerea> LineasAereasArchipielago;

typedef struct Isla{
   vector<Ciudad> CiudadesIsla;
   matriz<size_t> CostesIsla;
};

typedef vector<Isla> Archipielago;

//Función que nos calcula la distancia euclidea de dos ciudaes
size_t DistanciaEuclidea(Ciudad a, Ciudad b){
  return sqrt(pow(a.first-b.first,2) + (a.second-b.second,2));
}

//Función que nos calcula los costes minimos de cada isla dado su conjunto de ciudades
matriz<size_t> CalculaCostesIsla(vector<Ciudad> &ciudades){
  //Creamos el grafo para poder realizar el cálculo de los costes mínimos
  GrafoP<size_t> GIsla(ciudades.size());
  //Rellenamos el grafo con los costes (Distancia Euclídea)
  for(size_t i = 0; i < ciudades.size(); i++)
    for(size_t j =  i+1; j < ciudades.size(); j++){
      GIsla[i][j] = GIsla[j][i] = DistanciaEuclidea(ciudades[i],ciudades[j]);
    }
  //Rellenado el grafo, vamos a calcular sus costes mínimos, con Floyd por lo que creamos las matrices de vértices y costes
  matriz<size_t>Vertices(GIsla.numVert()),CostesMinimos(GIsla.numVert());
  return CostesMinimos = Floyd(GIsla,Vertices);
}

//Sabemos que partimos de una matriz de adyacencia (grafo no ponderado) y del conjunto de ciudades
LineasAereasArchipielago Tumbuctu(const Grafo& G, vector<Ciudad> &ciudades){
  //Con la matriz de adyacencia sabemos si una ciudad está en la misma isla que otra si esta devuelve 1, si no devuelve 0.
  //Sabiendo esto podemos ir recorriendo la matriz e insertandon en cada subconjunto de la partición las ciuades.
  size_t Tama = G.numVert();
  Particion P(Tama);
  //Recorremos el grafo comprobando si hay carretera
  for(size_t i = 0; i < Tama; i++)
    for(size_t j = 0; j < Tama; j++){
      if(G[i][j] && P.encontrar(i) != P.encontrar(j)){ //Hay carretera y no están unidas (distinto representante), las unimos en el mismo subconjunto.
        P.unir(P.encontrar(i),P.encontrar(j));
      }
    }
  //Tenemos los sunconjuntos crados, por lo que vamos a insertar en cada isla sus ciudades el coste
  size_t representante_actual = P.encontrar(0);
  Isla isla;
  Archipielago archipielago; //contiene el número de islas
  for(size_t i = 0; i < ciudades.size(); i++){
    if(P.encontrar(i) == representante_actual){ //está en esa isla
      isla.CiudadesIsla.push_back(ciudades[i]);
    }
    else{ //si no tiene el mismo representante, metemos la isla en el archipiélago y cambiamos el representante
      isla.CostesIsla = CalculaCostesIsla(isla.CiudadesIsla); //gaurdamos los costes mínimos de la isla
      archipielago.push_back(isla); //almacenamos la isla en el archipiélago
      //limpiamos el vector de ciudades de la isla
      isla.CiudadesIsla.clear();
      isla.CiudadesIsla.push_back(ciudades[i]); //insertamos la nueva ciudad
      representante_actual = P.encontrar(i); //nuevo representante, de la nueva ciudad      
    }
  }
  //Ya tenemos las islas y el archipiélago creado, vamos a obtener ahora las líneas aéreas del mismo.


  //Para ello, haremos uso del TAD APO, ya que el coste de encontrar el mínimo es de orden O(1).
  Apo<LineaAerea> A(archipielago.size()*(archipielago.size()-1));
  //Guardamos en el APO todas las líneas aéreas posible
  for(size_t i = 0; i < archipielago.size(); i++)
    for(size_t j = 0; j < archipielago.size(); j++){
      if(P.encontrar(i) != P.encontrar(j)){
        //Distinto representante, distinta isla -> linaea aerea
        //insertamos la linea aérea en el apo
        size_t representanteOrigen = P.encontrar(i);
        size_t representanteDestino = P.encontrar(j);
        A.insertar({representanteOrigen,representanteDestino,DistanciaEuclidea(ciudades[i],ciudades[j])});
      }
      //son de la misma isla, no hay linea aérea
    }
  //Tenemos el APO con las líneas aéreas, vamos a quedarnos con las menos costosas
  //Vamos a crearnos una matriz de adyacencia de las islas para saber que islas están unidas
  matriz<bool> ConexiónIsla(archipielago.size(),false);

  LineasAereasArchipielago vector_LA((archipielago.size()*(archipielago.size()-1))/2);
  size_t contador = 0;
  while(!A.vacio() && contador < (archipielago.size()*(archipielago.size()-1))/2){
    LineaAerea aux = A.cima(); //linea aérea menos costosa
    if(P.encontrar(aux.Origen_) != P.encontrar(aux.Destino_) && ConexiónIsla[aux.Origen_][aux.Destino_] ==false){ 
      //son islas diferentes y no están conectadas. 
      ConexiónIsla[aux.Origen_][aux.Destino_] = ConexiónIsla[aux.Origen_][aux.Destino_] = true;
      //rellenamos el vector de las lineas aereas
      vector_LA[contador].Origen_ = aux.Origen_;
      vector_LA[contador].Destino_ = aux.Destino_;
      vector_LA[contador].CosteViaje_ = aux.CosteViaje_;
      contador++ ; //aumentamos el contador de las líneas aéreas.
    }
  }
  return vector_LA;
}

#endif // !LineasAereasTumbuctu2_HPP
