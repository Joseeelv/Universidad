#include <iostream>
#include <vector>
#include "../Materiales/grafoPMC.h"
#include "../Materiales/alg_grafoPMC.h"

/*Ejercicio 2*/
size_t longitud_pseudocentro(const GrafoP<size_t>& G){
	matriz<size_t> D;
	matriz<GrafoP<size_t>::vertice> V;
	D=Floyd(G,V); //obtenemos la matriz de costes (optimizada)
	size_t pseudocentro;
    double media = GrafoP<size_t>::INFINITO;
    //Recorremos la matriz de costes y buscamos el centro (nodo con coste medio)
	for (auto i=0; i<D.dimension(); i++){
        size_t medialocalnodo= 0; //variable que nos calcula la media del nodo
		for(auto j=0;j<D.dimension(); j++){
			medialocalnodo += D[i][j];
		}
        //calculamos el nuevo pseudocentro
        medialocalnodo /= G.numVert();
        if(medialocalnodo < media){
            media = medialocalnodo;
            pseudocentro = i;
        }
    }
    //Tenemos que buscar los dos nodos más lejanos para calcular la longitud
    //Valores mínimos máximos respecto al pseudocentro
    size_t max1=0;
    size_t max2=0;
    for(auto i=0; i<D.dimension();i++){
        if(D[pseudocentro][i]> max2){
            max2 = D[pseudocentro][i];
            if(max2 > max1) std::swap(max1,max2);
        }
    }
    return (max1+max2);
}

/*Ejercicio 3*/
bool subvencion(const GrafoP<size_t> &G){
    matriz<size_t> D;
    matriz<GrafoP<size_t>::vertice> V;
    D = Floyd(G, V);
    bool res = true;
    // Recorremos V para comprobar si hay ciclos
    // Usando un vector booleano de visitados
    for (size_t i = 0; i < V.dimension(); i++)
    {
        std::vector<bool> visitados(V.dimension(), false);
        if (hayCiclo(V, i, visitados))
            res = false;
    }
}
bool hayCiclo( matriz<GrafoP<size_t>::vertice>& v, size_t nodo, std::vector<bool> &visitados){
}