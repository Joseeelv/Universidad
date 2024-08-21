#include <iostream>
#include "Lista.hpp"
using namespace std;
 typedef struct Salto{
      double inicio_, fin_, altura_;
      Salto(double i=0.0, double f=0.0, double a=0.0):inicio_(i),fin_(f),altura_(a){}
    };
class Escalonada{
  public:
  //metodos de la clase
  	Escalonada(const Salto& s);
    void AnadirSalto(const Salto& s);
  	void EliminarSalto(const Salto& s);
  	double ValorFuncion(double)const;
  	double MinimoValor()const;
  	double MaximoValor()const;
  	void Translacion(double, double);
  	~Escalonada();
  private:
  	double x_,y_,z_,w_;
  	Lista<Salto>funcion_escalonada; //lista de los saltos de la funcion
};
typedef typename Lista<Salto>::posicion posicion;

Escalonada::Escalonada(const Salto& s){
  //Creamos la funcion escalonda con el primer salto
  funcion_escalonada.insertar(s, funcion_escalonada.primera());
}

void Escalonada::AnadirSalto(const Salto& s){
  //definimos p como la primera posicion de nuestra lista
  posicion p = funcion_escalonada.primera();
	//buscamos en todos los saltos si el inicio de los saltos de la lista
	//concuerda con el inicio del salto introducido
  for(p;p!=funcion_escalonada.fin();p=funcion_escalonada.siguiente(p)){
    if(funcion_escalonada.elemento(p).inicio_ != s.inicio_){
      //como los inicios son distintos, insertamos el trazo sin problemas
      	funcion_escalonada.insertar(s,p);
    }else{ //los inicios son iguales, debemos de sustituir la funcion, pero vamos a comprobar
        funcion_escalonada.insertar(Salto(funcion_escalonada.elemento(funcion_escalonada.fin()).fin_,x_,y_));
    }
  }
}

void Escalonada::EliminarSalto(const Salto& s){
  //definimos p como la primera posicion de nuestra lista
  posicion p = funcion_escalonada.primera();
  for(p;p!=funcion_escalonada.fin();p=funcion_escalonada.siguiente(p)){
		if(funcion_escalonada.elemento(p).inicio_ == s.inicio_){
      	funcion_escalonada.eliminar(p);
    }
  }
}

double Escalonada::ValorFuncion(double x)const{
  //buscamos el salto que concuerde con dicha posicion
  posicion p = funcion_escalonada.primera();
  for(p;p!=funcion_escalonada.fin();p=funcion_escalonada.siguiente(p)){
		if(funcion_escalonada.elemento(p).inicio_ >= x && funcion_escalonada.elemento(p).fin_ <= x){
      //estamos en el intervalo, devolvemos la altura
      	return funcion_escalonada.elemento(p).altura_;
    }
  }
  return 0; //si no encuentra nada.
}

double Escalonada::MinimoValor() const{
  //recorremos la funcion y vamos comprarndo las alturas
  posicion p = funcion_escalonada.primera();
  double minimo = funcion_escalonada.elemento(p).altura_;
  for(p;p!=funcion_escalonada.fin();p=funcion_escalonada.siguiente(p)){
    if(funcion_escalonada.elemento(p).altura_ < minimo){
      minimo = funcion_escalonada.elemento(p).altura_;
    }
  }
  return minimo;
}

double Escalonada::MaximoValor() const{
  //igual que MinimoValor
  posicion p = funcion_escalonada.primera();
  double maximo = funcion_escalonada.elemento(p).altura_;
	for(p; p!= funcion_escalonada.fin(); p= funcion_escalonada.siguiente(p)){
    if(funcion_escalonada.elemento(p).altura_ > maximo){
      maximo = funcion_escalonada.elemento(p).altura_;
    }
  }
  return maximo;
}

void Escalonada::Translacion(double w, double z){
  //vamos a desplazar la funcion w unidades horizontales, z verticales.
  //es decir sumamos w a la variable inicio_ y sumamos z a la variable fin_
	posicion p = funcion_escalonada.primera();
  for(p;p!=funcion_escalonada.fin();p = funcion_escalonada.siguiente(p)){
    //a cada salto vamos sumando los valores
    funcion_escalonada.elemento(p).inicio_ += w;
    funcion_escalonada.elemento(p).fin_ += z;
  }
}


Escalonada::~Escalonada(){
  funcion_escalonada.~Lista();
}

