#include <iostream>
#include <vector>
#include "../Materiales/grafoPMC.h"
#include "../Materiales/alg_grafoPMC.h"
#include <cmath>
// El archipiélago de Tombuctú2 está formado por un número desconocido de islas, cada una de las cuales tiene, a su vez, un número desconocido de ciudades, las cuales tienen en común que todas y cada una de ellas dispone de un aeropuerto. Sí que se conoce el número total de ciudades del archipiélago (podemos llamarlo N, por ejemplo). Dentro de cada una de las islas existen carreteras que permiten viajar entre todas las ciudades de la isla. No existen puentes que unan las islas y se ha decidido que la opción de comunicación más económica de implantar será el avión. Se dispone de las coordenadas cartesianas (x, y) de todas y cada una de las ciudades del archipiélago. Se dispone de un grafo (matriz de adyacencia) en el que se indica si existe carretera directa entre cualesquiera dos ciudades del archipiélago. 
//El objetivo de nuestro problema es encontrar qué líneas aéreas debemos implantar para poder viajar entre todas las ciudades del archipiélago, siguiendo los siguientes criterios:

// 1. Se implantará una y sólo una línea aérea entre cada par de islas.
// 2. La línea aérea escogida entre cada par de islas será la más corta entre todas las posibles. Así pues, dados los siguientes datos: 

// •Lista de ciudades de Tombuctú2 representada cada una de ellas por sus coordenadas cartesianas.
// •Matriz de adyacencia de Tombuctú que indica las carreteras existentes en dicho archipiélago, 

// Implementen un subprograma que calcule y devuelva las líneas aéreas necesarias para comunicar adecuadamente el archipiélago siguiendo los criterios anteriormente expuestos.

//Creamos el tipo coordenada
typedef std::pair<size_t,size_t>ciudad; //dos coordenadas es una ciudad


vector<std::pair<ciudad,ciudad>> Tombuctú2(vector<ciudad>ciudades, const Grafo& archipielago)
{
    //Creamos un vector de lineas Aereas auxiliar que vamos a devolver
    vector<std::pair<ciudad,ciudad>> lineaAereaAux;
    archipielago archi;
    rellenar(c, carreteras,archi);

    //Recorremos una par de islas para buscar las ciudades más cercanas
    for(size_t i = 0; i<archi.size(); i++){
        for(size_t j = i+1; j<archi.size(); j++){
            size_t costeMin = GrafoP<size_t>::INFINITO;
            ciudad CiudadIsla1, CiudadIsla2;
            for(size_t k = 0; k<archi[i].size(); k++){
                for(size_t l = 0; l<archi[j].size(); l++){
                    if(distanciaEuclidea(archi[i].ciudades[k], archi[j].ciudades[l])<costeMin){
                        costeMin = distanciaEuclidea(archi[i].ciudades[k], archi[j].ciudades[l]);
                        CiudadIsla1 = archi[i].ciudades[k];
                        CiudadIsla2 = archi[j].ciudades[l];
                    }
                }
            }
            lineaAereaAux.push_bacK({CiudadIsla1, CiudadIsla2});
        }
    }
    return lineaAereaAux;
}

size_t distanciaEuclidea(ciudad i, ciudad j)
{
    return sqrt(pow(i.first - j.first, 2) + pow(i.second - j.second, 2));
}

void rellenar(vector<ciudad> c, Grafo carreteras, Grafo& archipielago)
{
    Particion p(c.size());
    // [{c1},{c2},{c3},{c4},{c5},{c6},{c7}]
    for (size_t i = 0; i < c.size(); i++)
    {
        for (size_t j = i + 1; j < c.size(); j++)
        {
            if (carreteras[i][j])
            {
                p.unir(p.encontrar(i), p.encontrar(j));
            }
        }
    }
}


/*
    Tenemos que buscar las ciudades más cercanas entre islas -> menor distnacia euclidea
    Las mas cercanas, las conectamos con una linea aerea.
    Devolvemos el vector
*/