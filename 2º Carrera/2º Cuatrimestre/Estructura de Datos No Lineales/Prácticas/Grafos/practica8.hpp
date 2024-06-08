#include <iostream>
#include <vector>
#include "../Materiales/grafoPMC.h"
#include "../Materiales/alg_grafoPMC.h"
#include "particion.h"
#include <cmath>

/*Ejercicio 1*/
typedef std::pair<size_t,size_t>ciudad;

typedef struct{
    vector<ciudad>ciudades;
    matriz<size_t> Mcoste;
}isla;

typedef vector<isla> archipielago;

archipielago Tombuctu1(vector<ciudad> ciudades, GrafoP<size_t>& carreteras){
    Particion p(ciudades.size());
    for(size_t i = 0; i<ciudades.size(); i++){
        for(size_t j=i+1; j<ciudades.size(); j++){
            if(carreteras[i][j]){
                p.unir(p.encontrar(i),p.encontrar(j));
            }
        }
    }
    // Ahora mismo en p tengo las islas ya formadas
    // [{c1,c2,c3},{c4,c5,c6,c7}]
    archipielago ArchipielagoAux;
    isla IslaAux;
    //recorremos la partición creando para cada subconjunto una isla
    //a cada isla le vamos a calcular el coste mínimo de viajar entre ciudades de la misma
    //y las insertamos dentro del archipielago Auxiliar
    size_t representante = p.encontrar(0);
    for(size_t i = 0; i<ciudades.size(); i++){
        if(representante ==p.encontrar(i)){ //mismo represnetante, misma isla
            IslaAux.ciudades.push_back(ciudades[i]);
        }
        else{
            IslaAux.Mcoste = calcularCostes(IslaAux.ciudades);
            ArchipielagoAux.push_back(IslaAux);
            IslaAux.ciudades.clear();
            IslaAux.ciudades.push_back(ciudades[i]);
            representante = p.encontrar(i);
        }
    }
    //Ahora calculamos los costes mínimos de ir de una ciudad cualquiera de cada isla
    

    return ArchipielagoAux;
}

matriz<size_t> calcularCostes(vector<ciudad>c){
    GrafoP<size_t> costes(c.size());

    matriz<size_t> res(costes.numVert()), vertices(costes.numVert());

    for(size_t i = 0; i<costes.numVert(); i++){
        for(size_t j = 0; j < costes.numVert(); j++){
            costes[i][j] = distanciaEU(c[i],c[j]);
        }
    }
    res = Floyd(costes, vertices);
    return res;
}

size_t distanciaEU(ciudad a, ciudad b){
    return sqrt(pow(a.first - b.first, 2) + pow(a.second - b.second, 2));
}

/*Ejercicio 2*/
typedef vector<std::pair<ciudad,ciudad>> lineasaereas;

lineasaereas Tombuctu2(vector<ciudad> ciudades, GrafoP<size_t>& carreteras){
    archipielago archipielagoAux = Tombuctu1(ciudades,carreteras);
    lineasaereas lineasaereasAux;

    for(size_t i = 0; i<archipielagoAux.size(); i++){
        for (size_t j=i+1; j<archipielagoAux.size(); i++){
            size_t costeMin = GrafoP<size_t>::INFINITO;
            ciudad ciudadIsla1, ciudadIsla2;
            for(size_t k=0; k < archipielagoAux[i].ciudades.size(); k++){
                for(size_t l = 0; k < archipielagoAux[j].ciudades.size(); l++){
                    if(distanciaEU(archipielagoAux[i].ciudades[k], archipielagoAux[j].ciudades[l])< costeMin){
                        costeMin = archipielagoAux[i].Mcoste[k][l];
                        ciudadIsla1 = archipielagoAux[i].ciudades[k];
                        ciudadIsla2 = archipielagoAux[j].ciudades[l];
                    }
                }
            }
            lineasaereasAux.push_back({ciudadIsla1,ciudadIsla2});
        }
    }
    return lineasaereasAux;
}

/*Ejercicio 3*/
template <typename tCoste>
GrafoP<tCoste> KruskallMaximo(const GrafoP<tCoste> &G)
// Devuelve un árbol generador de coste máximo
// de un grafo no dirigido ponderado y conexo G.
{
    assert(!G.esDirigido());

    typedef typename GrafoP<tCoste>::vertice vertice;
    typedef typename GrafoP<tCoste>::arista arista;

    const size_t n = G.numVert();
    Particion p(n);
    vector<arista> aristas;
    for (vertice u = 0; u < n; ++u)
        for (vertice v = u + 1; v < n; ++v)
            if (G[u][v] != GrafoP<tCoste>::INFINITO)
                aristas.push_back(arista(u, v, G[u][v]));

    sort(aristas.begin(), aristas.end(), greater<arista>()); //ordenar por la arista mayor
    
    // Igual a Kruskall pero en vez de ordenar de menor a mayor, ordenamos de mayor a menor 
    GrafoP<tCoste> A(n);
    for (size_t i = 0; i < aristas.size(); ++i)
    {
        vertice u = aristas[i].u, v = aristas[i].v;
        if (p.encontrar(u) != p.encontrar(v))
        {
            A[u][v] = A[v][u] = aristas[i].coste;
            p.unir(u, v);
        }
    }
    return A;
}

/*Ejercicio 4*/
GrafoP<size_t>CanalesJerte(vector<ciudad>ciudades){
    //Cremos un grafo con las distancias entre ciudades
    GrafoP<size_t> G(ciudades.size());

    for(size_t i = 0; i< G.numVert(); i++){
        for(size_t j=i+1; j<G.numVert(); j++){
            G[i][j] = distanciaEU(ciudades[i],ciudades[j]);
        }
    }
    return KruskallMaximo(G);
}

/*Ejercicio 5*/
size_t RETEUNI3(GrafoP<size_t>grafo){
    GrafoP<size_t> G(grafo.numVert());
    size_t resultado = 0;
    for(size_t i = 0; i<G.numVert(); i++){
        for(size_t j = i+1; j<G.numVert(); j++){
            resultado += G[i][j];
        }
    }
    return resultado;
}

/*Ejercicio 6*/

typedef struct{
    size_t distancia_,caudal_;
}canal;

GrafoP<canal> EMASAJER(matriz<size_t>caudales,matriz<size_t> distancias, size_t subvencionCaudal, size_t costeDistancia){
    GrafoP<size_t>Aux (caudales.dimension());
      // rellenamos el grafo con los caudales y distancias
    for (size_t i = 0; i < caudales.dimension(); i++){
        for (size_t j = i + 1; j < caudales.dimension(); j++){
           Aux[i][j]=caudales[i][j]*subvencionCaudal - caudales[i][j]*costeDistancia;
        }
    }
    Aux=KruskallMaximo(Aux);
    //Creamos un nuevo grafo de canales que lo rellenaremos 
    GrafoP<canal> Canalres(Aux.numVert());
    for(size_t i = 0; i<Canalres.numVert(),i++){
        for(size_t j=i+1; j<Canalres.numVert(); j++){
            if(Aux[i][j] != GrafoP<size_t>::INFINITO){
                Canalres[i][j].caudal_ = caudales[i][j];
                Canalres[i][j].distancia_ = distancias[i][j];
            }
        }
    }
    return Canalres;
}

/*Ejercicio 7*/
size_t Grecoland(vector<ciudad> fobos, vector<ciudad> deimos, vector<ciudad> costerasFobos, vector<ciudad> costerasDeimos, size_t origen, size_t destino){
    GrafoP<size_t>Grecoland(fobos.size() + deimos.size());
    GrafoP<size_t>Phobos(fobos.size());
    GrafoP<size_t>Deimos(deimos.size());

//Minimizamos las carreteras
    for (size_t i = 0; i < fobos.size(); i++)
        for (size_t j = i + 1; j < fobos.size(); j++)
            Phobos[i][j] = distanciaEU(fobos[i], fobos[j]);
    Phobos = Kruskall(Phobos);

     for (size_t i = 0; i < deimos.size(); i++)
        for (size_t j = i + 1; j < deimos.size(); j++)
            Deimos[i][j] = distanciaEU(deimos[i], deimos[j]);
    Deimos = Kruskall(Deimos);

    //Vamos a comprobar cuales de las ciudades costeras de ambas isla son las más cercanas
    //Rellenamos el grafo de Grecoland primero con Fobos
    for(size_t i = 0; i<fobos.size(); i++){
        for(size_t j = 0; j<fobos.size(); j++){
            Grecoland[i][j] = Phobos[i][j];
        }
    }
    //ahora con Deimos
    for(size_t i = 0; i<deimos.size(); i++){
        for(size_t j = 0; j<deimos.size(); j++){
            Grecoland[i+fobos.size()][j+fobos.size()] = Deimos[i][j];
        }
    }
       // Rellenamos el grafo con los puentes
    for (size_t i = 0; i < fobos.size(); i++)
    {
        for (size_t j = 0; j < deimos.size(); j++)
        {
            if (find(costerasFobos.begin(),  costerasFobos.end(),  fobos[i])  != costerasFobos.end() &&
                find(costerasDeimos.begin(), costerasDeimos.end(), deimos[j]) != costerasDeimos.end())
            {
                size_t costePuente = distanciaEU(fobos[i], deimos[j]);
                Grecoland[i][j + fobos.size()] = costePuente;
                Grecoland[j + fobos.size()][i] = costePuente;
            }
        }
    }
    //Minimizamos los puentes
    Grecoland = Kruskall(Grecoland);

    //Aplicamos Floyd para obtener matriz de costes minimos
    matriz<size_t> vertices (Grecoland.numVert());
    matriz<size_t>resultado = Floyd(Grecoland,vertices);
    return resultado[origen][destino];
}
