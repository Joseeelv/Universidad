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
	for (size_t i=0; i<D.dimension(); i++){
        size_t medialocalnodo= 0; //variable que nos calcula la media del nodo
		for(size_t j=0;j<D.dimension(); j++){
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
    for(size_t i=0; i<D.dimension();i++){
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
    bool flag = true;
    // Recorremos V para comprobar si hay ciclos
    // Usando un vector booleano de visitados
    for (size_t i = 0; i < V.dimension(); i++)
    {
        std::vector<bool> visitados(V.dimension(), false);
        if (hayCiclo(V, i, visitados))
            flag = false;
    }
    return flag;
}
bool hayCiclo( matriz<GrafoP<size_t>::vertice>& v, size_t nodo, std::vector<bool> &visitados){
    if(visitados[nodo]) return true;
    visitados[nodo]= true;
    for(size_t i = 0; i<v.dimension();i++){
        if(v[nodo][i] != GrafoP<size_t>::INFINITO){
            return hayCiclo(v,i,visitados);
        }
    }
    return false;
}


typedef GrafoP<size_t>::vertice ciudades; //Conjunto de ciudades "vertices" del grafo
typedef std::vector<ciudades>ciudades_rebeldes;//Conjunto de las ciudades rebeldes
typedef std::pair<ciudades,ciudades>Carretera; //carretera formada por dos ciudades
typedef std::vector<Carretera>carreteras_cortadas;//Conjunto de carreteras cortadas

/*Ejercicio 4*/
matriz<size_t> 
Zuelandia(GrafoP<ciudades>& Z, ciudades_rebeldes& CR, carreteras_cortadas& CC, const ciudades& Capital){
    //Recorremos las carreteras cortadas 
    for(size_t i = 0; i<CC.size(); i++){
        //Modificamos las carreteras cortadas
        Z[CC[i].first][CC[i].second] == GrafoP<size_t>::INFINITO;
    }
    //Recorremos las ciudades rebeldes
    for(size_t i = 0; i<CR.size();i++) //taamaño del vector de ciudades rebeldes
        for(size_t j=0; j<Z.numVert();j++){//recorremos el grafo
            //Si es infinito significa que no hay conexion
            Z[CR[i]][j] = GrafoP<size_t>::INFINITO;
            Z[j][CR[i]] = GrafoP<size_t>::INFINITO;
        }
    
    for(size_t i=0; i<Z.numVert();i++)//recorremos el grafo
        Z[i][Capital] = 0; //todos los caminos a la capital son coste 0
    
    //Como todos los viajes deben ser desde la capital, hacemos Floyd
    for (size_t i = 0; i < Z.numVert(); i++){
        if (i != Capital){
            for (size_t j = 0; j < Z.numVert(); j++){
                if(j!=Capital){
                //Ponemos a infinito todas las carreteras que no pasen por la capital
                    Z[i][j]==GrafoP<size_t>::INFINITO;
                }
            }
        }
    }
    //AHora hacemos la matrz de costes mínimos
    matriz<size_t> resultado_Floyd;
    matriz<ciudades>P;
    resultado_Floyd= Floyd(Z,P);
    return resultado_Floyd;
}