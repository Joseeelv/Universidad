#ifndef Pixeles_HPP
#define Pixeles_HPP

  /*
    Una forma de representar una figura plana en blanco y negro consiste en utilizar un árbol cuaternario en el que cada nodo o tiene exactamente cuatro hijos, o bien es una hoja.
    Un nodo hoja puede ser blanco o negro y un nodo interno no tiene color.

    Una figura dibujada dentro de un cuadrado de lado 2k se representa de la forma siguiente:
      
    Se divide el cuadrado en cuatro cuadrantes y cada uno se representa como un hijo del nodo raı́z. Si un cuadrante está completamente negro corresponde a una hoja negra; si, por el contrario, el cuadrante está completamente blanco, éste corresponde a una hoja blanca; y si un cuadrante está parcialmente ocupado por negro y blanco, entonces corresponde a un nodointerno del árbol y este cuadrante se representa siguiendo el mismo método subdividiéndoloen otros cuatro cuadrantes. Como ejemplo se muestra una figura en blanco y negro y su árbol asociado, tomando los cuadrantes en el sentido de las agujas del reloj a partir del cuadrante superior izquierdo.

    Implementa una función que dado un árbol de esta clase, con k+1 niveles, devuelva la figura asociada, representada como una matriz cuadrada de tamaño 2k en la que cada celda representa un punto blanco o negro.

    Nota: Por simplificar el problema, se asume que en cada nodo del árbol se incluyen las coordenadas de la esquina superior izquierda y de la esquina inferior derecha del cuadrante que representa.
  */

  #include <iostream>
  #include "agen.h"

  //Declaramos los tipos de datos a usar
  typedef struct Pixel{
    enum Color {Blanco,Negro,SinColor}color;
    //Nos movemos en el sentidos de las agujas del reloj
    size_t x_[2]; //  (0,0) --> (0,1) |
    size_t y_[2]; //  (0,1) <-- (1,1) v
  };

  //Devolvemos la matriz por referencia
  template <typename Pixel>
  void Figura(typename Agen<Pixel>::nodo n, const Agen<Pixel> &A, matriz<Pixel> &M){
    if(n != Agen<Pixel>::NODO_NULO){
      //Comprobamos si es un nodo intermedio
      if(A.elemento(n).color == Pixel::SinColor){
        //Vamos a recorrer a sus hijos
        typename Agen<Pixel>::nodo hijo = A.hijoIzqdo(n);
        while(hijo != Agen<Pixel>::NODO_NULO){
          //Llamamos a la función con los hijos
          Figura(hijo,A,M);
          hijo = A.hermDrcho(hijo);
        }
      }
      else if(A.elemento(n).color == Pixel::Blanco || A.elemento(n).color == Pixel::Negro){
        //Vamos ir insertando en la matriz los colores
        for(auto i = A.elemento(n).x_[0]; i < A.elemento(n).x_[1]; i++)
          for(auto j = A.elemento(n).y_[1]; j < A.elemento(n).y_[0]; j++){
            M[i][j] = A.elemento(n).color;
          }
      }
      //Si es otro color, no hace nada xd
    } 
    //Si es nodo nulo, no se hace nada
  }
#endif // !Pixeles_HPP
