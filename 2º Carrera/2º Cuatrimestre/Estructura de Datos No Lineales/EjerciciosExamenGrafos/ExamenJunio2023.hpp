/*
Modelizaremos Narnia como una matriz de NxM casillas. Los movimientos del fauno se modernizarán con los movimientos de un caballo del ajedrez. Dicho de otra forma, cada movimiento del fauno debe ser un movimiento de caballo de ajedrez.
A Narnia se llega a través de su entrada, casilla (0,0), y se marcha uno a través de una única salida, en la casilla (N-1, M-1).
Sería un problema bastante fácil, pero Narnia es un país lleno de peligros, en particular si eres un fauno.
Para empezar, los lugareños han puesto dentro de Narnia una serie de trampas en determinadas casillas, de forma que si pasas por ellas mueres. 
Pero no contentos con eso, los habitantes de Narnia han contratado Minos caballeros, que se colocan también en casillas estratégicas. En este caso, el fauno no muerte si cae en una de ellas, pero su muere en caso de caer en alguna de las casillas que rodean al caballero, entre 3 y 8, dependiendo de su posición, ya que su espada tiene longitud 1.
El problema nos pide dos cosas, la primera saber si el fauno puede hacer de forma segura el camino entre la entrada y la salida de Narnia, y, en caso afirmativo, cual sería el número mínimo de saltos necesarios para conseguirlo.

Dado los siguientes parámetros
  • Dimensiones de Narnia N y M.
  • Relación de casillas trampa.
  • Relación de casillas ocupadas por caballeros.
Implementa una función que calcula y devuelva si el fauno podrá llegar o no a la salida y, en caso afirmativo, el número mínimo de saltos necesarios para conseguirlo.
*/

#include <iostream>
#include <vector>
#include "grafoPMC.h"
#include "alg_grafoPMC.h"


//Vamos a convertir una casilla a un nodo
size_t Casilla_Nodo(size_t i, size_t j, size_t M){
  return i*M + j;
}

//Definimos los tipos de datos a usar
typedef std::pair<size_t,size_t>posicion;
typedef std::pair<bool,size_t> resultado; //booleano de si llega o no a la salida y el coste del viaje.


resultado Fauno(size_t N, size_t M, vector<posicion> &trampas, vector<posicion> &minos){
  //1º Creamos el grafo N*M
  GrafoP<size_t> GrafoFauno(N*M);
  //Rellenamos el grafo con los movimientos del Fauno
  for(size_t i = 0; i < M; i++)
    for(size_t j = i+1; j < N; j++){
      //Guardamos la casilla actual
      size_t casilla_actual = Casilla_Nodo(i,j,M);
      //Como el fauno se mueve como un caballo, tenemos 8 posibles movimientos que podemos efectuar, es decir, hay camino directo (ponerla a 1)
      if(i+1 < N && j-2 >= 0 )
        GrafoFauno[casilla_actual][Casilla_Nodo(i+1,j-1,M)] = 1;

      if(i+2 < N && j-1 <= 0)
        GrafoFauno[casilla_actual][Casilla_Nodo(i+2,j-1,M)] = 1;
      
      if(i+2 < N && j+1 < M)
        GrafoFauno[casilla_actual][Casilla_Nodo(i+2,j+1,M)] = 1;
      
      if(i+1 < N && j+2 < M )
        GrafoFauno[casilla_actual][Casilla_Nodo(i+1,j+2,M)] = 1;
      
      if(i-1 >= 0 && j+2 < M)
        GrafoFauno[casilla_actual][Casilla_Nodo(i-1,j+2,M)] = 1;

      if(i-2 >= 0 && j+1 < M)
        GrafoFauno[casilla_actual][Casilla_Nodo(i-2,j+1,M)] = 1;

      if(i-2 >= 0 && j-1 >= 0)
        GrafoFauno[casilla_actual][Casilla_Nodo(i-2,j-1,M)] = 1;
      
      if(i-1 >= 0 && j-2 >=0)
        GrafoFauno[casilla_actual][Casilla_Nodo(i-1,j-2,M)] = 1;
    }
  //Ahora rellenamos el grafo con las trampas del tablero, como el fauno no puede acceder, se pone infinito
  for(auto& trampa : trampas){
    size_t pos_trampa = Casilla_Nodo(trampa.first,trampa.second,M);
    for(size_t i = 0; i < GrafoFauno.numVert(); i++){
      GrafoFauno[pos_trampa][i] = GrafoP<size_t>::INFINITO;
      GrafoFauno[i][pos_trampa] = GrafoP<size_t>::INFINITO;
    }
  }
  //Ahora rellenamos el grafo con las posiciones donde se encuentran los minos y las adyacentes son inaccesibles, por lo que son infinito
  for(auto& mino : minos){
    for(size_t i = 0; i < GrafoFauno.numVert(); i++){
      if(mino.first >= 0 && mino.second - 1 >= 0)
        GrafoFauno[i][Casilla_Nodo(mino.first,mino.second-1,M)] = GrafoP<size_t>::INFINITO;
      if(mino.first+1 < M && mino.second-1 >= 0)
        GrafoFauno[i][Casilla_Nodo(mino.first+1,mino.second-1,M)] = GrafoP<size_t>::INFINITO;
      if(mino.first+1 < M && mino.second>= 0)
        GrafoFauno[i][Casilla_Nodo(mino.first+1,mino.second,M)] = GrafoP<size_t>::INFINITO;
      if(mino.first+1 < M && mino.second+1 < N)
        GrafoFauno[i][Casilla_Nodo(mino.first+1,mino.second+1,M)] = GrafoP<size_t>::INFINITO;
      if(mino.first >= 0 && mino.second+1 < N)
        GrafoFauno[i][Casilla_Nodo(mino.first,mino.second+1,M)] = GrafoP<size_t>::INFINITO;
      if(mino.first-1 >= 0 && mino.second+1 < N)
        GrafoFauno[i][Casilla_Nodo(mino.first-1,mino.second+1,M)] = GrafoP<size_t>::INFINITO;
      if(mino.first-1 >= 0 && mino.second>= 0)
        GrafoFauno[i][Casilla_Nodo(mino.first-1,mino.second,M)] = GrafoP<size_t>::INFINITO;
      if(mino.first-1 >= 0 && mino.second-1 >= 0)
        GrafoFauno[i][Casilla_Nodo(mino.first-1,mino.second-1,M)] = GrafoP<size_t>::INFINITO;
    }
  }
  //Ya tenemos el grafo relleno con los movimientos del fauno, las trampas y las posiciones de los minos con su casillas adyacentes inaccesibles. Por tanto, vamos a proceder a calcular el coste mínimo de ir desde el Origen (0,0), hasta el final.
  //Declaramos los vectores de vértices y coste mínimo para hacer uso de Dijkstra
  vector<size_t>vertices,Costeminimo;
  Costeminimo = Dijkstra(GrafoFauno,0,vertices);
  size_t salida = Casilla_Nodo(M-1,N-1,M); //calculamos la posicion de salida del tablero
  //nos creamos el resultado a devolver
  resultado res;
  if(Costeminimo[salida] != GrafoP<size_t>::INFINITO){
    res.first = true;
    res.second = Costeminimo[salida];
  }
  else{
    //No hay camino hacia la salida, devolvemos falso y 0, también podríamos devolver infinito
    res.first=false;
    res.second = 0;
  }
  return res; //devolvemos el estado y el coste del camino
}