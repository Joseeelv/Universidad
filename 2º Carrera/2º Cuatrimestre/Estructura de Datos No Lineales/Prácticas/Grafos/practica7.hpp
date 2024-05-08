#include <iostream>
#include <vector>
#include <algorithm>
#include "../Materiales/grafoPMC.h"
#include "../Materiales/alg_grafoPMC.h"

/*Ejercicio 1*/
template <typename size_t>
matriz<size_t> MaxFloyd(const GrafoP<size_t>& G, matriz<typename GrafoP<size_t>::vertice>&P){
    typedef typename GrafoP<size_t>::vertice vertice;
    const size_t n = G.numVert();
    matriz<size_t> A(n);   // matriz de costes mínimos

    // Iniciar A y P con caminos directos entre cada par de vértices.
    P = matriz<vertice>(n);
    for (vertice i = 0; i < n; i++) {
        A[i] = G[i];                    // copia costes del grafo
        A[i][i] = 0;                    // diagonal a 0
        P[i] = vector<vertice>(n, i);   // caminos directos
    }
    // Calcular costes mínimos y caminos correspondientes
    // entre cualquier par de vértices i, j
    for (vertice k = 0; k < n; k++)
        for (vertice i = 0; i < n; i++)
            for (vertice j = 0; j < n; j++) {
                size_t ikj = maximointeligente(A[i][k], A[k][j]);
            }
    return A;
}

template <typename size_t>
size_t maximointeligente(size_t a, size_t b){
    if(a==GrafoP<size_t>::INFINITO) return b;
    if(b==GrafoP<size_t>::INFINITO) return a;
    else return std::max(a,b);
}

/*Ejercicio 2*/
struct Casilla{
    int fila_,columna_;
};
typedef std::pair<Casilla,Casilla>pared;

typedef GrafoP<size_t>Laberinto;
typedef std::vector<pared>Paredes;

bool adyacentes(Casilla a, Casilla b){
	return (std::abs(a.fila_ - b.fila_) + std::abs(a.columna_ - b.columna_)==1);
}

Casilla vertice_casilla(Laberinto::vertice n, size_t N){
    Casilla C;
	C.fila_ = n / N; //Div
	C.columna_ = n % N; //MOD
	return C;
}

Laberinto::vertice casilla_nodo(Casilla c, int N){
	return c.fila_*N + c.columna_;
}

vector<Casilla> 
CaminoMasCorto(int N, Paredes& paredes, Casilla& Entrada, Casilla& Salida){
    typedef GrafoP<size_t>G(N*N);
    for(size_t i =0; i<N;i++)

}


vector<GrafoP<size_t>::vertice> laberinto(size_t N, Paredes p, Casilla entrada, Casilla salida)
{
    GrafoP<size_t> G(N * N);
    for (size_t i = 0; i < N; i++)
    {
        for (size_t j = 0; j < N; j++)
        {
            if (i > 0)
            {
                if (find(p.begin(), p.end(), pared{{i, j}, {i - 1, j}}) == p.end())
                {
                    G[casilla_nodo({i, j}, N)][casilla_nodo({i - 1, j}, N)] = 1;
                }
            }
            if (i < N - 1)
            {
                if (find(p.begin(), p.end(), pared{{i, j}, {i + 1, j}}) == p.end())
                {
                    G[casilla_nodo({i, j}, N)][casilla_nodo({i + 1, j}, N)] = 1;
                }
            }
            if (j > 0)
            {
                if (find(p.begin(), p.end(), pared{{i, j}, {i, j - 1}}) == p.end())
                {
                    G[casilla_nodo({i, j}, N)][casilla_nodo({i, j - 1}, N)] = 1;
                }
            }
            if (j < N - 1)
            {
                if (find(p.begin(), p.end(), pared{{i, j}, {i, j + 1}}) == p.end())
                {
                    G[casilla_nodo({i, j}, N)][casilla_nodo({i, j + 1}, N)] = 1;
                }
            }
        }
    }

    vector<GrafoP<size_t>::vertice> P;
    matriz<GrafoP<size_t>::vertice> M;
    Floyd(G, M);
    P.push_back(casilla_nodo(entrada, N));
    GrafoP<size_t>::vertice v = casilla_nodo(salida, N);
    while (v != P.back())
    {
        P.push_back(v);
        v = M[casilla_nodo(entrada, N)][v];
    }
    return P;
    
}

/*Ejercicio 6*/

matriz<size_t> tarifaminima(const GrafoP<size_t>&tren,const GrafoP<size_t>& Bus, size_t CiudadCambio){

}

/*Ejercicio 7*/
