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
typedef std::pair<Casilla,Casilla>p;

typedef GrafoP<size_t>Laberinto;
typedef std::vector<p>pes;

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
CaminoMasCorto(int N, pes& pes, Casilla& Entrada, Casilla& Salida){
    typedef GrafoP<size_t>G(N*N);
    for(size_t i =0; i<N;i++)

}


vector<GrafoP<size_t>::vertice> laberinto(size_t N, pes p, Casilla entrada, Casilla salida)
{
    GrafoP<size_t> G(N * N);
    for (size_t i = 0; i < N; i++)
    {
        for (size_t j = 0; j < N; j++)
        {
            if (i > 0)
            {
                if (find(p.begin(), p.end(), p{{i, j}, {i - 1, j}}) == p.end())
                {
                    G[casilla_nodo({i, j}, N)][casilla_nodo({i - 1, j}, N)] = 1;
                }
            }
            if (i < N - 1)
            {
                if (find(p.begin(), p.end(), p{{i, j}, {i + 1, j}}) == p.end())
                {
                    G[casilla_nodo({i, j}, N)][casilla_nodo({i + 1, j}, N)] = 1;
                }
            }
            if (j > 0)
            {
                if (find(p.begin(), p.end(), p{{i, j}, {i, j - 1}}) == p.end())
                {
                    G[casilla_nodo({i, j}, N)][casilla_nodo({i, j - 1}, N)] = 1;
                }
            }
            if (j < N - 1)
            {
                if (find(p.begin(), p.end(), p{{i, j}, {i, j + 1}}) == p.end())
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

/*Ejercicio 9*/

typedef std::pair<vector<size_t> , size_t > CaminoMinimo;
/*1. Crear la matriz de coste de 2*N nodos*/
CaminoMinimo Mcosteminimo(const GrafoP<size_t>& tren, const GrafoP<size_t>& bus, size_t origen, size_t destino, size_t ctaxi){
    //Creamos la matriz 2*n
    GrafoP<size_t> G(2*tren.numVert());

    //rellenamos la matriz
    for(size_t i = 0; i<tren.numVert(); i++){
        for(size_t j= 0; j<tren.numVert(); j++){
            //1er cuadrante
            if(i<tren.numVert() && j<tren.numVert()){
                G[i][j]=tren[i][j];
            }
            //2º y 3º Cuadrante
            else if(i < tren.numVert() && j >= tren.numVert() || i >= tren.numVert() && j < tren.numVert()){
                if(i+ tren.numVert() == j || j + tren.numVert() == i){
                    G[i][j] = ctaxi;
                }
                else G[i][j]=GrafoP<size_t>::INFINITO;
            }
            //4º Cuadrante
            else(i>=tren.numVert() && j>= tren.numVert()){
                G[i][j] = bus[i-tren.numVert()][j-tren.numVert()];
            }
        }
    }
    //Hemos rellenado el grafo, ahora hacemos dijkstra para Tren
    vector<size_t>DistanciaTren;
    vector<size_t>VerticesTren;
    size_t OrigenTren = origen;
    size_t DestinoTren = destino;
    DistanciaTren = Dijkstra(G,OrigenTren,VerticesTren);

    //Hacemos Dijkstra para el Bus
    vector<size_t>DistanciaBus;
    vector<size_t>VerticesBus;
    size_t OrigenBus = origen;
    size_t DestinoBus = destino;
    DistanciaBus = Dijkstra(G,OrigenBus,VerticesBus);

    //Obtenemos los costes de las 4 posibles maneras de viajar
    size_t viaje1 = DistanciaTren[DestinoTren];
    size_t viaje2 = DistanciaTren[DestinoBus];
    size_t viaje3 = DistanciaBus[DestinoBus];
    size_t viaje4 = DistanciaBus[DestinoTren];

    //Sacamos el mínimo
    size_t min= minimointeligente(viaje1,viaje2,viaje3,viaje4);

    //Devolvemos el mínimo y el camino de coste mínimo
     vector<size_t> verticesCamino = (min == a || min == b) ? VerticesTren : VerticesBus;

    vector<size_t> camino;
    size_t i = (min == a || min == b) ? DestinoTren : DestinoBus;;
    while (i != origen)
    {
        camino.push_back(i);
        i = verticesCamino[i];
    }
    camino.push_back(origen);
    camino.reserve(camino.size());
    return{camino,min};
}

//Hacemos una función mínimo debido a que si uno de los costes es infinito se obvia, por tanto,
//no podemos hacer uso de la función std::min de C++.
size_t minimointeligente(size_t a, size_t b, size_t c, size_t d){
    size_t minimo = a;
    if(b != GrafoP<size_t>::INFINITO && b<minimo){
        minimo = b;
    }
    if(c != GrafoP<size_t>::INFINITO && c<minimo){
        minimo = c;
    }
    if(d != GrafoP<size_t>::INFINITO && d<minimo){
        minimo = d;
    }
    return minimo;
}

/*Ejercicio 10*/
//En este ejercicio encontramos 3 grafos (tren, bus, avion).
std::pair<vector<size_t>, size_t>CosteMinimo
(const GrafoP<size_t>& tren, const GrafoP<size_t>& bus, const GrafoP<size_t>& avion,
size_t origen, size_t destino, size_t TaxiTB, size_t TaxiAero){
    GrafoP<size_t> G(3 * tren.numVert()); //tenemos un grafo 3*N

    //Rellenamos el nuevo grafo
    for(size_t i = 0; i<G.numVert(); i++){
        for(size_t j = 0; j<G.numVert() ; j++){
                //1er cuadrante Tren
                if(i<tren.numVert() && j <tren.numVert()){
                    G[i][j] = tren[i][j];
                }
                //2º y 4º Cuadrante -> TaxiTB
                else if(i<tren.numVert() && j>=tren.numVert() && j < 2*tren.numVert()){
                    if(j - tren.numVert() == i) G[i][j] = TaxiTB;
                    else G[i][j] = GrafoP<size_t>::INFINITO;
                }
                //3º Cuadrante -> TaxiAero
                else if(i<tren.numVert() && j >= 2*tren.numVert()){
                    if(j - 2 * tren.numVert() == i){
                        G[i][j] = TaxiAero;
                    }
                    else G[i][j] = GrafoP<size_t>::INFINITO;
                }

                //4º Cuadrante -> Bus
                else if(i>= tren.numVert() && i<2*tren.numVert() && j<tren.numVert()){
                    if(i - tren.numVert() == j){
                        G[i][j] = TaxiTB;
                    }
                    else{
                        G[i][j] = GrafoP<size_t>::INFINITO;
                    }
                }
                //5º Cuadrante -> bus
                else if(i<2*tren.numVert() && i >= tren.numVert() && j>=tren.numVert() && j < 2*tren.numVert()){
                    G[i][j] = bus[i-tren.numVert()][j-tren.numVert()];
                }
                //6º Cuadrante -> taxiAero
                else if(i>=tren.numVert()&&j && i<2*tren.numVert() && j>= 2*tren.numVert()){
                    if(i - tren.numVert() == j - 2*tren.numVert()) G[i][j] == TaxiAero;
                    else G[i][j] = GrafoP<size_t>::INFINITO;
                }
                
                //7º Cuadrante -> TaxiAero
                else if(i>=2*tren.numVert() && j<tren.numVert()){
                    if(i-2*tren.numVert() == j)G[i][j] = TaxiAero;
                    else G[i][j] = GrafoP<size_t>::INFINITO;
                }

                //8º Cuadrante -> TaxiAero
                else if(i>= 2*tren.numVert() && j>=tren.numVert() && j<2*tren.numVert()){
                    if(i-2*tren.numVert() == j - tren.numVert()) G[i][j] = TaxiAero;
                    else G[i][j] = GrafoP<size_t>::INFINITO;
                }
                //9º Cuadrante -> Avion
                else{
                    G[i][j] = avion[i-2*tren.numVert()][j-2*tren.numVert()];
                }
        }
    }

    //Hacemos Dijkstra para los viajes
    
    // Dijkstra desde la estación de tren de la ciudad origen
    vector<size_t> distanciasTren;
    vector<size_t> verticesTren;
    size_t origenTren = origen;
    size_t destinoTren = destino;
    distanciasTren = Dijkstra(G, origenTren, verticesTren); // el camino de costes minimos de Tren

    // Dijkstra desde la estación de bus de la ciudad origen
    vector<size_t> distanciasBus;
    vector<size_t> verticesBus;
    size_t origenBus = origen + tren.numVert();
    size_t destinoBus = destino + tren.numVert();
    distanciasBus = Dijkstra(G, origenBus, verticesBus); // Camino de costes minimos de Bus

    // Dijkstra desde el aeropuerto de la ciudad origen
    vector<size_t> distanciasAvion;
    vector<size_t> verticesAvion;
    size_t origenAvion = origen + 2 * tren.numVert();
    size_t destinoAvion = destino + 2 * tren.numVert();
    distanciasAvion = Dijkstra(G, origenAvion, verticesAvion); // Camino de costes minimos de Avion

    // Calcular el coste mínimo
    size_t a = distanciasTren[destinoTren];
    size_t b = distanciasTren[destinoBus];
    size_t c = distanciasTren[destinoAvion];
    size_t d = distanciasBus[destinoTren];
    size_t e = distanciasBus[destinoBus];
    size_t f = distanciasBus[destinoAvion];
    size_t g = distanciasAvion[destinoTren];
    size_t h = distanciasAvion[destinoBus];
    size_t i = distanciasAvion[destinoAvion];

    size_t min = minimo_inteligente(a, b, c, d, e, f, g, h, i);
    // Devolver el camino y el coste mínimo
    vector<size_t> verticesCamino = (min == a || min == b || min == c) ? verticesTren 
                    : (min == d || min == e || min == f) ? verticesBus 
                    : verticesAvion;

    vector<size_t> camino;
    size_t i = (min == a || min == d || min == g) ? destinoTren : 
               (min == b || min == e || min == h ) ? destinoBus : destinoAvion;
    while (i != origen)
    {
        camino.push_back(i);
        i = verticesCamino[i];
    }
    camino.push_back(origen);
    camino.reserve(camino.size());
    return {camino, min};
}

size_t minimo_inteligente(size_t a, size_t b, size_t c, size_t d, size_t e, size_t f, size_t g, size_t h, size_t i)
{
    // Hacer el minimo pero si es infinito no lo coja
    size_t min = a;
    if (b != GrafoP<size_t>::INFINITO && b < min)
        min = b;
    if (c != GrafoP<size_t>::INFINITO && c < min)
        min = c;
    if (d != GrafoP<size_t>::INFINITO && d < min)
        min = d;
    if (e != GrafoP<size_t>::INFINITO && e < min)
        min = e;
    if (f != GrafoP<size_t>::INFINITO && f < min)
        min = f;
    if (g != GrafoP<size_t>::INFINITO && g < min)
        min = g;
    if (h != GrafoP<size_t>::INFINITO && h < min)
        min = h;
    if (i != GrafoP<size_t>::INFINITO && i < min)
        min = i;
    return min;
}

/*Ejercicio 11*/
//Un puente es un pair de dos ciudades de dos islas diferentes
typedef std::pair<size_t,size_t>puente;
typedef std::vector<puente> puentes;

matriz<size_t> CosteMinimo11(const GrafoP<size_t>& Isla1, const GrafoP<size_t>& Isla2,
    const GrafoP<size_t>& Isla3, puentes p){

    GrafoP<size_t>G(Isla1.numVert() + Isla2.numVert() + Isla3.numVert());
    for(size_t i = 0; i<G.numVert(); i++){
        for(size_t j = 0; j<G.numVert(); j++){
            //1º Cuadrante -> Isla1
            if(i<Isla1.numVert() && j<Isla1.numVert())G[i][j]=Isla1[i][j];
            
            //5º Cuadrante -> Isla2
            else if(i>=Isla1.numVert() && i<Isla2.numVert()+Isla2.numVert() && j >= Isla1.numVert() && j<Isla1.numVert()+Isla2.numVert()){
                G[i][j] = Isla2[i-Isla1.numVert()][j-Isla1.numVert()];
            }

            //9º Cuadrante -> Isla3
            else if(i>=Isla1.numVert() + Isla2.numVert() && j >= Isla1.numVert() + Isla2.numVert()){
                G[i][j] = Isla3[i-Isla1.numVert() + Isla2.numVert()][j-Isla1.numVert() + Isla2.numVert()];
            }   
        else{
                G[i][j] = GrafoP<size_t>::INFINITO;
            }
        }   
    }

    //Insertamos los puentes que nos dan
    for(auto& puentesito : p){
        G[puentesito.first][puentesito.second] = 0;
        G[puentesito.second][puentesito.first] = 0;
    }
    //Calculamos la matriz de costes mínimos
    matriz<size_t>M, P;
    M = Floyd(G,P);
    return M;
}

/*Ejercicio 12*/
puente PuenteGrecoland(const GrafoP<size_t>& Phobos, const GrafoP<size_t>& Deimos,
    std::vector<size_t>&CosteraPhobos, std::vector<size_t>&CosteraDeimos){
    //Hacemos FLoyd tanto a Phobos como a Deimos para obtener la matriz de coste minimo
    matriz<size_t> P, Pphobos, D, Pdeimos;
    P = Floyd(Phobos,Pphobos);
    D = Floyd(Deimos, Pdeimos);

    size_t MinimoP = GrafoP<size_t>::INFINITO;
    for(size_t i = 0; i<CosteraPhobos.size(); i++){
        size_t media= 0;
        for(size_t j = 0; j<Phobos.numVert();j++){
            media += P[j][CosteraPhobos[i]];
        }
        if(media < MinimoP){
            MinimoP = CosteraPhobos[i];
        }
    }
    size_t MinimoD = GrafoP<size_t>::INFINITO;
    for(size_t i = 0; i<CosteraDeimos.size(); i++){
        size_t media= 0;
        for(size_t j = 0; j<Phobos.numVert();j++){
            media += D[j][CosteraDeimos[i]];
        }
        if(media < MinimoD){
            MinimoD = CosteraDeimos[i];
        }
    }
    return {MinimoP,MinimoD};
}