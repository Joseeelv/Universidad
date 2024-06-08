#include <iostream>
#include <vector>
#include "../Materiales/grafoPMC.h"
#include "../Materiales/alg_grafoPMC.h"
// JUNIO 2023
// Modelizaremos narnia como una matriz de NxM casillas.
// Los movimientos del fauno se modernizarán con los movimientos de un caballo del ajedres.
// Dicho de otra forma: cada movimiento del fauno debe ser un movimiento de caballo de ajedrez
// A Narnia se llega a través de su entrada, casilla (0,0), y se marcha uno a través de la salida, casilla (N-1,M-1).
// Sería un problema bastante fácil, pero Narnia es un país lleno de peligros, en particular si eres un fauno.
// Para empezar los lugareños han puesto dentro de Narnia una serie de trampas en determinadas casillas de forma que si pasas por ellas mueres
// Pero no contentos con eso, los habitantes de Narnia han puesto una serie de Minos caballeros en determinadas casillas
// En este caso, el fauno no muere si pasa por una de estas casillas, pero si muere si cae en una casilla adyacente a un Minos
    // Entre 3 y 8 porque su espada mide 1 de longitud
    // El problema nos pide 2 cosas:
    // 1. Determinar si el fauno puede llegar a la salida sin morir
    // 2. Si puede llegar, determinar el número mínimo de movimientos necesarios para llegar a la salida
    // Dados los siguientes datos:
    // - Dimensiones de Narnia N y M
    // - Relación de casillas trampa
    // - Relación de casillas ocupadas por minos
// Implementa una función que calcua y devuelva si el fauno podrá llegar o no a la salida y, en caso afirmativo, el numero minimo de saltos necesarios para conseguirlo.


typedef std::pair<size_t,size_t>coordenada;
typedef std::pair<bool,size_t> resultado;

resultado narnia(size_t N, size_t M, const vector<coordenada>& trampas,const vector<coordenada>&minos)
{
    //Creamos el grafo con tamaño N*M
    GrafoP<size_t>G(N*M);
    //ahora vamos a poner las posiciones de los caballos
    for(size_t i = 0; i<M; i++)
        for(size_t j=i+1; j<N; j++){
            //Guardamos la casilla en la que estamos
            size_t actual = coordenadaAcasilla(i,j,M);
            //Como tenemos 8 posibles posiciones de caballo, esas las ponemos a 1
           if (i + 1 < N && j + 2 < M)
                G[actual][coordenadaAcasilla(i + 1, j + 2, M)] = 1;
            if (i + 1 < N && j - 2 >= 0)
                G[actual][coordenadaAcasilla(i + 1, j - 2, M)] = 1;
            if (i - 1 >= 0 && j + 2 < M)
                G[actual][coordenadaAcasilla(i - 1, j + 2, M)] = 1;
            if (i - 1 >= 0 && j - 2 >= 0)
                G[actual][coordenadaAcasilla(i - 1, j - 2, M)] = 1;
            if (i + 2 < N && j + 1 < M)
                G[actual][coordenadaAcasilla(i + 2, j + 1, M)] = 1;
            if (i + 2 < N && j - 1 >= 0)
                G[actual][coordenadaAcasilla(i + 2, j - 1, M)] = 1;
            if (i - 2 >= 0 && j + 1 < M)
                G[actual][coordenadaAcasilla(i - 2, j + 1, M)] = 1;
            if (i - 2 >= 0 && j - 1 >= 0)
                G[actual][coordenadaAcasilla(i - 2, j - 1, M)] = 1;
        }
    //Ahora añadimos las trampas, recorriendo el vector 
    for(auto& t : trampas){
        size_t coordenada_trampa = coordenadaAcasilla(t.first,t.second,M);
        for(size_t i = 0; i<G.numVert();i++){
            G[coordenada_trampa][i] = GrafoP<size_t>::INFINITO;
            G[i][coordenada_trampa] = GrafoP<size_t>::INFINITO;
        }
    }

    //Ahora añadimos a los minos, en las 8 posiciones posibles
    for(auto& m : minos){
        for(size_t i = 0; i<G.numVert();i++){
            if(m.first-1 >= 0 && m.second-1>= 0) G[i][coordenadaAcasilla(i-1,j-1,M)] = GrafoP<size_t>::INFINITO;
            if(m.first-1 >= 0 && m.second < N) G[i][coordenadaAcasilla(i-1,j,M)] = GrafoP<size_t>::INFINITO;
            if(m.first-1 >= 0 && m.second+1<N) G[i][coordenadaAcasilla(i-1,j+1,M)] = GrafoP<size_t>::INFINITO;
            if(m.first >= 0 && m.second+1<N) G[i][coordenadaAcasilla(i,j+1,M)] = GrafoP<size_t>::INFINITO;
            if(m.first+1 < M && m.second+1 < N) G[i][coordenadaAcasilla(i+1,j+1,M)] = GrafoP<size_t>::INFINITO;
            if(m.first+1 < M && m.second >= 0) G[i][coordenadaAcasilla(i+1,j,M)] = GrafoP<size_t>::INFINITO;
            if(m.first+1 < M && m.second-1>= 0) G[i][coordenadaAcasilla(i+1,j-1,M)] = GrafoP<size_t>::INFINITO;
            if(m.first >= 0 && m.second-1>= 0) G[i][coordenadaAcasilla(i,j-1,M)] = GrafoP<size_t>::INFINITO;
        }
    }

    //Ahora hacemos Dijsktra para buscar el camino con menos coste
    vector<size_t>vertices, costeMin;
    costeMin = Dijkstra(G,0,vertices); //nuestro origen es la casilla 0
    resultado res;
    if(costeMin[coordenadaAcasilla(M-1,N-1,M)]!=GrafoP<size_t>::INFINITO){
        res.first = true;
        res.second = costeMin[coordenadaAcasilla(M-1,N-1,M)];
    }
    else{
        //Si no hay camino, devuelve false y 0.
        res.first = false;
        res.second =0;
    }
    return res; //devolvemos el pair
}

size_t coordenadaAcasilla(size_t i, size_t j, size_t M){
    return (i*M+j);
}