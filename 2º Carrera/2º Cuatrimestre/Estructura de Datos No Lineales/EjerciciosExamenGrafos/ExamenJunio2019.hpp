/**El archipiélago de Tombuctú2 está formado por un número desconocido de islas, cada una de las cuales tiene, a su vez, un número desconocido de ciudades, las cuales tienen en común que todas y cada una de ellas dispone de un aeropuerto. 
Sí que se conoce el número total de ciudades del archipiélago (podemos llamarlo N, por ejemplo). Dentro de cada una de las islas existen carreteras que permiten viajar entre todas las ciudades de la isla. 
No existen puentes que unan las islas y se ha decidido que la opción de comunicación más económica de implantar será el avión. Se dispone de las coordenadas cartesianas (x, y) de todas y cada una de las ciudades del archipiélago.*

*Se dispone de un grafo (matriz de adyacencia) en el que se indica si existe carretera directa entre cualesquiera dos ciudades del archipiélago.*

 
*El objetivo de nuestro problema es encontrar qué líneas aéreas debemos implantar para poder viajar entre todas las ciudades del archipiélago, siguiendo los siguientes criterios:*

*1. Se implantará una y sólo una línea aérea entre cada par de islas.*

*2. La línea aérea escogida entre cada par de islas será la más corta entre todas las posibles.*

*Así pues, dados los siguientes datos:* 

*• Lista de ciudades de Tombuctú2 representada cada una de ellas por sus coordenadas cartesianas.*

*• Matriz de adyacencia de Tombuctú que indica las carreteras existentes en dicho archipiélago,* 

*Implementen un subprograma que calcule y devuelva las líneas aéreas necesarias para comunicar adecuadamente el archipiélago siguiendo los criterios anteriormente expuestos.*

Partimos de que contamos con la lista de ciudades de Tumbuctú, donde una ciudad es el par de dos coordenadas cartesianas (x, y), que las representaremos como dos enteros, además contamos con la matriz de adyacencia, donde nos indica que ciudades están conectadas con otras por las carreteras.

Como tenemos que implementar líneas aéreas, cogeremos las que menor distancia haya entre cada par de ciudades más cercanas, es decir, su coste sea el menor (distancia euclidea).

Finalmente haremos uso de Floyd para calcular el coste mínimo de ir desde cualquier par de ciudades del archipiélago, ya que no tenemos ni un origen ni destino concretos.*/


#include <iostream>
#include <vector>
#include "alg_grafoPMC.h"
#include <cmath>

//Definimos los tipos de datos a usar 
typedef std::pair<size_t,size_t> ciudad;
typedef std::pair<ciudad,ciudad> LineaAerea;

//Suponemos que una isla es el conjunto de ciudades con su coste
typedef struct{
  vector<ciudad>CiudadesIsla;
  matriz<size_t> coste;
}isla;

//Un archipielago será el conjunto de islas
typedef vector<isla>Archipielago;

size_t DistanciaEuclidea(ciudad a, ciudad b){
  return sqrt(pow(a.first-b.first,2) + pow(a.second-b.second,2));
}

//Función que nos calcula el coste de viajar entre las ciudades de una isla
matriz<size_t> CalcularCostesIsla(vector<ciudad> &ciudades){
  //Creamos el Grafo que almacenará los costes de viajar entre cualquier ciudad de la isla
  GrafoP<size_t> CostesIsla(ciudades.size());
  //Como queremos los costes mínimos vamos a declarar las matrices de vértices y costesminimos para realizar Floyd
  matriz<size_t>vertices(CostesIsla.numVert()),CostesMinimos(CostesIsla.numVert());
  //Rellenamos el grafo con los costes
  for(size_t i = 0; i < ciudades.size(); i++)
    for(size_t j = i+1; j < ciudades.size(); j++){
      CostesIsla[i][j] = DistanciaEuclidea(ciudades[i],ciudades[j]);
    }
  //Ahora vamos a obtener los costes minimos
   return CostesMinimos = Floyd(CostesIsla,vertices);
}

vector<LineaAerea> Tumbuctu(Grafo &Carreteras, vector<ciudad> &ciudades){
  //Creamos un vector que contendrá las lineas aéreas a devolver
  vector<LineaAerea> vector_lineasAereas;

  //Vamos a crear el Grafo Archipielago, a partir de la matriz de adyacencia de las carreteras
  //Tenemos un archipielago (conjunto de isla), como tenemos que identificar las ciudades de cada isla lo haremos mediante el TAD Partición, donde cada ciudad tendrá un representante (que será la capital de la isla).
  Particion p(ciudades.size());
  //Ahora vamos a ir obteniendo los subconjuntos
  for(size_t i = 0; i < ciudades.size(); i++)
    for(size_t j = i+1; j < ciudades.size(); j++){
      if(Carreteras[i][j]){ //Hay dos ciudades unidas por una carretera, están en la misma isla
        p.unir(p.encontrar(i),p.encontrar(j));
      }
    }
  //En p tenemos las islas formadas, por lo que vamos a crear el archipielago
  Archipielago archipielago;
  //Ahora recorriendo la partición p, vamos a crear una isla por cada subconjunto.
  size_t represenante_isla = p.encontrar(0);
  isla IslaAux;
  for(size_t i = 0; i < ciudades.size(); i++)
    //Si el representante de la ciudad es el mimso que el de la isla, esta ciudad pertenecerá a dicha isla
    if(p.encontrar(i) == represenante_isla)
      IslaAux.CiudadesIsla.push_back(ciudades[i]);
    else{
      //Si hemos cambiado de representante, hemos cambiado de isla, por lo que esta la guardamos y creamos otra
      IslaAux.coste = CalcularCostesIsla(IslaAux.CiudadesIsla);
      //Guardamos la isla en el archipielago
      archipielago.push_back(IslaAux);
      //Borramos el vector de ciudades de la isla
      IslaAux.CiudadesIsla.clear();
      //añadimos la nueva ciudad,
      IslaAux.CiudadesIsla.push_back(ciudades[i]);
      represenante_isla = p.encontrar(i); //nuevo representante
    }
  //Ya tenemos creado el archipielago, con sus islas y carreteras, ahora vamos a obtener las líneas aéreas del propio archipielago
  //Para ello, vamos a recorrer todas las islas
  for(size_t i = 0; i < archipielago.size(); i++)
    for(size_t j = i+1; j < archipielago.size(); j++){
      //Vamos a obtener el coste de ir entre las dos ciudades
      size_t CosteMinimo = GrafoP<size_t>::INFINITO;
      ciudad CiudadOrigen, CiudadDestino; //guardamos las ciudades de la linea aerea
      //vamos a recorrer cada ciudad de cada isla
      for(size_t k = 0; k < archipielago[i].CiudadesIsla.size(); k++)
        for(size_t l = 0; l < archipielago[j].CiudadesIsla.size(); l++){
          if(DistanciaEuclidea(archipielago[i].CiudadesIsla[k], archipielago[j].CiudadesIsla[l]) < CosteMinimo){
            CosteMinimo = DistanciaEuclidea(archipielago[i].CiudadesIsla[k], archipielago[j].CiudadesIsla[l]);
            CiudadOrigen = archipielago[i].CiudadesIsla[k];
            CiudadDestino = archipielago[j].CiudadesIsla[l];
          }
        }
      vector_lineasAereas.push_back({CiudadOrigen,CiudadDestino});
    }
  return vector_lineasAereas;
} 