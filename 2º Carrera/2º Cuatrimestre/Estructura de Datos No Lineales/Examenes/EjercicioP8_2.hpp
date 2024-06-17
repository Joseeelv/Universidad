// El archipiélago de Tombuctú2 está formado por un número desconocido de islas, cada una de las cuales tiene, a su vez, un número desconocido de ciudades, las cuales tienen en común que todas y cada una de ellas dispone de un aeropuerto. Sí que se conoce el número total de ciudades del archipiélago (podemos llamarlo N, por ejemplo). Dentro de cada una de las islas existen carreteras que permiten viajar entre todas las ciudades de la isla. No existen puentes que unan las islas y se ha decidido que la opción de comunicación más económica de implantar será el avión. Se dispone de las coordenadas cartesianas (x, y) de todas y cada una de las ciudades del archipiélago. Se dispone de un grafo (matriz de adyacencia) en el que se indica si existe carretera directa entre cualesquiera dos ciudades del archipiélago. El objetivo de nuestro problema es encontrar qué líneas aéreas debemos implantar para poder viajar entre todas las ciudades del archipiélago, siguiendo los siguientes criterios: 
  //  1) Se implantará una y sólo una línea aérea entre cada par de islas. 
  //  2) La línea aérea escogida entre cada par de islas será la más corta entre todas las posibles. Así pues, dados los siguientes datos:
      // • Lista de ciudades de Tombuctú2 representada cada una de ellas por sus coordenadas cartesianas.
      // • Matriz de adyacencia de Tombuctú que indica las carreteras existentes en dicho archipiélago
// Implementen un subprograma que calcule y devuelva las líneas aéreas necesarias para comunicar adecuadamente el archipiélago siguiendo los criterios anteriormente expuestos.

/*
  Tenemos un numero indeterminado de islas, N.
  Tenemos varias ciudades por islas, por tanto, una isla es una conjunto de ciudades.
  Cada ciudad tiene un aeropuerto.
  Una ciudad se compone de dos coordenadas (x,y).
  Tenemos un grafo (matriz de adyacencia), que indica las carreteras entre ciudades.
  Tenemos que conectar dos ciudades de dos islas diferentes que más cercan estén.
  Contamos con una lista de ciudades del archipielago.
*/

#include <iostream>
#include <vector>
#include "../Grafos/Materiales/alg_grafoMA.h"
#include "../Grafos/Materiales/alg_grafoPMC.h"
#include "../Grafos/Materiales/particion.h"
#include <algorithm>
#include "../Materiales/apo.h"
#include <cmath>
//Ciudad
typedef std::pair<size_t,size_t>ciudad;
//Linea aerea
typedef struct LineaAerea{
  ciudad ciudadO, ciudadD;
  double coste;
};

vector<LineaAerea> Tombuctu2(const vector<ciudad>& ciudades, const Grafo& Carretera){
  size_t N = ciudades.size();
  size_t NlineasAereas = nlineas(N); //lineas aereas como máximo.

  //Creamos una partiion del grafo de tamaño todas las ciudades.
  Particion islas = organiza(Carretera, N);
  GrafoP<double>CosteMinimo(Carretera.numVert()); //creamos un grafo y lo rellenamos.
  for(auto i = 0; i<CosteMinimo.numVert(); i++)
  {
    for(auto j = 0; j<CosteMinimo.numVert();j++)
    {
      CosteMinimo[i][j] = DistanciaEU(ciudades[i],ciudades[j]);
    }
  }
  vector<LineaAerea> res(NlineasAereas);
  Apo<LineaAerea>LineasAereas = rellenarApo(ciudades, islas);
  matriz<bool>LineasUsadas(N,false);
  size_t linea_actuales = 0;
  while(linea_actuales < NlineasAereas){
    
    LineaAerea actual = LineasAereas.cima();
    LineasAereas.suprimir(); //eliminamos el elemento insertado en el vector
    size_t vertice1 = islas.encontrar(ciudadAIndice(ciudades, actual.ciudadO)); //obtenemos la isla con menor coste
    size_t vertice2 = islas.encontrar(ciudadAIndice(ciudades, actual.ciudadD));

    size_t representante_1 = islas.encontrar(vertice1); //buscamos la ciudad representante de cada isla
    size_t representante_2 = islas.encontrar(vertice2);

    if(!LineasUsadas[representante_1][representante_2])  //comprobamos que las ciudades de esas islas no esten conectadas.
    {
      linea_actuales ++;//actualizamos el contador.
      res.push_back(actual); //insertamos la pareja de ciudades que es la linea aerea en el vector de lineas aereas.
      LineasUsadas[representante_1][representante_2] = 
            LineasUsadas[representante_2][representante_1] = true; //ponemos que esas islas ya están unidas
    }
  }
  return res;
}

size_t ciudadAIndice(vector<ciudad> ciudades, ciudad c)
{
    for (size_t i = 0; i < ciudades.size(); i++)
        if (ciudades[i] == c) return i;

    return ciudades.size();
}

double DistanciaEU(ciudad a, ciudad b)
{
  return sqrt(std::pow(a.first - b.first,2)-std::pow(a.second - b.second,2));
}

Particion organiza(const Grafo& Carretera, size_t& numIslas)
{
  Particion isla(Carretera.numVert()); 
    //recorremos la matriz de adyacencia
  for(auto i = 0; i < Carretera.numVert(); i++)
  {
    for(auto j=i+1; j < Carretera.numVert(); j++)
    {
      if(Carretera[i][j])
      { //Si hay carretera, buscamos representante.
        size_t representante_1 = isla.encontrar(i);
        size_t representante_2 = isla.encontrar(j);
        if(representante_1 != representante_2)
        {//Si los representantes son distintos, se unen.
          numIslas--;
          isla.unir(representante_1,representante_2);
        }
      }
    }
  }
  return isla;
}

size_t nlineas(size_t n)
{
  return (n*(n-1))/2;
}

Apo<LineaAerea> rellenarApo(vector<ciudad> ciudades, Particion p)
{
    Apo<LineaAerea> res(ciudades.size());
    for (size_t i = 0; i < ciudades.size(); i++)
        for (size_t j = 0; j < ciudades.size(); j++)
        {
            int isla1 = p.encontrar(i);
            int isla2 = p.encontrar(j);
            if (isla1 != isla2)
            { // Distintas islas, necesitamos construir linea
                LineaAerea linea = {ciudades[i],ciudades[j],DistanciaEU(ciudades[i],ciudades[j])};
                res.insertar(linea);
            }
        }
    return res;
}