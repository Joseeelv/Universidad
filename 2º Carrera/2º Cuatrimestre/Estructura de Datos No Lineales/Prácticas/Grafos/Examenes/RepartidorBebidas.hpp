#include <iostream>
#include <vector>
#include "../Materiales/grafoPMC.h"
#include "../Materiales/alg_grafoPMC.h"
// Un repartidor de una empresa de distribucion de bebidas tiene que visitar a todos sus clientes cada dias.Pero, al comentar su jornada de trabajo, no conoce que cantidad de bebidas
// tiene que servir cada cliente, por lo que no puede planificar una ruta optima para visitarlos a todos. Por tanto, nuestro repartidor decide llevar
// a cabo la siguiente estrategia: 
//     -El camión parte del almacen con la máxima carga permitida rumbo a su cliente más próximo
//     - El repartidor descarga las cajas de bebidas que le pide el cliente. si no tiene suficientes cajas en el camion, le entrega todas las que tiene. Este cliente terminara de ser servido en algun otro momento a lo largo del dia cuando la estratefia de reparto vuelva a llevar al repartidor hasta él 
//     - Después de servir a un cliente:
//     - Si quedan bebidas en el camion, el repartidor consulta su sistema de navegacion basado en el GPS para conocer la ruta que le lleva hasta su cliente más proximo pendiente de ser servido.
//     - Si no quedan bebidas en el camion, vuelve al almacén por el camino más corto y otra vez carga el camión completamente
//     - Despues de cargar el camión, el repartidor consulta su sistema de navegacion y se va por el camino mas corto a visitar al cliente pendiente de ser servido más proximo Implementa un subprograma que calcule y devuelva, la distancia total recorrida en un dia por nuestro repartidor a partir de lo siguiente :
//     - Grafo representado mediante la matriz de costes con las distancias de los caminos directos entre los clientes y entre ellos y la central
//     - Capacidad máxima del camión ( cantidad de cajas de bebidas)
//     - Asumiremos que existe una funcion int Pedido() que devuelve el numero de cajas que quedan por servir al cliente en el que se encuentra el repartidor
// NOTA: Es absolutamente necesario definir todos los tipos de datos implicados en la resolucion del problema, así como los prototipos de las operaciones utilizadas de los TADS conocidos y tambien los prototipos de los algoritmos de grafo utilizados de los estudiados en las asignaturas

int Pedido(size_t); //Método que nos facilitan

size_t Distanciarepartidor(GrafoP<size_t> G, size_t capacidadTotal, size_t centro ){
    //Lo primero que tenemos que hacer es buscar el vértice más cercano, entre todos los vértices -> FLOYD
    matriz<GrafoP<size_t>::vertice>MV;
    matriz<size_t> Mcostes = Floyd(G,MV); 
    //guardamos las cajas del camion
    size_t cajasCamion = capacidadTotal;
    //Vemos cuantas paradas tiene que hacer el camion 
    size_t paradas = G.numVert();
    //Vector que dice que ciudades han sido visitadas por el camion
    vector<bool>Abastecidos(G.numVert(), false); //ciudades visitadas de tamaño numVert y todas a falso porque no se han visitado todavía
    size_t distanciaTotal = 0; //distancia recorrida por el camion
    size_t vActual = centro;
    size_t Vaux; //creamos un vertice auxiliar
    while(visitados(Abastecidos)){
        vActual = minimoCoste(Mcostes, vActual); //Nos vamos al vertice más cercano
        distanciaTotal += MV[vActual][Vaux];  //Actualizamos la distancia del camion
        if(cajasCamion <= Pedido(vActual)){
            Pedido(vActual) -= cajasCamion; //descarga -> vuelve al origen -> carga
            distanciaTotal += MV[vActual][centro]; //sumamos las distancias de ida y vuelta
            //ahora estamos en el centro
            vActual = centro;
            //Recargamos el camion
            cajasCamion = capacidadTotal;

        }else{
            size_t cajasAux = Pedido(vActual);
            Pedido(vActual) -= cajasCamion;
            cajasCamion -= cajasAux;
            Abastecidos[vActual] = true;
        }
    }
    return distanciaTotal;
}

bool visitados(const vector<bool>ciudades){
    for(size_t i = 0; i<ciudades.size(); i++){
        if(!ciudades[i]){
            return true;
        }
        else return false;
    }
}

size_t minimoCoste(matriz<size_t>M, size_t nodo){
    size_t min = M[nodo][0];
    for(size_t i = 0; i<M.dimension(); i++){
        if(M[nodo][i] < min){
            min = M[nodo][i];
        }
    }
    return min;
}
